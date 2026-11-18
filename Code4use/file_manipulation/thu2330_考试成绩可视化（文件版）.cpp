// thu2330_考试成绩可视化（文件版）
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    ifstream fin("input.txt");
    if(!fin)
    {
        cerr << "unable to open file input.txt" << endl;
        return 1;
    }
    string line;
    string call;
    int score;
    vector<int> count(10,0); //count[i]代表区间10i到10i+10

    while(fin >> call >> score)
    {
        if(score >= 100) count[9]++;
        else count[score / 10]++;
    }
    fin.close();

    ofstream fout("output.txt");
    if(!fout)
    {
        cerr << "unable to open file output.txt" << endl;
        return 1;
    }

    for(int i=0;i<=9;i++)
    {
        for(int j=0;j<=9;j++)
        {
            if(j < count[i]) fout << '@';
            else fout << '.';
        }
        fout << endl;
    }

    return 0;
}