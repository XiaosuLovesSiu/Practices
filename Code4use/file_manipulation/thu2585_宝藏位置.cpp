#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

string extract(int loc1, int loc2, int dual, const vector<string> &ifile)
{
    string result;
    if (loc1 < 0 || loc2 < 0 || loc1 >= ifile.size() || loc2 >= ifile[loc1].size())
    {
        for (int i = 0; i < dual; i++)
        {
            result += '*';
        }
        return result;
    }
    else
    {
        for (int i = 0; i < dual; i++)
        {
            if (loc2 + i - 1 >= ifile[loc1].size())
            {
                result += '*';
            }
            else
                result += ifile[loc1][loc2 - 1 + i];
        }
    }
    return result;
}

int main()
{
    ifstream fin("clues_and_plays.txt");
    if (!fin)
    {
        cerr << "fail to open file" << "(name: clues_and_plays.txt)" << endl;
        return 1;
    }
    ofstream fout("secret_message.txt");
    if (!fout)
    {
        cerr << "fail to open file" << "(name: secret_message.txt)" << endl;
        return 1;
    }
    vector<string> ifile;
    ifile.reserve(1000);
    ifile.push_back("");

    while (!fin.eof() && ifile.size() != 1000)
    {
        string line;
        getline(fin, line);
        ifile.push_back(line);
    }

    stringstream ss0(ifile[1]);
    int N = 0;
    ss0 >> N;
    
    for (int i = 2; i <= N + 1; i++)
    {
        if (i != 2)
            fout << ' ';
        stringstream ss(ifile[i]);
        int loc1 = 0, loc2 = 0, dual = 0;
        ss >> loc1 >> loc2 >> dual;
        fout << extract(loc1, loc2, dual, ifile);
    }

    fin.close();
    fout.close();
    return 0;
}