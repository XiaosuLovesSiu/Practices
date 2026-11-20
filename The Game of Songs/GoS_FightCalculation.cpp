#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <utility>
#include <string>

using namespace std;

// ---------------------------------------------------------------------------
// 效果模型（Effect）
//
// 一个回合内双方机器人「同时」结算：
//   1. 双方「校验」主招式：重章叠唱连用检测、主费用检查（违规 → 生命归 0，招式无效；不扣费）；
//   2. 特异性防御（防X）：若某方使用防X且对方本回合使用X（双方均有效、且X本回合生效），
//      取消X的所有效果（花费照常），防御方 valCuiwei +1；防采采/防苍苍成功时再获得「灵」
//      （antiRepeater）。被防招式若违规或本回合被封印（如采采在 round<5）则不触发；
//   3. 时间旅行（溯洄）：溯洄本回合生效且未被防溯洄取消时，令上一回合重新结算，追加 1 点
//      锋伤害参与上一回合的叠加/相抵/免伤（蝴蝶效应）；若重算已造成击杀，本回合立即结束；
//   4. 为霜盾校验（时间旅行之后：重算可能打掉盾）→ 盾不足即违规（主招式与为霜都无效、费用
//      与盾均不扣）→ 扣费（主费用 + 为霜盾）；
//   5. 执行各 effect（违规/被封印/被防御取消的招式跳过；获得资源、造成伤害、获得免伤、
//      放置溯游标记等）；
//   6. 双方 effect 跑完后结算伤害（相抵、免伤，见 roundCal 内注释）；
//   7. 最后结算「延后结算」的伤害（苍苍，所有其它效果之后、免伤已移除，目前必中）；
//   8. 采采/苍苍的 antiRepeater 仅在该点伤害造成对方实际生命扣减时才赋予。
//
// 招式 minRound：最早生效回合（从 1 开始）。采采 minRound=5（第 5 回合起才生效；前 4 回合
// 使用采采效果被取消，非违规，不触发防御，且不视为使用了重章叠唱招式），其余招式 minRound=1。
//
// cost 只负责「消耗资源」。获得资源、造成伤害、获得免伤、采采/苍苍/溯游的效果都属于 effect；
// 溯洄的「重新结算上一回合」由 action.rewindSharp 字段驱动（非 effect，因它需要访问上一回合快照）。
// 式微·X（104/204/304）的 30 点伤害由 shiweiEffect(X) 触发：对手支付费用后耗尽对应资源，或使用
// 重章叠唱招式且无该资源；资源判定发生在 effect 执行阶段（双方均已扣费），被封印招式不触发式微。
// 蓁蓁（309）的 1 点弱免伤由 addWeakReduction 提供；其「受非锋溢出伤害每 1 点获得 1 桃夭」由
// action.overflowGainType 字段驱动（结算阶段、抵算后免伤前，非 effect，因它需要知道溢出伤害量）。
// 白露（202）获得盾；盾在 applyDamage 中优先抵挡（每 1 盾 = 1 生命）。「为霜」由纸带 * 后缀触发
// （id=910，不消耗回合）：每 1 次消耗 1 盾、造成 1 点锋伤害；盾不足则违规（生命归 0，主招式与为霜
// 都无效、费用均不扣）。防为霜（1910）取消对方全部为霜（盾照常支付）。
//
// 多段伤害（同来源）：本回合招式伤害（damageOut.normal/sharp）+ 上回合溯游标记的锋伤害
// 叠加求和；只要其中存在锋伤害，总和伤害即为锋伤害。多段免伤：收到锋溢出伤害时弱免伤无效，
// 否则弱免伤与正常免伤叠加（详见 roundCal 注释）。
//
// effect 回调签名：void(player& user, player& opponent, RoundContext& ctx)
//   user/opponent = 出招者/对方；ctx = 本回合上下文（伤害、免伤、双方招式、溯游标记等）。
//
// 招式标签：basic（是否基础资源招式）、isRepeater（重章叠唱）。
// 伤害类型：DamageType::Normal / Sharp。
// ---------------------------------------------------------------------------

enum class DamageType { Normal, Sharp };

// 本回合即将造成的伤害，按类型区分
struct DamageAmount
{
    int normal = 0;
    int sharp = 0;
    int total() const { return normal + sharp; }
};

class action;   // 前置声明：RoundContext 需要持有对方招式的指针

struct RoundContext
{
    DamageAmount damageOut;                     // 本回合招式造成的伤害（同时结算）
    DamageAmount delayedOut;                    // 延后结算的伤害（所有效果之后，目前必中）
    int reduction = 0;                          // 出招者本回合获得的正常免伤（非弱免伤）
    int weakReduction = 0;                      // 出招者本回合获得的弱免伤（锋伤害下无效）
    int suyouPlaced = 0;                        // 本回合放置的溯游标记数（下回合结算为锋伤害）
    const action* opponentAction = nullptr;             // 对方本回合招式
    const action* opponentPreviousAction = nullptr;     // 对方上一回合招式
    const action* userPreviousAction = nullptr;         // 自己上一回合招式（重章叠唱连用检测）
    bool pendingAntiRepeater = false;                   // 若伤害实际扣血，给对方打上 antiRepeater
    bool effectsCancelled = false;                      // 本回合效果被特异性防御取消（花费照常）
    int round = 0;                                      // 当前回合数（从 1 开始，用于招式生效条件）
    int shuangCount = 0;                                // 本回合「为霜」次数（不消耗回合，每 1 次 = 1 点锋伤害）
    bool shuangCancelled = false;                       // 为霜被「防为霜」取消
};

