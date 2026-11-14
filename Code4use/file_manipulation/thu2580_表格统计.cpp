#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

int transferToNum(const string &s, int l, int r)
{
    int diff = '1' - 1;
    int res = 0;
    for (int i = l; i <= r; i++)
    {
        res = res * 10 + s[i] - diff;
    }
    return res;
}

int distri(string &line, vector<int> &data)
{
    int label = 0;
    int flag = 0;
    for (; label < line.size(); label++)
    {
        if (line[label] == ',')
        {
            data.push_back(transferToNum(line, flag, label - 1));
            flag = label + 1;
        }
    }
    if(line[line.size() - 1] == '\r') line.pop_back();
    data.push_back(transferToNum(line, flag, line.size() - 1));
    return 0;
}

int main()
{
    ifstream fin("input.csv");
    ofstream fout("output.csv");
    fout << fixed << setprecision(2);
    if (!fin || !fout)
    {
        cerr << "fail to open file" << endl;
        return 1;
    }

    string line;
    vector<vector<int>> data;

    while (getline(fin, line))
    {
        data.push_back(vector<int>());
        distri(line, data[data.size() - 1]);
    }

    int subjects = data[0].size();
    for (int j = 0; j < subjects; j++)
    {
        if(j!=0) fout << endl;
        double avr = 0;
        vector<double> mid;
        double max=-1,min=101,sqsum=0;
        for (int i = 0; i < data.size(); i++)
        {
            avr += data[i][j];
            sqsum += data[i][j] * data[i][j];
            mid.push_back(data[i][j]);
            if (data[i][j] > max)
                max = data[i][j];
            if (data[i][j] < min)
                min = data[i][j];
            
        }
        avr /= data.size();
        sqsum /= data.size();
        double dsq = sqsum - avr * avr;
        sort(mid.begin(), mid.end());
        double median = 0;
        if (data.size() % 2 == 0)
        {
            median = (mid[data.size() / 2] + mid[data.size() / 2 - 1]) / 2;
        }
        else
        {
            median = mid[data.size() / 2];
        }
        fout << avr << "," << median << "," << max << "," << min << "," << dsq;
    }
    fin.close();
    fout.close();
    return 0;
}