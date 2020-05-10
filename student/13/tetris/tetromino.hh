/* Class: Tetromino
    Course : TIE-02201
    Student's name : Hong Nghia Duc
    Student No : 292119
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class represents the tetromino of the game.
 *
 * */
#ifndef TETROMINO_HH
#define TETROMINO_HH

#include <vector>

using Positions = std::vector<std::pair<int,int>>;

class Tetromino
{
public:
    Tetromino(const int& tetromino_kind_, const int& color_, Positions initial_pos_);
    Tetromino();
    ~Tetromino();
    //can not disable copy constructor and assign operator because I am using it.

    /**
     * @brief return the kind of tetromino.
     */
    int get_kind() const;

    /**
     * @brief return the color of tetromino.
     */
    int get_color() const;

    /**
     * @brief return the initial position of tetromino.
     */
    Positions get_initial_pos() const;
private:
    int tetromino_kind;
    Positions initial_pos;
    int color;
};

#endif // TETROMINO_HH
