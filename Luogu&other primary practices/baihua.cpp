#include <iostream>
#include <cmath>
#include <bitset>
using namespace std;
/*unsigned long long planAmount(int flowertypes, int floweramounts,int *point)
{
    unsigned long long result=0;
    int *temp=point;
    if(flowertypes==1)
    {
        if(floweramounts>*point||floweramounts<0)
            return 0;
        else
            return 1;
    }
    else
    {
        for(int pl = 0;pl<=*point;pl++)
        {
            *point=0;
            point++;
            result+=(planAmount(flowertypes-1,floweramounts-pl,point))%1000007;
        }
    }
    return result%1000007;
}
    */
int rmb[105][105];
unsigned long long planAmount(int flowertypes, int floweramounts, int* point)
{
    if (floweramounts < 0) return 0;
    if (flowertypes == 1)
    {
        if (floweramounts <= *point)
            return 1;
        else
            return 0;
    }
    if(rmb[flowertypes][floweramounts]) return rmb[flowertypes][floweramounts];
    unsigned long long result = 0;
    int maxForThisType = *point;  // 先保存当前类型的上限
    
    for (int pl = 0; pl <= maxForThisType; pl++)
    {
        // 注意：递归时传入 point+1，而不是修改 point 本身
        result = (result + planAmount(flowertypes - 1, floweramounts - pl, point + 1)) % 1000007;
        rmb[flowertypes][floweramounts]=result;
    }
    return result % 1000007;
}
int main()
{
    int fType=0,fAmount=0;
    cin >> fType >> fAmount;
    int fmaxn[fType];
    for(int i=0;i<fType;i++)
    {
        cin >> fmaxn[i];
    }
    int *p = &fmaxn[0];
    cout << planAmount(fType,fAmount,p) <<endl;
    return 0;
}