class player
{
public:
    int heart;
    int shield;              // 护盾：受到伤害（免伤后）优先用盾抵挡，每 1 盾 = 1 生命；白露获得、为霜消耗
    vector<int> resources;   // 8 种资源；下标 0..7 对应资源类型 1..8
    bool antiRepeater;       // 「灵」效果：为 true 时采采/苍苍对其不再生效
    bool revivable;          // (预留，当前未使用)

    int valCuiwei;           // 式微/防X 计数（特异性防御成功时 +1）
    int valYuanxing;         // (预留，当前未使用)

    int lastActionId;        // 上一回合使用的招式 id（0 表示无，用于跨回合规则）
    int suyouNow;            // 本回合结算时对对方造成的溯游锋伤害（上回合放置）

    player() : heart(2), shield(0), resources(8, 0), antiRepeater(false),
               revivable(true), valCuiwei(0), valYuanxing(1), lastActionId(0), suyouNow(0) {}
    player(int hp) : heart(hp), shield(0), resources(8, 0), antiRepeater(false),
                     revivable(true), valCuiwei(0), valYuanxing(1), lastActionId(0), suyouNow(0) {}
};

using Effect = function<void(player& user, player& opponent, RoundContext& ctx)>;

// ---------------------------------------------------------------------------
// cost 工具：cost 只描述「消耗多少资源」
// ---------------------------------------------------------------------------

vector<int> noCost() { return vector<int>(8, 0); }

vector<int> costOf(int type, int amount)
{
    vector<int> c(8, 0);
    if (type >= 1 && type <= 8)
        c[type - 1] = amount;
    return c;
}

// ---------------------------------------------------------------------------
// 招式（action）
// ---------------------------------------------------------------------------
class action
{
public:
    int id;
    int system;              // 该招式所属派系（1..8，0 = 无）；仅作说明，不影响结算
    vector<int> cost;        // 消耗的资源（下标 0..7）；不够则违规判负
    bool isRepeater;         // 重章叠唱标签（参与「不能连续使用」规则）
    bool selectgoal;         // 是否有目标指定（true 表示该招式作用于对方）
    bool basic;              // 是否基础资源招式（供采采等 effect 检查）
    player* user;            // (预留，当前未使用)
    player* goal;            // (预留，当前未使用)
    vector<Effect> effects;  // 费用支付后依次执行的 effect
    int defendAgainst;       // 特异性防御：0=非防御招式；>0=「防X」，值是被防招式 id
    int minRound;            // 招式最早生效回合（从 1 开始；采采=5，其余=1）
    int rewindSharp;         // 时间旅行：>0 表示本招式令上一回合重新结算，值=给目标追加的锋伤害
    int overflowGainType;    // 蓁蓁：>0 表示使用者受到非锋溢出伤害时，每 1 点获得该类型资源（0=无）

    action(int ID, int sys, const vector<int>& cst, bool repeat, bool select,
           bool isBasic = false, vector<Effect> effs = {}, int defendAgainstId = 0,
           int minRoundVal = 1, int rewindSharpVal = 0, int overflowGainTypeVal = 0)
        : id(ID), system(sys), cost(cst), isRepeater(repeat), selectgoal(select),
          basic(isBasic), user(nullptr), goal(nullptr), effects(std::move(effs)),
          defendAgainst(defendAgainstId), minRound(minRoundVal), rewindSharp(rewindSharpVal),
          overflowGainType(overflowGainTypeVal)
    {
        if (cost.size() < 8)
            cost.resize(8, 0);
    }
};

// ---------------------------------------------------------------------------
// effect 工厂函数
// ---------------------------------------------------------------------------

// 获得 amount 个资源类型 type（type 取 1..8）的资源
Effect gainResource(int type, int amount)
{
    return [type, amount](player& user, player&, RoundContext&) {
        if (type >= 1 && type <= (int)user.resources.size())
            user.resources[type - 1] += amount;
    };
}

// 对对方造成 amount 点伤害（同时结算：先相抵、再被对方本回合免伤减免）
Effect dealDamage(int amount, DamageType type = DamageType::Normal)
{
    return [amount, type](player&, player&, RoundContext& ctx) {
        if (type == DamageType::Sharp)
            ctx.damageOut.sharp += amount;
        else
            ctx.damageOut.normal += amount;
    };
}

// 本回合获得 amount 点正常免伤（每 1 点使受到的伤害减少 1，最少为 0）
Effect addReduction(int amount)
{
    return [amount](player&, player&, RoundContext& ctx) {
        ctx.reduction += amount;
    };
}

// 本回合获得 amount 点弱免伤（若本回合受到的溢出伤害是锋类型则无效）
Effect addWeakReduction(int amount)
{
    return [amount](player&, player&, RoundContext& ctx) {
        ctx.weakReduction += amount;
    };
}

