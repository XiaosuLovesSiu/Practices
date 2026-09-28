#include <iostream>
#include <vector>
using namespace std;

struct people
{
    bool honest;
    bool murder;
};

int main()
{
    people tarpeo={false,false};
    for(int i=0;i<6;i++)
    {
        vector<people> vec(6,tarpeo);
        vec[i].murder=true;
        vec[0].honest=!vec[0].murder;
        vec[5].honest=vec[5].murder;
        vec[1].honest=vec[0].murder || vec[2].murder;
        vec[2].honest=(!vec[0].honest) && (!vec[1].honest);
        vec[3].honest=(!vec[2].honest) && (!vec[5].honest);
        vec[4].honest=(!vec[1].honest) && vec[0].honest && vec[3].honest && (!vec[2].honest) && (!vec[5].honest);
        int count=0;
        for(int j=0;j<6;j++)
        {
            count+=static_cast<int>(vec[j].honest);
        }
        if(count==3) cout << static_cast<char>(i+'A') << endl;
    }
    return 0;
}