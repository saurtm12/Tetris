#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function

std::vector < std::string > split(std::string line,char seperator,bool k=false)
{
    std::vector < std::string > strs;
    int i=0;
    int n = line.length();
    while (i<n)
    {
            std ::string temp_string="";
            while (line[i] != seperator && i <n)
            {
                temp_string += line[i];
                i++;
            }
            strs.push_back(temp_string);
            if (k)
            {
                while (line[i]==seperator)
                    i++;
            }
            else {i++;}

    }
    return strs;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
