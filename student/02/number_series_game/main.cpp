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
        {   if (i<=20) {
            cout<<"zip"<<endl <<"boing"<<endl;}
            else {
                cout << "zip boing"<<endl;
            }
        }
            else
        {
            if (i%3 ==0)
            {
                cout <<"zip"<<endl;
            } else
                {
                       if (i%7 ==0)
                {
                       cout << "boing"<< endl ;
            }else
                       {
                           cout<<i<<endl;
                       }

            }

        }
    }
    return 0;
}
