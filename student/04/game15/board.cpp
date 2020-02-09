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

/*initializing by reading the choice of user and
 *  check if it is a valid choice
*/
bool Board::initializing_board()
{

    // Select random choice of the user
    std::string random_choice;

    //reading the choice from user, only stop when it is a valid choice
    while (true)
    {
        std::cout << "Random initialization (y/n): ";
        std::getline(std::cin, random_choice);
        if (random_choice == no_command || random_choice == yes_command
             || random_choice == NO_command || random_choice == YES_command )
            break;
        else
            std::cout<< "Unknown choice: "+random_choice<<"\n";
    }

    // initialize a vector that we can use it to intialize grid's values
    std::vector <unsigned int> numbers;

    //proceed storing by that vector, proceed result can be right/wrong
    int proceed_result = this->proceed_choice(numbers,random_choice);
    if (proceed_result ==0)
            return 0;

    //when initializing successful, initializing the EMPTY position
    //using initialize_empty_pointer() function
    this->initialize_empty_pointer();

    return 1;
}

/*proceed randomization choice
*/
bool Board::proceed_choice(std::vector <unsigned int> &numbers
                           , std::string choice)
{
    //consider if user want to randomize
    if (choice == yes_command || choice == YES_command)
    {
            std::string seed_;
            std::cout<<"Enter a seed value (or an empty line): ";
            std::getline(std::cin,seed_);

            //reading seed.
            int seed;
            if (seed_ != "")
                seed = std::stoi(seed_);
            else
                seed = (time (NULL) );

            //initializing a vector that has 1-15 elements
            for (int i=0; i < SIZE*SIZE  ; i++)
            {
                numbers.push_back(i+1);
            }

            //adding element to grid from 1-d vector to 2-d vector
            this->add_element_togrid(numbers, yes_command, seed );
            return 1;

    }
    else
    {
        //if the elements are given by user
        std::cout<< "Enter the numbers 1-16 "
                    "in a desired order (16 means empty):\n";
        for (int i=0; i<SIZE; i++)
            for (int j =0; j<SIZE; j++)
                {
                    int temp;
                    std::cin >>temp;
                    numbers.push_back(temp);
                }
        //skip the line including numbers.
        std::string empty_string;
        std::getline(std::cin,empty_string);

        /*check if the given elements are valid by using
        an additional array that has elements are 1 if
        the index is in the array and 0 if the index is not
        in the vector
         */
        int test[SIZE*SIZE+1]={0};
        for (unsigned int i = 0; i<numbers.size(); i++)
            if (numbers[i]>=1 && numbers[i]<= SIZE*SIZE)
            test[numbers[i]] = 1;

        for (unsigned int i = 1; i <= numbers.size(); i++)
        {
            if ( test[i] != 1)
            {   //if the inputs are not valid, return the
                //result of initializing is 0 (false)
                std::cout<< "Number "<<i<<" is missing";
                return 0;
            }
        }
        // if initializing successfully, add elements to 2-d vector
        this->add_element_togrid(numbers);
        return 1;
    }


}
//print board, is given in template
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

// shuffle the initial vector, given in template
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

// randomize vector if needed, then convert to grid
void Board::add_element_togrid(std::vector <unsigned int> numbers,
                               std::string choice , int seed )
{
    //proceed randomize
    if (choice == yes_command || choice == YES_command)
    {
        this->my_shuffle(numbers, seed);
    }
    int temp=0;
    for (int i =0; i < SIZE;i++)
    {
        //initialize an empty vector then add 4 elements
        std::vector < unsigned int> temp_vector(0);
        for (int j =0; j < SIZE; j++)
        {
            temp_vector.push_back(numbers[temp++]);
        }
        //push this 1d vector into 2-d vector
        grid_.push_back(temp_vector);
    }
}

bool Board::move_element(std::string command,unsigned int compare)
{
    /*initialize temporary variables needed, element is
     * the one that has a valid values != 16 and
     * TEMP_empty_pos are variiables store current
     * EMPTY position
    */
    int element_row=0, element_column=0;
    int TEMP_empty_pos_row= this->empty_pos_row
            ,TEMP_empty_pos_column=this->empty_pos_column;
    //check the valid element need to swap
    if (command==command_up)
    {
        element_row= TEMP_empty_pos_row++ ;
        element_column= TEMP_empty_pos_column;
    }
    else if (command == command_down)
    {
        element_row= TEMP_empty_pos_row--;
        element_column= TEMP_empty_pos_column;
    }
    else if (command == command_left)
    {
        element_row= TEMP_empty_pos_row ;
        element_column= TEMP_empty_pos_column++ ;
    }
    else if (command == command_right)
    {
        element_row= TEMP_empty_pos_row ;
        element_column= TEMP_empty_pos_column-- ;
    }

    //check if the range is beyond the boundary, if the range
    //is outside boundary, abort moving
    if (!(TEMP_empty_pos_row<SIZE && TEMP_empty_pos_row>=0
            && TEMP_empty_pos_column <SIZE && TEMP_empty_pos_column >=0))
    {

        return 0;
    }
    else
    {
        //if the compare value is not identical, then abort swaping
        if (compare != 0  &&
                grid_.at(TEMP_empty_pos_row)
                .at(TEMP_empty_pos_column) != compare)
            return 0;
        //if all condition satisfy, proceed swaping and changing EMPTY position
        grid_.at(element_row).at(element_column)
                = grid_.at(TEMP_empty_pos_row).at(TEMP_empty_pos_column);
        grid_.at(TEMP_empty_pos_row).at(TEMP_empty_pos_column)= EMPTY;
        this->empty_pos_row = TEMP_empty_pos_row;
        this->empty_pos_column = TEMP_empty_pos_column;
        return 1;
    }
}

//find the first position of the pointer by
//considering the grid
int Board::initialize_empty_pointer()
{
    for (int i =0; i < SIZE; i++)
        for (int j =0; j<SIZE; j++)
        {
            if (grid_.at(i).at(j) == EMPTY)
            {
                this->empty_pos_row = i;
                this->empty_pos_column = j;
                return 0;
            }
        }
    return 1;
}

//check if the game is solvable
int Board::check_solvability()
    {
    //first move the EMPTY to bottom row.
    while ( this->empty_pos_row < SIZE-1)
    {
        this->move_element(command_up);
    }
    // create a vector include all the elements exclude EMPTY
    std::vector < unsigned int > temp_vector;
    for (unsigned int i=0; i<SIZE; i++)
        for (unsigned int j = 0; j<SIZE; j++){
            unsigned int temp_int = this->grid_.at(i).at(j);
            if (temp_int != EMPTY)
                temp_vector.push_back(temp_int);
        }

    //counting inversion
    unsigned int inversion=0;
    for (unsigned int i=0; i<temp_vector.size()-1; i++)
        for (unsigned int j = i+1; j<temp_vector.size(); j++)
        {
            if (temp_vector[i]>temp_vector[j])
                inversion++;
        }
    //return the solvability. Even - solvable, if not, not solvable
    return inversion % 2 == 0;
}

//check if we win
bool Board::is_won()
{   //create a temporary vector store elements
    std::vector <unsigned int > temp_vector;
    for (unsigned int i=0; i<SIZE; i++)
        for (unsigned int j = 0; j<SIZE; j++)
        {
                temp_vector.push_back(grid_.at(i).at(j));
        }
    //check if all elements is in the right position
    for (unsigned int i=0; i <temp_vector.size();i++)
    {
        unsigned int temp = i+1;
        if ( temp != temp_vector[i])
            return 0;
    }
    return 1;
}


