#include <iostream>
#include <cstring>
using namespace std;

// 统计原字符串中字母、数字、非字母非数字的个数
void count_chars(const char a[], int *p_letter, int *p_digit, int *p_other)
{
    for (int i = 0; i < 100; i++)
    {
        if (a[i] == '\0')
            return;
        else if (('a' <= a[i] && 'z' >= a[i]) || ('A' <= a[i] && 'Z' >= a[i]))
            (*p_letter) += 1;
        else if ('0' <= a[i] && a[i] <= '9')
            (*p_digit) += 1;
        else
            (*p_other) += 1;
    }
}

// 将小写改大写，大写保持不变，数字变为#，其他变为.
void process_chars(char a[])
{
    for (int i = 0; i < 100; i++)
    {
        if (a[i] == '\0')
            return;
        else if ('a' <= a[i] && 'z' >= a[i])
            a[i] = a[i] - 'a' + 'A';
        else if ('0' <= a[i] && a[i] <= '9')
            a[i] = '#';
        else if (!('A' <= a[i] && 'Z' >= a[i]))
            a[i] = '.';
    }
}

int main()
{
    char s[100];
    cin.getline(s, 100);

    int letters = 0, digits = 0, others = 0;
    count_chars(s, &letters, &digits, &others);

    process_chars(s);
    cout << s << endl;

    cout << "Letters: " << letters
         << ", Digits: " << digits
         << ", Others: " << others;
    return 0;
}