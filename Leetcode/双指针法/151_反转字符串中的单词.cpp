#include <vector>
#include <string>
using namespace std;

//法一：使用一个矩阵记录单词，逆序输出；空间复杂度高。
class Solution {
public:
    string reverseWords(string s) {
        vector<string> matrix;
        int i=0,count=0,w=s.size()-1;
        while(s[i]==' ') i++;
        while(s[w]==' ') w--;
        matrix.push_back("");
        while(i<=w)
        {
            if(s[i]!=' ')
            {
                matrix[count].push_back(s[i]);
                i++;
            }
            else
            {
                count++;
                matrix.push_back("");
                while(s[i]==' ') i++;
            }
        }
        string rstr="";
        for(;count>=1;count--)
        {
            rstr.append(matrix[count]);
            rstr.push_back(' ');
        }
        rstr.append(matrix[0]);
        return rstr;
    }
};

//方法二：O(1)空间复杂度，先去掉多余空格，再逆序整个字符串，最后逆序每个单词。
void MyReverse(string& s,int start,int end)//闭区间内翻转
{
    while(start<end)
    {
        char temp=s[start];
        s[start]=s[end];
        s[end]=temp;
        start++;
        end--;
    }
}
void MyClear(string& s)
{
    int i=0,process=0;
    while(i<s.size())
    {
        if(s[i]!=' ')
        {
            s[process]=s[i];
            i++;
            process++;
        }
        else
        {
            if(i==s.size()-1||s[i+1]==' ') i++;
            else
            {
                s[process]=' ';
                i++;
                process++;
            }
        }
    }
    s.erase(s.begin()+process,s.end());
    int j=0;
    while(s[j]==' ') j++;
    if(j!=0) s.erase(s.begin(),s.begin()+j);
}
class Solution {
public:
    string reverseWords(string s) {
        MyClear(s);
        MyReverse(s,0,s.size()-1);
        int i=0,process=0;
        while(i<s.size())
        {
            if(s[i]==' ')
            {
                MyReverse(s,process,i-1);
                i++;
                process=i;
            }
            i++;
        }
        MyReverse(s,process,i-1);
        return s;
    }
};