#include <iostream>
using namespace std;

int main() {
    double celsius, fahrenheit;
    cout << "Please enter the Fahrenheit temperature: " << endl;
    cin >> fahrenheit;
    celsius = (fahrenheit - 32) * 5.0/9.0;
    if(celsius<-273.15) 
    {
        cout << "The entered Fahrenheit temperature is below absolute zero, and thus cannot be converted to Celsius." << endl;
    }
    else cout << "The Celsius temperature is: " << celsius << endl;
    return 0;
}