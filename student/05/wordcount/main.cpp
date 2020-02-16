#include <iostream>
#include <fstream>
#include <map>
#include <vector>
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
        return EXIT_FAILURE;
    }

    map <std::string, vector <int> > words;
    std::string line;
    int n_line = 1;
    while (getline(input_file,line))
    {

        int i=0, n = line.length();
        while (i<n)
        {
            std::string word ="";
            while (i<n && line[i] != ' ')
            {
                word+= line[i++];
            }
            i++;

            if (words.find(word) != words.end())
            {
                if (find(words.at(word).begin(),words.at(word).end() , n_line) == words.at(word).end())
                    words.at(word).push_back(n_line);
            }
            else
            {
                words.insert({ word,{n_line} });
            }

       }
     n_line++;

    }

    map <std::string, vector<int>>:: iterator iter;
    vector <int> ::iterator iter_v;

    for (iter = words.begin(); iter != words.end(); iter++)
    {
        std::cout<<iter->first<<" "<<iter->second.size()<<": ";
        for  (iter_v = iter->second.begin(); iter_v  != iter->second.end(); iter_v++)
        {   if (iter_v+1 == iter->second.end())
            {
                  cout<<*iter_v<<endl;
            }
            else
            std::cout<<*iter_v<<", ";
       }

    }

    input_file.close();
    return EXIT_SUCCESS;

}
