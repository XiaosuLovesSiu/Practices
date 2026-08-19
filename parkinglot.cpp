#include <iostream>
using namespace std;
void park()
{
    static int i=0;
    i++;
    cout << "Parking lot " << 30-i << endl;
}
int main()
{
    cout << "How many cars just entered?" << endl;
    int n;
    cin >> n;
    for(int j=0; j<n; j++)
    {
        park();
    }
    return 0;
}