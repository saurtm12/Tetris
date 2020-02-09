/*
 * Desc:
 *  This program generates a 15 puzzle. The board is SIZE x SIZE,
 * (original was 4x4) and every round the player chooses a direction and
 * a number tile, making the given tile to be moved to the given direction.
 *  Game will end when the numbers 1-15 (1-16) are in the ascending order,
 * starting from top left and proceeding row by row.
 * Empty space is represented by the number 16 in the code (constant EMPTY)
 * and by dot when printing the game board.
 *
 * Program author ( Fill with your own info )
 * Name: Nghia Duc Hong
 * Student number: 292119
 * UserID: vsduho
 * E-Mail: duc.hong@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * */
#include <iostream>
#include "board.hh"
#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

const int EMPTY = 16;
/* proceed playing with a while loop
 * , only get out when the command is "q" or win the game
*/
int playing_game(Board &board)
{
        while (true)
        {
            //first print the board
            board.print();

            //check if we have won using is_won() function of Board Class
            if (board.is_won())
            {
                std::cout<<"You won!";
                //collapse the program immediately when we win
                return 0;
            }

            // initialize string variables used to store command
            std::cout<<"Dir (command, number): ";
            std::string dir, command="", num_string="";
            std::getline(std::cin, dir);

            //initial a integer that use to separate two part of command
            unsigned int pos = 0;
            //read the command
            while ( pos<dir.length() && dir[pos] != ' ')
                command += dir[pos++];
            //proceed command
            if (command == command_up || command == command_down ||
                    command == command_left || command ==command_right)
            {
                //find the second part of the command
                for (unsigned int i =pos; i < dir.length(); i++)
                    num_string += dir[i];
                // convert string number to integer
                int compare_number = std::stoi(num_string);

                //check if it is a valid number
                if (compare_number >=1 && compare_number<=EMPTY-1)
                    {
                    //proceeding move if all the previous condition is valid
                    bool move = board.move_element(command, compare_number);
                    //if the function return 0, that mean we cant move
                    //successfully
                    // that mean the move is not completed
                    if (!move)
                    {
                        std::cout<<"Impossible direction: "<<command<<"\n";
                    }
                    }
                    else
                    // notify unvalid number
                    std::cout<<"Invalid number: "<< compare_number<<"\n";
            }

            // collapse program if the command is q
            else if (command == "q")
                return 0;
            else

            //notify if there is an unknown command
            {
                std::cout<<"Unknown command: "<<command<<"\n";
            }
        }
}
int main()
{
    //initializing board
    Board board;

    //proceed read inputs, the proceeding_success is the
    //result if the initializing is successful
    bool proceeding_success  = board.initializing_board();
    if  (proceeding_success == 0)
        return EXIT_FAILURE;

   //make a copy board that helps checking the solvability
   Board temp_board = board;

    //check if the board is solvable by check_solvability() function
   int solvability = temp_board.check_solvability();
   if (solvability == 0)
   {
        std::cout<<"Game is not solvable. What a pity.";
        return EXIT_SUCCESS;
   }

   //proceeding the game if there is no problem
   std::cout<<"Game is solvable: Go ahead!\n";
   playing_game(board);
   return EXIT_SUCCESS;
}
