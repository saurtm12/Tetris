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
void Board::add_element_togrid(std::vector <unsigned int> numbers,
                               std::string choice , int seed )
{
    if (choice == "y")
    {
        this->my_shuffle(numbers, seed);
    }
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
bool Board::move_element(std::string command)
{
    int element_row, element_column;
    if (command==command_up)
    {
        element_row= this->empty_pos_row++ ;
        //this->empty_pos_row++;
        element_column= this->empty_pos_column;
    }
    else if (command == command_down)
    {
        element_row= this->empty_pos_row;
        this->empty_pos_row--;
        element_column= this->empty_pos_column;
    }
    else if (command == command_left)
    {
        element_row= this->empty_pos_row ;
        element_column= this->empty_pos_column ;
        this->empty_pos_column--;
    }
    else if (command == command_right)
    {
        element_row= this->empty_pos_row ;
        element_column= this->empty_pos_column ;
        this->empty_pos_column++;
    }


    if (!(element_row<4 && element_row>=0
            && element_column <4 &&element_column >=0))
    {

        return 0;
    }
    else
    {
        grid_.at(element_row).at(element_column) = grid_.at(empty_pos_row).at(empty_pos_column);
        grid_.at(empty_pos_row).at(empty_pos_column)= EMPTY;
        return 1;
    }
}
int Board::initialize_empty_pointer()
{
    for (int i =0; i < SIZE; i++)
        for (int j =0; j<SIZE; j++)
        {
            if (grid_.at(i).at(j) == EMPTY)
            {
                this->empty_pos_row = i;
                this-> empty_pos_column = j;
                return 0;
            }
        }
    return 1;
}
int Board::check_solvability()
    {

    while ( this->empty_pos_row < SIZE-1)
    {
        this->move_element(command_up);
    }

    std::vector < unsigned int > temp_vector;
    for (unsigned int i=0; i<SIZE; i++)
        for (unsigned int j = 0; j<SIZE; j++){
            unsigned int temp_int = this->grid_.at(i).at(j);
            if (temp_int != 16)
                temp_vector.push_back(temp_int);
        }
    unsigned int inversion=0;
    for (unsigned int i=0; i<temp_vector.size()-1; i++)
        for (unsigned int j = i+1; j<temp_vector.size(); j++)
        {
            if (temp_vector[i]>temp_vector[j])
                inversion++;
        }
    return inversion % 2 == 0;
}


