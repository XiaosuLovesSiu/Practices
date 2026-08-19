#include <iostream>
#include <cstring>
using namespace std;
char* reverse(char *ipt)
{
    int l=strlen(ipt);
    for(int i=0;i<l/2;i++)
    {
        int temp =ipt[i];
        ipt[i]=ipt[l-i-1];
        ipt[l-i-1]=temp;
    }
    return ipt;
}
/*int Loop(char *i1)
    {
        reverse(i1);
    if(strcmp(ipt,i1)==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
    }
int main()
{
    cin.getline(ipt,101);
    char i1[101];
    strcpy(i1, ipt);
    reverse(i1);
    if(strcmp(ipt,i1)==0)
    {
        cout<<"YES"<<endl;
    }
    else
    {
        cout<<"NO"<<endl;
    }
}*/
int Loop(char *i1)
    {
        char i2[101];
        strcpy(i2, i1);
        reverse(i2);
    if(strcmp(i1,i2)==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
    }
int main()
{
    int n=0;
    char input[101];
    cin.getline(input,101);
    char *p=input;
    //reverse(p);
    //for(int j=0;j<strlen(input);j++)
    //{
    //    cout<<i[j];
    //}
    //cout<<endl;
    while(Loop(p))
    {
        n++;
        
    }
    cout<<Loop(p)<<endl;
    return 0;
}