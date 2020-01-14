#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string S1;
    cout << "Enter the encryption key: ";
    cin >>S1;
    int len = S1.length();
    if (len != 26)
    {
    cout << "Error! The encryption key must contain 26 characters.";
            return 0;
    }


    for (int i=0; i<len;i++)
    {
        if (!((S1[i]>='a' && S1[i]<='z')))
        {
            cout <<"Error! The encryption key must contain only lower case characters.";
            return EXIT_FAILURE;
        }
    }


    int array[256];
    for (int i=0;i<256;i++)
    {
        array[i]=0;
    }

    for (int i =0; i<len;i++)
        array[(int)S1[i]] =1;
    int Check = 1;
    for (int i='a';i<='z';i++)
        if (array[i]==0)
        {
            Check = 0;
        }
    if (Check==0)
    {
        cout <<"Error! The encryption key must contain all alphabets a-z.";
        return EXIT_FAILURE;
    }
    for (int i='a';i<='z';i++)
    {
        array[i]=S1[i-'a'];
    }


    string S;
    cout << "Enter the text to be encrypted: ";
    cin >>S;
    int en[S.length()];
    for (int i =0;i <(int)S.length();i++)
        en[i]= S[i];
    for (int i = 0; i<(int)S.length() ; i++)
    {
        en[i]=array[(int)S[i]];
        }
    cout <<"Encrypted text: ";
    for (int i = 0; i< (int)S.length(); i++)
    {
        cout <<(char)en[i];
    }
    return 0;
}
