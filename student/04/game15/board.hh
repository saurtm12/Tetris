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
#define BOARD_HH
#include <vector>

const int SIZE = 4;

class Board
{
public:
    // For creating and initializing the grid, you have at least two choices:
    // 1. Implement a constructor that fills the game grid with empties or such
    // and two initialize methods
    // 2. Implement two constructors, one for each initialization way

    // Prints the game grid
    void print();
    struct empty_pos
    {
        int row;
        int column;
    };
    // Shuffles the numbers vector by using seed as a seed value
    void my_shuffle(std::vector<unsigned int>& numbers, int seed);
    // More methods
    void add_element_togrid(std::vector <unsigned int> ints);

private:


    // Game grid for the 15 puzzle
    std::vector<std::vector<unsigned int>> grid_;

};

#endif // BOARD_HH
