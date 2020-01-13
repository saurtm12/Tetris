#include <iostream>

using namespace std;
float factory(int n)
{
    if (n<=1)
    {
        return 1;
    } else
        return n*factory(n-1);
}
int main()
{
    int lball,dball;
    cout <<"Enter the total number of lottery balls: ";
    cin >> lball;
    cout << "Enter the number of drawn balls: ";
    cin >> dball;
    if (lball <=0 || dball <=0)
    {
        cout << "The number of balls must be a positive number.";
        return 0;

    }
    float prob = factory(lball)/factory(dball)/factory(lball -dball);
    cout << "The probability of guessing all " << dball << " balls correctly is 1/" << (long)prob;
    return 0;
}
