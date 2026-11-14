#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream fin("test.txt"); // 打开文件用于读取
    if (!fin)
    {
        cerr << "fail to open file" << "(name: test.txt)" << endl;
        return 1;
    }

    string line;
    // 逐行读取，直到文件结束
    while (getline(fin, line))
    {
        cout << line << endl; // 打印到屏幕
    }

    fin.close();
    return 0;
}