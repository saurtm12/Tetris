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




int playing_game(Board &board)
{
        while (true)
        {
            board.print();
            if (board.is_won())
            {
                std::cout<<"You won!";
                return 0;
            }

            std::cout<<"Dir (command, number): ";
            std::string dir, command="", num_string="";
            std::getline(std::cin, dir);
            unsigned int pos = 0;
            while ( pos<dir.length() && dir[pos] != ' ')
                command += dir[pos++];

            if (command == command_up || command == command_down ||
                    command == command_left || command ==command_right)
            {
                for (unsigned int i =pos; i < dir.length(); i++)
                    num_string += dir[i];
                int compare_number = std::stoi(num_string);
                if (compare_number >=1 && compare_number<=15)
                    {
                    bool move = board.move_element(command, compare_number);
                    if (!move)
                    {
                        std::cout<<"Impossible direction: "<<command<<"\n";
                    }
                    }
                    else
                    std::cout<<"Invalid number: "<< compare_number<<"\n";
            }
            else if (command == "q")
                return 0;
            else
            {
                std::cout<<"Unknown command: "<<command<<"\n";
            }


        }

}


int main()
{
    Board board;
    bool proceeding_success  = board.initializing_board();
    if  (proceeding_success == 0)
        return EXIT_FAILURE;
   Board temp_board = board;

   int solvability = temp_board.check_solvability();
   if (solvability == 0)
   {
        std::cout<<"Game is not solvable. What a pity.";
        return EXIT_SUCCESS;
   }


   std::cout<<"Game is solvable: Go ahead!\n";
   playing_game(board);

    return EXIT_SUCCESS;
}
