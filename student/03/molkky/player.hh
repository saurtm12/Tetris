#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>
class Player{
    private:
        int score;
        std::string name;
    public :
        Player (std::string name1);
        void add_points(int point);
        bool has_won();
        std::string get_name();
        int get_points();
};
#endif // PLAYER_HH
