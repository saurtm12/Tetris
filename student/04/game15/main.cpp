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


bool initializing_board(Board &board);
bool proceed_choice(std::vector<unsigned int> &numbers, std::string choice, Board &board);
int check_solvability(Board  &board);
bool initializing_board(Board &board)
{

    // Select random choice of the user
    std::string random_choice;
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

    std::vector <unsigned int> numbers;

    int proceed_result = proceed_choice(numbers,random_choice,board);
    if (proceed_result ==0)
            return 0;


    board.initialize_empty_pointer();
    return 1;
}






bool proceed_choice(std::vector <unsigned int> &numbers, std::string choice, Board &board)
{
    if (choice == yes_command || choice == YES_command)
    {
            std::string seed_;
            std::cout<<"Enter a seed value (or an empty line): ";
            std::getline(std::cin,seed_);


            int seed;
            if (seed_ != "")
                seed = std::stoi(seed_);
            else
                seed = (time (NULL) );

            for (int i=0; i < SIZE*SIZE  ; i++)
            {
                numbers.push_back(i+1);
            }
            board.add_element_togrid(numbers, yes_command, seed );
            return 1;

    }
    else
    {
        std::cout<< "Enter the numbers 1-16 in a desired order (16 means empty):\n";
        for (int i=0; i<SIZE; i++)
            for (int j =0; j<SIZE; j++)
                {
                    int temp;
                    std::cin >>temp;
                    numbers.push_back(temp);
                }
        int test[SIZE*SIZE+1]={0};
        for (unsigned int i = 0; i<numbers.size(); i++)
            if (numbers[i]>=1 && numbers[i]<= SIZE*SIZE)
            test[numbers[i]] = 1;



        for (unsigned int i = 1; i <= numbers.size(); i++)
        {
            if ( test[i] != 1)
            {
                std::cout<< "Number "<<i<<" is missing";
                return 0;
            }
        }
        board.add_element_togrid(numbers);
        return 1;
    }


}

int playing_game(Board &board)
{
    while (true)
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
            std::string dir, command, num_string;
            std::getline(std::cin, dir);
            command = dir[0];
            if (command == command_up || command == command_down ||
                    command == command_left || command ==command_right)
            {
                for (unsigned int i =2; i < dir.length(); i++)
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
}


int main()
{
    Board board;
    bool proceeding_success  = initializing_board(board);
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
