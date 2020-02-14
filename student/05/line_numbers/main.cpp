#include <iostream>
#include <fstream>
#include <vector>
int main()
{
    std::string input_fname, output_fname;
    std::cout << "Input file: ";
    getline(std::cin, input_fname);
    std::cout<< "Output file: ";
    getline(std::cin, output_fname);
    std::ifstream input(input_fname);
    if (!input)
    {
        std::cout<<"Error! The file "<<input_fname<<" cannot be opened.";
        return EXIT_FAILURE;
    }
    std::vector <std::string> str_vector;
    std::string temp_string;
    while (getline(input, temp_string))
    {
        str_vector.push_back(temp_string);
    }
    std::ofstream output(output_fname);
    unsigned int i = 1, n = str_vector.size();
    while (i<= n)
    {
        output <<i<<" "<<str_vector[i-1]<<"\n";
        i++;
    }
    input.close();
    output.close();
    return 0;
}
