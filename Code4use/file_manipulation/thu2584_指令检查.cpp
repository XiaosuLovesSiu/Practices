#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

int main()
{
    ifstream fin("input.txt"); // 打开文件用于读取
    if (!fin)
    {
        cerr << "fail to open file" << "(name: input.txt)" << endl;
        return 1;
    }
    ofstream fout("output.txt"); // 打开文件用于写入
    if (!fout)
    {
        cerr << "fail to open file" << "(name: output.txt)" << endl;
        return 1;
    }
    string line;
    int areaNum, commandNum;

    fin >> areaNum >> commandNum; // 读取第一行的两个整数

    getline(fin, line); // 读取第一行后面的换行符
    getline(fin, line); // 读取第二行的字符串
    stringstream ss(line);
    map<string, int> coms; // key是命令，value是操作数
    string com;
    for (int i = 0; i < commandNum; i++)
    {
        ss >> com;
        if (com == "inbox" || com == "outbox")
        {
            coms[com] = 0;
        }
        else if (com == "jump" || com == "jumpifzero")
        {
            coms[com] = 2;
        }
        else
            coms[com] = 1;
    }

    int iptNum;
    fin >> iptNum;      // 读取第三行的整数
    getline(fin, line); // 读取第三行后面的换行符

    for (int i = 0; i < iptNum; i++)
    {
        if (i != 0)
            fout << endl;
        getline(fin, line); // 读取每一行的字符串
        if (line[line.size() - 1] == '\r')
            line.pop_back(); // 去掉行末的回车符
        stringstream sin(line);
        sin >> com; // 读取每一行的第一个字符串
        auto it = coms.find(com);
        if (it == coms.end())
        {
            fout << "Error";
        }
        else
        {
            int value = it->second;
            if (value == 0)
            {
                string str;
                if (!(sin >> str)) // 如果没有其他字符串
                    fout << "OK";
                else
                    fout << "Error";
            }
            else if (com == line)
                fout << "Error";
            else
            {
                int n;
                if(!(sin >> n))
                {
                    fout << "Error";
                    continue;
                }
                string m;
                if(sin >> m)
                {
                    fout << "Error";
                    continue;
                }
                if (value == 1)
                {
                    if (n >= 0 && n < areaNum)
                        fout << "OK";
                    else
                        fout << "Error";
                }
                else if (value == 2)
                {
                    if (n >= 1 && n <= iptNum)
                        fout << "OK";
                    else
                        fout << "Error";
                }
            }
        }
    }

    fin.close();
    fout.close();
    return 0;
}