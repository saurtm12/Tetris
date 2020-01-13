#include <iostream>
using namespace std;

int main()
{
    int n;
    float mean = 0;
    cout << "From how many integer numbers you want to count the mean value? ";
    cin >>n;
    if (n==0)
    {
        cout <<"Cannot count mean value from 0 numbers";
        return 0;
    }
    for (int i = 1; i<=n;i++)
    {
        cout <<"Input "<< i <<". number: ";
        int input;
        cin >>input;
        mean += input;
    }
    mean = mean/n;
    cout << "Mean value of the given numbers is " << mean;
    return 0;

}