// 获得 amount 点护盾（shield）：受到伤害时优先用盾抵挡，每 1 盾等效 1 点生命
Effect gainShield(int amount)
{
    return [amount](player& user, player&, RoundContext&) {
        user.shield += amount;
    };
}

// 采采：指定对方，若其本回合使用基础资源招式（basic）且 antiRepeater 为 false，
// 对其造成 1 点「锋」伤害；antiRepeater 的赋予延迟到伤害实际扣血后。
Effect caicaiEffect()
{
    return [](player&, player& opponent, RoundContext& ctx) {
        if (ctx.opponentAction && ctx.opponentAction->basic && !opponent.antiRepeater)
        {
            ctx.damageOut.sharp += 1;
            ctx.pendingAntiRepeater = true;
        }
    };
}

// 苍苍：指定对方，若其上回合与本回合使用的招式都是薄言（boyan，id=900）且 antiRepeater
// 为 false，对其造成 1 点「延后结算」的伤害（所有其它效果之后，免伤已移除，目前必中）。
Effect cangcangEffect()
{
    return [](player&, player& opponent, RoundContext& ctx) {
        if (ctx.opponentAction && ctx.opponentPreviousAction
            && ctx.opponentAction->id == 900
            && ctx.opponentPreviousAction->id == 900
            && !opponent.antiRepeater)
        {
            ctx.delayedOut.normal += 1;
            ctx.pendingAntiRepeater = true;
        }
    };
}

// 桃夭：若本回合使用者的生命为 1 且 shield 为 0，则额外获得 1 点弱免伤。
Effect taoyaoEffect()
{
    return [](player& user, player&, RoundContext& ctx) {
        if (user.heart == 1 && user.shield == 0)
            ctx.weakReduction += 1;
    };
}

// 溯游：对目标玩家施加溯游标记，使其在下回合受到来自本招式使用者的一点「锋」伤害。
Effect suyouEffect()
{
    return [](player&, player&, RoundContext& ctx) {
        ctx.suyouPlaced += 1;
    };
}

// 式微·X（X 为资源类型编号 1..3）：若对手本回合满足以下任一条，对其造成 30 点普通伤害：
//   1) 对手使用了 system=X 的非基础资源招式，且支付其消耗后该种资源耗尽（=0）；
//   2) 对手使用了（任意系列的）重章叠唱招式，且其没有 X 对应的资源。
// 资源检查发生在双方已支付费用之后（runEffects 阶段）；被封印的招式（如采采 round<5）不触发。
Effect shiweiEffect(int X)
{
    return [X](player&, player& opponent, RoundContext& ctx) {
        if (!ctx.opponentAction)
            return;
        bool oppActive = (ctx.round >= ctx.opponentAction->minRound);
        if (!oppActive)
            return;
        bool exhausted = (X >= 1 && X <= (int)opponent.resources.size())
                         && (opponent.resources[X - 1] == 0);
        bool cond1 = (ctx.opponentAction->system == X) && !ctx.opponentAction->basic && exhausted;
        bool cond2 = ctx.opponentAction->isRepeater && exhausted;
        if (cond1 || cond2)
            ctx.damageOut.normal += 30;
    };
}

// ---------------------------------------------------------------------------
// 结算
// ---------------------------------------------------------------------------

bool actionExists(int id, const map<int, action>& content)
{
    return content.find(id) != content.end();
}

const action* findAction(int id, const map<int, action>& content)
{
    auto it = content.find(id);
    return it == content.end() ? nullptr : &it->second;
}

// 校验一个机器人的主招式（不扣费）。
// 返回 false 表示违规（重章叠唱连用 / 主费用不足）：该机器人生命立即归 0，招式不生效。
// 为霜的盾不足在 roundCal 的「时间旅行」之后单独校验（时间旅行可能打掉盾），故此处不检查。
bool validateMain(const action& a, player& user, RoundContext& ctx)
{
    // 规则1：重章叠唱招式不能连续使用。
    // 本回合被封印的招式（如采采在 round < minRound）不触发此违规：效果取消、非违规。
    bool active = (ctx.round >= a.minRound);
    // 上一回合的招式仅在其上一回合「已生效」（未被封印）时才计为一次使用：
    // 采采前 4 回合被封印（round < minRound），不视为使用了重章叠唱招式。
    bool prevWasActive = ctx.userPreviousAction && (ctx.round - 1) >= ctx.userPreviousAction->minRound;
    if (active && a.isRepeater && prevWasActive && ctx.userPreviousAction->isRepeater)
    {
        user.heart = 0;
        return false;
    }

    // 规则2：主费用不足即违规
    for (int i = 0; i < (int)a.cost.size() && i < (int)user.resources.size(); ++i)
    {
        if (user.resources[i] < a.cost[i])
        {
            user.heart = 0;   // 违反规则：资源不足，生命立即归 0，招式不生效
            return false;
        }
    }
    return true;
}

// 扣费：主费用 + 为霜的盾。调用前须已通过 validateMain 与「为霜盾足够」校验。
void payCost(const action& a, player& user, RoundContext& ctx)
{
    for (int i = 0; i < (int)a.cost.size() && i < (int)user.resources.size(); ++i)
        user.resources[i] -= a.cost[i];
    user.shield -= ctx.shuangCount;   // 支付为霜的盾
}

