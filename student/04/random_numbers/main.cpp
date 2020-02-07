#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper)
{
    // Implement your function here
    string line="";
    string seed_;
    cout<<"Enter a seed value or an empty line: ";
    getline(cin, seed_);
    default_random_engine gen;
    if (seed_=="")
    {
        gen.seed( time(NULL) );
    }
    else
        gen.seed(stoi(seed_));
    uniform_int_distribution<int> distr(lower, upper);

    while (line!="q")
    {
        cout<<"Your drawn random number is "<< distr(gen)<<"\n";
        cout<<"Press enter to continue or q to quit:";
        getline(cin,line);
        if (line=="q")
        {
             break;
        }
    }
}

int main()
{
    unsigned int lower_bound, upper_bound;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    // Reading the line feed, which was left unread by >> operator above.
    // This is necessary since the seed value will be read by getline
    // in the function produce_random_numbers.
    string line_feed = "";
    getline(cin, line_feed);

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound" << endl;
        return EXIT_FAILURE;
    }

    produce_random_numbers(lower_bound, upper_bound);

    return EXIT_SUCCESS;
}
