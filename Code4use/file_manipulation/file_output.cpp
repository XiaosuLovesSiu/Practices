#include <iostream>
#include <fstream> // 引入文件流头文件
#include <string>
using namespace std;

int main()
{
    // 1. 创建输出流，并打开文件 "test.txt"
    ofstream fout("test.txt");
    //if the file does not exist, it will be created; if it exists, it will be overwritten.

    // 2. 判断是否成功打开（好习惯！）
    if (!fout)
    {
        cerr << "fail to open file" << "(name: test.txt)" << endl;
        return 1;
    }

    // 3. 像用 cout 一样写入
    fout << "Hello, file!" << endl;
    fout << "i'm going to master these skills!" << endl;

    // 4. 关闭文件（程序结束时会自动关，但显式关闭是好习惯）
    fout.close();

    cout << "File writing completed!" << endl;
    return 0;
}