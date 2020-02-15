#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
using namespace  std;

int main()
{
    std::string ifile_name;
    std::cout<<"Input file: ";
    getline(std::cin, ifile_name);
    std::ifstream input_file(ifile_name);
    if (!input_file)
    {
        std::cout<<"Error! The file "<<ifile_name <<" cannot be opened.";
        return 0;
    }

    map <std::string, int> score;
    std::string temp_string;
    while (getline(input_file,temp_string))
    {
        std::string name="",_score="";
        int i=0, n = temp_string.length();
        while( i< n && temp_string[i]!= ':')
        {
            name+=temp_string[i++];
        }
        i++;
        while( i < n)
            _score += temp_string[i++];

        int int_score = std::stoi(_score);
        if (score.find(name) == score.end())
            score.insert({name,int_score});
        else
        {
            score.at(name)+= int_score;
        }

    }
    map <std::string, int>:: iterator iter;
    std::cout<<"Final scores:\n";

    for (iter = score.begin(); iter != score.end();iter++)
    {
        std::cout<<iter->first<<": "<<iter->second<<"\n";
    }

    input_file.close();
    return 0;

}