// 执行一个机器人的招式效果（若被特异性防御取消则跳过；花费已照常支付）
void runEffects(const action& a, player& user, player& opponent, RoundContext& ctx)
{
    if (ctx.effectsCancelled)
        return;
    for (const Effect& e : a.effects)
        e(user, opponent, ctx);
}

// 把 damage 结算到 target 身上：先被 target 的免伤抵扣，再由盾抵挡，最后扣生命
void applyDamage(player& target, int damage, int reduction)
{
    int taken = max(0, damage - reduction);
    int absorbed = min(target.shield, taken);   // 盾优先抵挡（每 1 盾 = 1 生命）
    target.shield -= absorbed;
    taken -= absorbed;
    target.heart = max(0, target.heart - taken);
}

// 同来源多段伤害的汇总：招式伤害 + 上回合溯游锋伤害；存在锋伤害则总和为锋伤害
struct DamageSummary
{
    int amount = 0;
    bool hasSharp = false;
    DamageType type() const { return hasSharp ? DamageType::Sharp : DamageType::Normal; }
};

DamageSummary summarizeDamage(const DamageAmount& dmg, int suyouSharp)
{
    DamageSummary s;
    s.amount = dmg.total() + suyouSharp;
    s.hasSharp = (dmg.sharp > 0) || (suyouSharp > 0);
    return s;
}

// 免伤结算：收到锋溢出伤害 → 仅正常免伤；否则正常免伤 + 弱免伤
int effectiveReduction(const RoundContext& ctx, DamageType overflowType)
{
    if (overflowType == DamageType::Sharp)
        return ctx.reduction;
    return ctx.reduction + ctx.weakReduction;
}

// ---------------------------------------------------------------------------
// 时间旅行（溯洄）：上一回合伤害结算快照
// ---------------------------------------------------------------------------

// 记录上一回合「伤害结算前」的状态，供「溯洄」重新结算上一回合使用
struct RoundSnapshot
{
    bool valid = false;                // 是否存在上一回合（第 1 回合为 false）
    int h1 = 0, h2 = 0;                // 伤害结算前双方生命
    bool ar1 = false, ar2 = false;     // 伤害结算前双方 antiRepeater（已含特异性防御赋予的「灵」）
    int shield1 = 0, shield2 = 0;      // 伤害结算前双方护盾
    DamageAmount dmg1, dmg2;           // 双方本回合招式伤害
    int suyou1 = 0, suyou2 = 0;        // 双方本回合结算的溯游锋伤害（上回合放置）
    int red1 = 0, weak1 = 0, red2 = 0, weak2 = 0;  // 双方本回合正常/弱免伤
    DamageAmount delayed1, delayed2;   // 双方本回合延后结算伤害（苍苍）
    bool pendingAR1 = false, pendingAR2 = false;   // 双方 pendingAntiRepeater
};

// 重新结算上一回合：把 rewindSharp1/rewindSharp2 点锋伤害追加进上一回合伤害，
// 重跑「同来源叠加 → 相抵 → 免伤 → 延后结算 → 灵赋予」全过程（时间旅行打击、蝴蝶效应）。
void rewindRound(player& p1, player& p2, const RoundSnapshot& snap, int rewindSharp1, int rewindSharp2)
{
    if (!snap.valid)
        return;

    // 恢复上一回合伤害结算前的状态（生命 + antiRepeater + 护盾）
    p1.heart = snap.h1;
    p2.heart = snap.h2;
    p1.antiRepeater = snap.ar1;
    p2.antiRepeater = snap.ar2;
    p1.shield = snap.shield1;
    p2.shield = snap.shield2;

    // 同来源多段伤害叠加：上一回合招式伤害 + 溯游锋伤害 + 溯洄追加的锋伤害
    DamageSummary s1 = summarizeDamage(snap.dmg1, snap.suyou1);
    s1.amount += rewindSharp1;
    if (rewindSharp1 > 0) s1.hasSharp = true;
    DamageSummary s2 = summarizeDamage(snap.dmg2, snap.suyou2);
    s2.amount += rewindSharp2;
    if (rewindSharp2 > 0) s2.hasSharp = true;

    // 相抵
    int overflowToP1 = 0;
    int overflowToP2 = 0;
    DamageType typeToP1 = DamageType::Normal;
    DamageType typeToP2 = DamageType::Normal;
    if (s1.amount > s2.amount)
    {
        overflowToP2 = s1.amount - s2.amount;
        typeToP2 = s1.type();
    }
    else if (s2.amount > s1.amount)
    {
        overflowToP1 = s2.amount - s1.amount;
        typeToP1 = s2.type();
    }

    // 免伤结算（锋溢出 → 弱免伤无效）
    int redToP1 = (typeToP1 == DamageType::Sharp) ? snap.red1 : (snap.red1 + snap.weak1);
    int redToP2 = (typeToP2 == DamageType::Sharp) ? snap.red2 : (snap.red2 + snap.weak2);
    applyDamage(p1, overflowToP1, redToP1);
    applyDamage(p2, overflowToP2, redToP2);

    // 延后结算（苍苍）：免伤已移除，必中
    applyDamage(p1, snap.delayed2.total(), 0);
    applyDamage(p2, snap.delayed1.total(), 0);

    // 灵（antiRepeater）赋予：仅当该点伤害造成对方实际生命扣减
    if (snap.pendingAR1 && p2.heart < snap.h2)
        p2.antiRepeater = true;
    if (snap.pendingAR2 && p1.heart < snap.h1)
        p1.antiRepeater = true;
}

