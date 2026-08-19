#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    char piece1[150], piece2[50], piece3[50];
    char *str1,*str2,*str3;
    str1 = piece1;
    str2 = piece2;
    str3 = piece3;
    cin >> piece1 >> piece2 >> piece3;
    cout << str1 << endl;
    cout << str2 << endl;
    cout << str3 << endl;
    while(*str1 != '\0')
    {
        str1++;
    }
    while(*str2 != '\0')
    {
        *str1 = *str2;
        str1++;
        str2++;
    }
    while(*str3 != '\0')
    {
        *str1 = *str3;
        str1++;
        str3++;
    }
    *str1='\0';
    cout << piece1 << endl;
    return 0;
}