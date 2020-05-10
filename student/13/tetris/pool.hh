#ifndef POOL_HH
#define POOL_HH

#include <tetromino.hh>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QBrush>
#include <QPen>
#include <vector>
#include <unordered_map>
#include <random>

enum Color
{
    LIGHT_BLUE,
    DARK_BLUE,
    GRAY,
    YELLOW,
    GREEN,
    PURPLE,
    RED,
    WHITE
};

enum Tetromino_kind
{
    HORIZONTAL,
    LEFT_CORNER,
    RIGHT_CORNER,
    SQUARE,
    STEP_UP_RIGHT,
    PYRAMID,
    STEP_UP_LEFT,
    NUMBER_OF_TETROMINOS
};

// Constants describing scene coordinates
// Copied from moving circle example and modified a bit
const int BORDER_UP = 0;
const int BORDER_DOWN = 480; // 260; (in moving circle)
const int BORDER_LEFT = 0;
const int BORDER_RIGHT = 240; // 680; (in moving circle)

// Size of a tetromino component
const int SQUARE_SIDE = 20;
// Number of horizontal cells (places for tetromino components)
const int COLUMNS = BORDER_RIGHT / SQUARE_SIDE;
// Number of vertical cells (places for tetromino components)
const int ROWS = BORDER_DOWN / SQUARE_SIDE;
const int MILISECOND_PER_SECOND = 1000;

//initialize tetrominos by their name/color/initial position
//I decide to put the rotating origin point is the first position,
//so it will make implementing rotating more easier.
const std::vector<Tetromino> TETROMINO_INFO =
{
    Tetromino(HORIZONTAL, LIGHT_BLUE,
        {{COLUMNS/2,ROWS-2},
         {COLUMNS/2 - 2,ROWS-2},
         {COLUMNS/2-1,ROWS-2},
         {COLUMNS/2 +1,ROWS-2}}),
    Tetromino(LEFT_CORNER, DARK_BLUE,
        {{COLUMNS/2,ROWS-2},
        {COLUMNS/2 - 1,ROWS-2},
         {COLUMNS/2 +1,ROWS-2},
         {COLUMNS/2 -1,ROWS-1}}),
    Tetromino(RIGHT_CORNER, GRAY,
        {{COLUMNS/2,ROWS-2},
         {COLUMNS/2 - 1,ROWS-2},
         {COLUMNS/2 +1,ROWS-2},
         {COLUMNS/2 +1,ROWS-1}}),
    Tetromino(SQUARE, YELLOW,
        {{COLUMNS/2-1, ROWS-1},
         {COLUMNS/2-1,ROWS-2},
         {COLUMNS/2,ROWS-2},
         {COLUMNS/2,ROWS-1}}),
    Tetromino(STEP_UP_RIGHT, GREEN,
        {{COLUMNS/2,ROWS-2},
         {COLUMNS/2-1, ROWS-2},
         {COLUMNS/2,ROWS-1},
         {COLUMNS/2 +1,ROWS-1}}),
    Tetromino(PYRAMID, PURPLE,
        {{COLUMNS/2,ROWS-2},
         {COLUMNS/2-1, ROWS-2},
         {COLUMNS/2,ROWS-1},
         {COLUMNS/2 +1,ROWS-2}}),
    Tetromino(STEP_UP_LEFT, RED,
         {{COLUMNS/2,ROWS-2},
          {COLUMNS/2-1, ROWS-1},
          {COLUMNS/2,ROWS-1},
          {COLUMNS/2 +1,ROWS-2}})
};

const std::vector<std::pair<int, QBrush>> COLOR_INFO =
{
    {LIGHT_BLUE, QBrush(Qt::cyan)},
    {DARK_BLUE, QBrush(Qt::blue)},
    {GRAY, QBrush(Qt::gray)},
    {YELLOW, QBrush(Qt::yellow)},
    {GREEN, QBrush(Qt::green)},
    {PURPLE, QBrush(Qt::magenta)},
    {RED, QBrush(Qt::red)},
    {WHITE, QBrush(Qt::white)}
};

class Pool : public QObject
{
    Q_OBJECT
public :
    Pool(QObject *parent, QGraphicsScene* board_);
    ~Pool();
};

#endif // POOL_HH
