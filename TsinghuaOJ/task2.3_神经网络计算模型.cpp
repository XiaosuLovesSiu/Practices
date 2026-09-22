//待完成

#include <vector>
#include <cmath>
using namespace std;

double sigmoid(double x)
{
    return 1.0/(1.0+exp(-x));
}


int main()
{
    vector<double> inputs={0.5,10.2,0.8,1.0,-0.7};
    vector<double> weights={0.1,0.2,-0.1,0.3,0.05};


    return 0;
}