// 一个回合的结算：双方同时出招
void roundCal(player& p1, int a1id, int shuang1, player& p2, int a2id, int shuang2,
              const map<int, action>& content, int round, const RoundSnapshot& prev, RoundSnapshot& cur)
{
    const action* a1 = findAction(a1id, content);
    const action* a2 = findAction(a2id, content);
    const action* prev1 = findAction(p1.lastActionId, content);   // p1 上一回合招式
    const action* prev2 = findAction(p2.lastActionId, content);   // p2 上一回合招式

    RoundContext ctx1;   // p1 本回合上下文
    RoundContext ctx2;   // p2 本回合上下文
    ctx1.round = round;
    ctx2.round = round;
    ctx1.opponentAction = a2;
    ctx1.opponentPreviousAction = prev2;
    ctx1.userPreviousAction = prev1;
    ctx2.opponentAction = a1;
    ctx2.opponentPreviousAction = prev1;
    ctx2.userPreviousAction = prev2;
    ctx1.shuangCount = shuang1;
    ctx2.shuangCount = shuang2;

    // ---- 1) 校验主招式（违规 → 生命归 0，招式无效；不扣费，扣费见步骤 3.8）----
    bool ok1 = a1 ? validateMain(*a1, p1, ctx1) : false;
    bool ok2 = a2 ? validateMain(*a2, p2, ctx2) : false;

    // 招式本回合是否「生效」（采采在 round < minRound 时被封印：效果取消、非违规、不触发防御）
    bool active1 = a1 ? (round >= a1->minRound) : false;
    bool active2 = a2 ? (round >= a2->minRound) : false;

    // ---- 2) 特异性防御（双方均有效、且被防招式本回合生效时才触发）----
    if (ok1 && ok2)
    {
        if (a1->defendAgainst && a1->defendAgainst == a2->id && active2)
        {
            ctx2.effectsCancelled = true;
            p1.valCuiwei += 1;
            if (a2->id == 109 || a2->id == 209)   // 防采采/防苍苍成功 → 获得「灵」（antiRepeater）
                p1.antiRepeater = true;
        }
        if (a2->defendAgainst && a2->defendAgainst == a1->id && active1)
        {
            ctx1.effectsCancelled = true;
            p2.valCuiwei += 1;
            if (a1->id == 109 || a1->id == 209)
                p2.antiRepeater = true;
        }
        // 防为霜：取消对方任意多个「为霜」（不消耗回合的锋伤害）
        if (a1->defendAgainst == 910 && ctx2.shuangCount > 0)
        {
            ctx2.shuangCancelled = true;
            p1.valCuiwei += 1;
        }
        if (a2->defendAgainst == 910 && ctx1.shuangCount > 0)
        {
            ctx1.shuangCancelled = true;
            p2.valCuiwei += 1;
        }
    }

    // ---- 3) 时间旅行（溯洄）：重新结算上一回合 ----
    // 溯洄本回合生效且未被防溯洄取消时，令上一回合重新结算，追加锋伤害（参与叠加/相抵/免伤）
    int rewind1 = (a1 && ok1 && active1 && !ctx1.effectsCancelled) ? a1->rewindSharp : 0;
    int rewind2 = (a2 && ok2 && active2 && !ctx2.effectsCancelled) ? a2->rewindSharp : 0;
    if (rewind1 > 0 || rewind2 > 0)
    {
        rewindRound(p1, p2, prev, rewind1, rewind2);
        // 重新结算只重跑上一回合的伤害；当前回合的违规（生命归 0）仍须保留
        if (!ok1) p1.heart = 0;
        if (!ok2) p2.heart = 0;
    }

    // ---- 3.5) 重算后的死亡判定：若上一回合的重算已造成击杀，本回合立即结束，不再进入正常结算 ----
    if (p1.heart == 0 || p2.heart == 0)
    {
        p1.lastActionId = a1id;
        p2.lastActionId = a2id;
        cur.valid = false;
        return;
    }

    // ---- 3.7) 为霜盾校验（时间旅行之后：重算可能打掉盾，导致盾不足 → 违规）----
    // 盾不足即违规：生命归 0，主招式与为霜都无效，费用（资源与盾）均不扣
    if (ok1 && p1.shield < ctx1.shuangCount)
    {
        p1.heart = 0;
        ok1 = false;
    }
    if (ok2 && p2.shield < ctx2.shuangCount)
    {
        p2.heart = 0;
        ok2 = false;
    }

    // ---- 3.8) 扣费（主费用 + 为霜盾；违规者不扣费）----
    if (ok1) payCost(*a1, p1, ctx1);
    if (ok2) payCost(*a2, p2, ctx2);

    // ---- 4) 执行效果（违规/被封印/被防御取消的招式跳过；花费照常）----
    if (a1 && ok1 && active1) runEffects(*a1, p1, p2, ctx1);
    if (a2 && ok2 && active2) runEffects(*a2, p2, p1, ctx2);

    // ---- 4.5) 为霜：不消耗回合，每 1 次为霜 = 1 点锋伤害（同源叠加；被防为霜取消则跳过）----
    if (ok1 && !ctx1.shuangCancelled && ctx1.shuangCount > 0)
        ctx1.damageOut.sharp += ctx1.shuangCount;
    if (ok2 && !ctx2.shuangCancelled && ctx2.shuangCount > 0)
        ctx2.damageOut.sharp += ctx2.shuangCount;

    int h1 = p1.heart;   // 记录伤害结算前血量，用于判断「是否实际扣血」
    int h2 = p2.heart;

    // 构建本回合快照（供下回合溯洄重新结算使用）：记录伤害结算前的完整局面
    cur.valid = true;
    cur.h1 = h1;
    cur.h2 = h2;
    cur.ar1 = p1.antiRepeater;
    cur.ar2 = p2.antiRepeater;
    cur.shield1 = p1.shield;
    cur.shield2 = p2.shield;
    cur.dmg1 = ctx1.damageOut;
    cur.dmg2 = ctx2.damageOut;
    cur.suyou1 = p1.suyouNow;
    cur.suyou2 = p2.suyouNow;
    cur.red1 = ctx1.reduction;
    cur.weak1 = ctx1.weakReduction;
    cur.red2 = ctx2.reduction;
    cur.weak2 = ctx2.weakReduction;
    cur.delayed1 = ctx1.delayedOut;
    cur.delayed2 = ctx2.delayedOut;
    cur.pendingAR1 = ctx1.pendingAntiRepeater;
    cur.pendingAR2 = ctx2.pendingAntiRepeater;

    // ---- 1) 同来源多段伤害叠加：招式伤害 + 上回合溯游锋伤害 ----
    DamageSummary s1 = summarizeDamage(ctx1.damageOut, p1.suyouNow);
    DamageSummary s2 = summarizeDamage(ctx2.damageOut, p2.suyouNow);

    // ---- 2) 双方伤害相抵：高的一方对另一方造成溢出伤害，溢出类型 = 高的一方总体类型 ----
    int overflowToP1 = 0;
    int overflowToP2 = 0;
    DamageType typeToP1 = DamageType::Normal;
    DamageType typeToP2 = DamageType::Normal;
    if (s1.amount > s2.amount)
    {
        overflowToP2 = s1.amount - s2.amount;
        typeToP2 = s1.type();
    }
    else if (s2.amount > s1.amount)
    {
        overflowToP1 = s2.amount - s1.amount;
        typeToP1 = s2.type();
    }

    // ---- 3.5) 蓁蓁：受到非锋溢出伤害时，每 1 点获得 1 个对应资源（抵算后、免伤前）----
    if (a1 && ok1 && active1 && !ctx1.effectsCancelled && a1->overflowGainType > 0
        && a1->overflowGainType <= 8 && overflowToP1 > 0 && typeToP1 == DamageType::Normal)
        p1.resources[a1->overflowGainType - 1] += overflowToP1;
    if (a2 && ok2 && active2 && !ctx2.effectsCancelled && a2->overflowGainType > 0
        && a2->overflowGainType <= 8 && overflowToP2 > 0 && typeToP2 == DamageType::Normal)
        p2.resources[a2->overflowGainType - 1] += overflowToP2;

    // ---- 3) 免伤结算：锋溢出 → 弱免伤无效；否则弱免伤 + 正常免伤 ----
    applyDamage(p1, overflowToP1, effectiveReduction(ctx1, typeToP1));
    applyDamage(p2, overflowToP2, effectiveReduction(ctx2, typeToP2));

    // ---- 5) 延后结算的伤害（苍苍）：所有其它效果之后，免伤已移除，必中 ----
    applyDamage(p1, ctx2.delayedOut.total(), 0);
    applyDamage(p2, ctx1.delayedOut.total(), 0);

    // ---- 6) 采采/苍苍的 antiRepeater 赋予：仅当该点伤害造成对方实际生命扣减 ----
    if (ctx1.pendingAntiRepeater && p2.heart < h2)
        p2.antiRepeater = true;
    if (ctx2.pendingAntiRepeater && p1.heart < h1)
        p1.antiRepeater = true;

    // ---- 7) 更新跨回合状态 ----
    p1.lastActionId = a1id;
    p2.lastActionId = a2id;
    p1.suyouNow = ctx1.suyouPlaced;   // 本回合放置的溯游标记，下回合生效
    p2.suyouNow = ctx2.suyouPlaced;
}

