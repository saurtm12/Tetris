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

#ifndef BOARD_HH
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
const int SIZE = 4;
const std::string no_command = "n", NO_command = "N";
const std::string yes_command = "y", YES_command = "Y";
const std::string command_up="w",
                    command_down="s",
                    command_left="a",
                    command_right="d";
class Board
{
public:
    //initializing board and reading inputs
    bool initializing_board();
    //is included in initializing that has parameter is an
    //vector used for randomization or own user's use
    // by using 2nd parameter is randomization choice
    bool proceed_choice(std::vector <unsigned int> &numbers
                        , std::string choice);
    //check if we win
    bool is_won();
    // Prints the game grid
    void print();
    //find the initial position of the EMPTY element
    int initialize_empty_pointer();


    // ADD element to grid that has a 1 dimentional vector to
    // 2 dimentional vector (grid) by command and randomization
    void add_element_togrid(std::vector <unsigned int> numbers,
                            std::string choice = no_command
            , int seed = time(NULL) );
    //move an element which uses the current position of EMPTY element
    // and based on command, parameter compare is confirm if the move
    // is right
    bool move_element(std::string command, unsigned int compare = 0);
    //check solvability
    int check_solvability();
private:
    // Shuffles the numbers vector by using seed as a seed value
    void my_shuffle(std::vector<unsigned int>& numbers, int seed);

    // Game grid for the 15 puzzle
    std::vector<std::vector<unsigned int>> grid_ ;
    //store the position of EMPTY element
    int empty_pos_row,empty_pos_column;
};

#endif // BOARD_HH
