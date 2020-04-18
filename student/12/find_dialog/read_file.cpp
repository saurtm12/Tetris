#include <iostream>
#include <fstream>
#include <algorithm>
const std::string FNOT_FOUND = "File not found",
             F_FOUND = "File_found",
             WNOT_FOUND = "Word not found",
             W_FOUND = "Word found",
             EMPTY = "";

std::string findWord(std::string file, std::string word,bool tick)
{
    std::ifstream input(file);
    if (!input)
    {
        return FNOT_FOUND;
    }
    std::string line = "";
    if (!tick)
    {
        std::for_each(word.begin(),word.end(), [](char& c)
        {
            c = ::toupper(c);
        });
    }
    while (getline(input,line))
    {
        if (!tick)
        {
            std::for_each(line.begin(),line.end(), [](char& c)
            {
                c = ::toupper(c);
            });
        }
        std::size_t found = line.find(word);
        if (found != std::string::npos)
        {
            return W_FOUND;
        }
    }
    return WNOT_FOUND;
}