// ---------------------------------------------------------------------------
// 招式注册表：以后加新招式，在这里加一行即可
// ---------------------------------------------------------------------------
map<int, action> buildActions()
{
    map<int, action> content;
    // 获得1个基础资源"芣苢"（基础资源招式 basic=true）
    content.emplace(100, action(100, 1, noCost(),     false, false, true,  { gainResource(1, 1) }));
    // 消耗1个芣苢，造成1点伤害
    content.emplace(101, action(101, 1, costOf(1, 1), false, true,  false, { dealDamage(1) }));
    // 消耗2个芣苢，造成2点伤害
    content.emplace(102, action(102, 1, costOf(1, 2), false, true,  false, { dealDamage(2) }));
    // 消耗3个芣苢，造成3点伤害
    content.emplace(103, action(103, 1, costOf(1, 3), false, true,  false, { dealDamage(3) }));
    // 无消耗，本回合获得2点正常免伤
    content.emplace(900, action(900, 0, noCost(),     false, false, false, { addReduction(2) }));
    // 空招式：无任何花费，无任何效果
    content.emplace(1000, action(1000, 0, noCost(),   false, false, false, {}));
    // 为霜(910)：无派系，指定目标，非重章叠唱，非基础；不消耗回合（由纸带 * 后缀触发，非纸带招式）。
    // 每 1 次消耗 1 个盾、对目标造成 1 点锋伤害；一回合可多次使用（同源叠加）。实际结算见 roundCal。
    content.emplace(910, action(910, 0, noCost(), false, true, false, {}));
    // 采采：无消耗，芣苢系，重章叠唱，有目标指定；克制基础资源招式；第5回合起才生效
    content.emplace(109, action(109, 1, noCost(),     true,  true,  false, { caicaiEffect() }, 0, 5));
    // 苍苍：无消耗，蒹葭系，重章叠唱，有目标指定；克制连续两回合使用薄言的玩家
    content.emplace(209, action(209, 2, noCost(),     true,  true,  false, { cangcangEffect() }));
    // 蒹葭：无消耗，蒹葭系，基础资源招式；获得1个蒹葭（资源第2位）
    content.emplace(200, action(200, 2, noCost(),     false, false, true,  { gainResource(2, 1) }));
    // 桃夭：无消耗，桃夭系，基础资源招式；获得1个桃夭（资源第3位），若生命为1且shield为0再获得1点弱免伤
    content.emplace(300, action(300, 3, noCost(),     false, false, true,  { gainResource(3, 1), taoyaoEffect() }));
    // 桃之夭夭：消耗1个桃夭，桃夭系，非重章叠唱，不指定目标；本回合获得15点正常免伤
    content.emplace(301, action(301, 3, costOf(3, 1), false, false, false, { addReduction(15) }));
    // 灼华：消耗2个桃夭，桃夭系，非重章叠唱，不指定目标；对所有敌方玩家造成1点普通伤害
    //（1v1 中即对对手造成1点；不指定目标 → 无对应防X，可出其不意）
    content.emplace(302, action(302, 3, costOf(3, 2), false, false, false, { dealDamage(1) }));
    // 灼灼其华：消耗2个桃夭，桃夭系，非重章叠唱，指定目标；对指定目标造成2点、对其他敌方玩家造成1点。
    // 等价于「灼华 effect（全体1点）+ 采 effect（目标1点）」的叠加，1v1 中即对对手造成2点普通伤害。
    content.emplace(303, action(303, 3, costOf(3, 2), false, true,  false, { dealDamage(1), dealDamage(1) }));
    // 溯游：消耗1个蒹葭，蒹葭系，指定目标，非重章叠唱；本回合获得1点免伤，并放置溯游标记
    //（下回合对对方造成1点锋伤害）；这两项效果都可被防溯游取消
    content.emplace(201, action(201, 2, costOf(2, 1), false, true,  false, { addReduction(1), suyouEffect() }));
    // 溯洄：消耗3个蒹葭，蒹葭系，指定目标，非重章叠唱；令上一回合重新结算
    //（追加1点锋伤害参与上一回合的叠加/相抵/免伤），本回合获得3点免伤
    content.emplace(203, action(203, 2, costOf(2, 3), false, true,  false, { addReduction(3) }, 0, 1, 1));
    // 白露(202)：消耗2个蒹葭，蒹葭系，不指定目标，非重章叠唱；本回合获得2点免伤，再获得1个盾。
    // 盾在当回合伤害结算前获得（执行效果阶段，先于伤害结算），受到伤害时优先用盾抵挡。
    content.emplace(202, action(202, 2, costOf(2, 2), false, false, false, { addReduction(2), gainShield(1) }));

    // 式微系统：式微·芣苢(104)/式微·蒹葭(204)/式微·桃夭(304)
    // 非重章叠唱、非基础、指定目标，消耗1个对应资源；触发条件见 shiweiEffect 注释。
    // 式微·蒹葭额外提供本回合1点正常免伤（消耗 n 蒹葭的招式通常附带 n 点免伤）。
    content.emplace(104, action(104, 1, costOf(1, 1), false, true, false, { shiweiEffect(1) }));
    content.emplace(204, action(204, 2, costOf(2, 1), false, true, false, { addReduction(1), shiweiEffect(2) }));
    content.emplace(304, action(304, 3, costOf(3, 1), false, true, false, { shiweiEffect(3) }));

    // 蓁蓁(309)：桃夭系，重章叠唱，不指定目标，非基础，无消耗；获得 1 点弱免伤；
    // 若本回合受到非锋溢出伤害（抵算后、免伤前），每 1 点获得 1 个桃夭（overflowGainType=3）。
    content.emplace(309, action(309, 3, noCost(), true, false, false, { addWeakReduction(1) }, 0, 1, 0, 3));

    // 特异性防御「防X」：id = 1000 + 被防招式 id；无消耗，非重章叠唱，非指定目标，非基础，无派系(system=0)。
    // 若本回合被 X 指为目标且双方均有效，则取消 X 的所有效果（花费照常），自身 valCuiwei +1。
    content.emplace(1101, action(1101, 0, noCost(), false, false, false, {}, 101)); // 防采
    content.emplace(1102, action(1102, 0, noCost(), false, false, false, {}, 102)); // 防有
    content.emplace(1103, action(1103, 0, noCost(), false, false, false, {}, 103)); // 防掇
    content.emplace(1109, action(1109, 0, noCost(), false, false, false, {}, 109)); // 防采采
    content.emplace(1209, action(1209, 0, noCost(), false, false, false, {}, 209)); // 防苍苍
    content.emplace(1201, action(1201, 0, noCost(), false, false, false, {}, 201)); // 防溯游
    content.emplace(1203, action(1203, 0, noCost(), false, false, false, {}, 203)); // 防溯洄
    content.emplace(1303, action(1303, 0, noCost(), false, false, false, {}, 303)); // 防灼灼其华
    content.emplace(1104, action(1104, 0, noCost(), false, false, false, {}, 104)); // 防式微·芣苢
    content.emplace(1204, action(1204, 0, noCost(), false, false, false, {}, 204)); // 防式微·蒹葭
    content.emplace(1304, action(1304, 0, noCost(), false, false, false, {}, 304)); // 防式微·桃夭
    content.emplace(1910, action(1910, 0, noCost(), false, false, false, {}, 910)); // 防为霜（取消对方全部为霜）
    return content;
}

