#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream fin("test.txt");
    ofstream fout("output.txt");

    if (!fin || !fout)
    {
        cerr << "fail to open file" << endl;
        return 1;
    }

    string line;
    while (getline(fin, line))
    {
        fout << line << endl; // 读一行，写一行
    }

    cout << "File copying completed!" << endl;
    return 0;
}