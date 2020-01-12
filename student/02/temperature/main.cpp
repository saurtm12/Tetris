#include <iostream>

using namespace std;

int main()
{
    int temp;
    cout << "Enter a temperature: ";
    cin >> temp;
    cout << temp <<" degrees Celsius is "<< temp*9/5+32 <<" degrees Fahrenheit"<< endl;
    cout << temp <<" degrees Fahrenheit is "<< (temp-32)/1.8  <<" degrees Celsius";
    return 0;
}