// 纸带条目：主招式 id + 为霜次数（为霜不消耗回合，用 * 后缀表示，如 102* = 有 + 1 次为霜）
struct TapeEntry
{
    int actionId = 0;
    int shuang = 0;
};

int main()
{
    map<int, action> actionidContent = buildActions();

    cout << "input how many actions Robot1 uses in a cycle(a number between 1 and 10):" << endl;
    int T1 = 0;
    cin >> T1;
    if (T1 <= 0 || T1 > 10)
    {
        cerr << "invalid input" << endl;
        return 1;
    }
    vector<TapeEntry> instructions1(T1);
    cout << "then input the id of each action one by one (append '*' for frost attack, e.g. 102*):" << endl;

    for (int i = 0; i < T1; i++)
    {
        string tok;
        cin >> tok;
        int actionid = -1;
        int shuang = 0;
        size_t starPos = tok.find('*');
        if (starPos != string::npos)
        {
            actionid = stoi(tok.substr(0, starPos));
            shuang = (int)tok.size() - (int)starPos;
        }
        else
        {
            actionid = stoi(tok);
        }
        if (!actionExists(actionid, actionidContent))
        {
            cerr << "such action does not exist" << endl;
            return 1;
        }
        instructions1[i] = TapeEntry{ actionid, shuang };
    }

    cout << "input how many actions Robot2 uses in a cycle(a number between 1 and 10):" << endl;
    int T2 = 0;
    cin >> T2;
    if (T2 <= 0 || T2 > 10)
    {
        cerr << "invalid input" << endl;
        return 1;
    }
    vector<TapeEntry> instructions2(T2);
    cout << "then input the id of each action one by one (append '*' for frost attack, e.g. 102*):" << endl;
    for (int i = 0; i < T2; i++)
    {
        string tok;
        cin >> tok;
        int actionid = -1;
        int shuang = 0;
        size_t starPos = tok.find('*');
        if (starPos != string::npos)
        {
            actionid = stoi(tok.substr(0, starPos));
            shuang = (int)tok.size() - (int)starPos;
        }
        else
        {
            actionid = stoi(tok);
        }
        if (!actionExists(actionid, actionidContent))
        {
            cerr << "such action does not exist" << endl;
            return 1;
        }
        instructions2[i] = TapeEntry{ actionid, shuang };
    }

    player p1;
    player p2;

    RoundSnapshot snap;   // 上一回合伤害结算快照（供溯洄重新结算使用）

    for (int i = 0; i < 10 * T1 * T2; i++)
    {
        TapeEntry e1 = instructions1[i % T1];
        TapeEntry e2 = instructions2[i % T2];
        roundCal(p1, e1.actionId, e1.shuang, p2, e2.actionId, e2.shuang, actionidContent, i + 1, snap, snap);
        if (p1.heart == 0)
        {
            if (p2.heart == 0)
            {
                cout << "Dual! Game ends at round " << i + 1 << endl;
                return 0;
            }
            else
            {
                cout << "Robot2 wins! Game ends at round " << i + 1 << endl;
                return 0;
            }
        }
        else if (p2.heart == 0)
        {
            cout << "Robot1 wins! Game ends at round " << i + 1 << endl;
            return 0;
        }
    }
    cout << "Dual! Game does not end after " << 10 * T1 * T2 << " rounds, which indicates that the game may never end.";
    return 0;
}
