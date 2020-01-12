#include <iostream>

using namespace std;

int main()
{
    int num;
    cout << "How many numbers would you like to have? ";
    cin>> num;
    for (int i=1; i<=num; i++)
    {
        if ((i%3==0) &&(i%7==0))
        {
            cout<< endl <<"zip"<<endl <<"boing";
        }
            else
        {
            if (i%3 ==0)
            {
                cout <<endl<<"zip";
            } else
                {
                       if (i%7 ==0)
                {
                       cout << endl << "boing";
            }else
                       {
                           cout<<endl<<i;
                       }

            }

        }
    }
    return 0;
}
