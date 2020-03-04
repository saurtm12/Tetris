#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <string>
using namespace std;

std::vector<std::string> split( const std::string& s,
                                const char delimiter,
                                bool ignore_empty )
{
    std::vector<std::string> result;
    std::string tmp = s;

    while( tmp.find(delimiter) != std::string::npos )
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(! (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if( ! (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}
int devide(int num1, int num2)
{
    if (num2 == 0)
        return -2;
    return num1/num2;
}
int check_int(string str)
{
    for (unsigned int i=0;i<str.length();i++)
    {
        if (str[i]>'9' || str[i] < '0')
        {
            return -1;
        }
    }
    return stoi(str);
}
int oper(string operate, int* num1, int* num2)
{
    if (operate == "+")
    {
        return *num1 + *num2;
    }
    if (operate == "-")
    {
        return *num1 - *num2;
    }
    if (operate == "*")
    {
        return *num1 * *num2;
    }
    if (operate == "/")
    {
        return devide(*num1,*num2);
    }
    return -1;
}

int main()
{
    cout << "Input an expression in reverse Polish notation (end with #):\n";
    cout << "EXPR> ";
    int* a = new int [80];
    string line ="";
    getline(cin, line);
    vector <string> strs = split(line,' ',true);
    int current =-1;
    for (auto str : strs)
    {
        if (str == "#")
        {
            if (current != 0)
            {
                cout<<"Error: Too few operators";
                return EXIT_FAILURE;
            }
            cout<<"Correct: "<<*a <<" is the result";
            return EXIT_SUCCESS;
        }

        int result = check_int(str);

        if (result != -1)
        {
            *(a+current+1) = result;
            current++;
        }
        else
        {
            if (current <0)
            {
                cout<<"Error: Expression must start with a number";
                return EXIT_FAILURE;
            }
            if (current <1)
            {
                cout<<"Error: Too few operands";
                return EXIT_FAILURE;
            }
            int oresult = oper(str,(a+current-1),(a+current));
            if (oresult == - 1)
            {
                cout<<"Error: Unknown character";
                return EXIT_FAILURE;
            }
            if (oresult == - 2)
            {
                cout<<"Error: Division by zero";
                return EXIT_FAILURE;
            }
            current--;
            *(a+current) = oresult;

        }

    }
    return EXIT_SUCCESS;
}
