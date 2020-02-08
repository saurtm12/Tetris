/* Game15
 *
 * Class: Board
 *  Describes a two-dimensional grid for puzzle 15 with necessary functions.
 *
 * Program author
 * Name: Nghia Duc Hong
 * Student number: 292119
 * UserID: vsduho
 * E-Mail: duc.hong@tuni.fi
 * */

#include "board.hh"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

const int EMPTY = 16;
const unsigned int PRINT_WIDTH = 5;
void Board::print()
{
    for(unsigned int x = 0; x < SIZE; ++x)
    {
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        for(unsigned int y = 0; y < SIZE; ++y)
        {
            std::cout << "|" << std::setw(PRINT_WIDTH - 1);
            if(grid_.at(x).at(y) != EMPTY)
            {
                std::cout << grid_.at(x).at(y);
            }
            else
            {
//                this->empty_pos.row = x;
//                this->empty_pos.column= y;


                std::cout << ".";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}

void Board::my_shuffle( std::vector<unsigned int> &numbers, int seed)
{
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, numbers.size() - 1);
    for(unsigned int i = 0; i < numbers.size(); ++i)
    {
        unsigned int random_index = distr(randomEng);
        unsigned int temp = numbers.at(i);
        numbers.at(i) = numbers.at(random_index);
        numbers.at(random_index) = temp;
    }
}
void Board::add_element_togrid(std::vector <unsigned int> numbers)
{
    int temp=0;
    for (int i =0; i < SIZE;i++)
    {
        std::vector < unsigned int> temp_vector(0);
        for (int j =0; j < SIZE; j++)
        {
            temp_vector.push_back(numbers[temp++]);
        }
        grid_.push_back(temp_vector);
    }
}



