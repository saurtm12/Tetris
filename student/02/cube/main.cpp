#include <iostream>
using namespace std;

int main()
{
    int n;
    cout <<"Enter a number: ";
    cin>> n;
    long temp = n;
    int cube = n*n*n;
    temp = temp*temp*temp;
    if (cube == temp)
    {
        cout << "The cube of "<< n <<" is "<< temp <<".";
    } else
    {
        cout << "the cube of " << n << " is not " << cube <<".";
    }

}
