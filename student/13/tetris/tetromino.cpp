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
#include "tetromino.hh"

Tetromino::Tetromino(const int& tetromino_kind_, const int& color_
                     , Positions initial_pos_):
    tetromino_kind(tetromino_kind_),
    initial_pos(initial_pos_),
    color(color_)
{

}

Tetromino::Tetromino()
{

}

Tetromino::~Tetromino()
{

}
int Tetromino::get_kind() const
{
    return tetromino_kind;
}

int Tetromino::get_color() const
{
    return color;
}

Positions Tetromino::get_initial_pos() const
{
    return initial_pos;
}
