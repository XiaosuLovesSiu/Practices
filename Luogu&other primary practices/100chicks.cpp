#include <iostream>
using namespace std;
int main() 
{
    int pSmall = 0,pFemale = 0,pMale = 0,nSmall = 0,nFemale = 0,nMale = 0;
    for(;pSmall<=33;pSmall++)
    {
        nSmall = 3*pSmall;
        for(nFemale=0;nFemale<=100-nSmall;nFemale++)
        {
            pFemale = 3*nFemale;
            nMale = 100 - nSmall - nFemale;
            pMale = 5*nMale;
            if(pSmall+pFemale+pMale==100)
            {
                cout << "pSmall: " << pSmall << ", pFemale: " << pFemale << ", pMale: " << pMale << endl;
                cout << "nSmall: " << nSmall << ", nFemale: " << nFemale << ", nMale: " << nMale << endl;
            }


        }
    }
    cout << "End of program" << endl;
    return 0;
}