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
    // For creating and initializing the grid, you have at least two choices:
    // 1. Implement a constructor that fills the game grid with empties or such
    // and two initialize methods
    // 2. Implement two constructors, one for each initialization way

    bool is_won();
    // Prints the game grid
    void print();

    int initialize_empty_pointer();
    int empty_pos_row,empty_pos_column;

    // More methods
    void add_element_togrid(std::vector <unsigned int> numbers,
                            std::string choice = no_command , int seed = time(NULL) );
    bool move_element(std::string command, unsigned int compare = 0);

    int check_solvability();
private:
    // Shuffles the numbers vector by using seed as a seed value
    void my_shuffle(std::vector<unsigned int>& numbers, int seed);

    // Game grid for the 15 puzzle
    std::vector<std::vector<unsigned int>> grid_ ;

};

#endif // BOARD_HH
