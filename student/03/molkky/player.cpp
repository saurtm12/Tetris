#include "player.hh"

#include <bits/stdc++.h>
#include <string>
using namespace std;

    Player::Player (std::string name1){
    name=name1 ;
    score=0;
        }

        void Player::add_points(int point){
            score += point;
            if (score>50)
            {
                score=25;
            }
        }
        bool Player::has_won()
        {
            if (score == 50)
            {
                return 1;
            }
            else return 0;
        }
        std::string Player::get_name()
        {
            return name;
        }
        int Player::get_points()
        {
            return score;
        }
