#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
int main()
{
    int warenum,dim;
    cin >> warenum >> dim;
    long chart[warenum][dim];
    int result[warenum];
    memset(result,0,sizeof(result));
    for(int i=0;i<warenum;i++)
    {
        for(int j=0; j<dim; j++)  cin >> chart[i][j];
    }
    for(int k=0;k<warenum;k++)
    {
        for(int l=0;l<warenum;l++)
        {
            bool p=true;
            for(int m=0;m<dim;m++) p=p&&(chart[l][m]>chart[k][m]);
            if(p)
            {
                result[k]=l+1;
                break;
            }
        }
    }
    for(int n=0;n<warenum;n++) cout<<result[n]<<endl;
    return 0;
}