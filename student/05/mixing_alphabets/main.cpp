#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <time.h>
#include <vector>
#include <chrono>
int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;
    generator.seed(time(NULL));
    std:: uniform_int_distribution<int> distr(1, 100);
    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;

    while (std::cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }
        std::vector <char> v={};
        for (auto chr: word)
            {
            v.push_back(chr);
            }

      shuffle(v.begin()+1,v.end()-1,generator);
        std::string result="";
        for (auto chr: v)
            {
            result +=chr;
            }

        std::cout << result << std::endl;
    }
}
