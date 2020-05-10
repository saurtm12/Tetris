/* Class: Pool
    Course : TIE-02201
    Student's name : Hong Nghia Duc
    Student No : 292119
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class represents the pool (board) of the game.
 *
 * */
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
    Pool(const Pool& initial_value) = delete;
    Pool& operator=(const Pool& assignable_value) = delete;
    /**
     * @brief if the game is started.
     * @return true if the game is started, other wise false.
     */
    bool game_is_start() const;

    /**
     * @brief if the game is paused.
     * @return true if the game is paused, other wise false.
     */
    bool game_is_pause() const;

public slots :
    /**
     * @brief start the game.
     */
    void start_game();

    /**
     * @brief pause the game.
     */
    void pause_game();

    /**
     * @brief resume the game.
     */
    void resume_game();

    /**
     * @brief finish a second.
     */
    void finish_second();

    /**
     * @brief a time period that it is necessary to drop the tetromino down.
     */
    void tick();

    /**
     * @brief try move the tetromino down.
     */
    void move_down();

    /**
     * @brief try move the tetromino right.
     */
    void move_right();

    /**
     * @brief try move the tetromino left.
     */
    void move_left();

    /**
     * @brief try move the tetromino down.
     */
    void rotate();

signals :
    /**
     * @brief emit a signal that tell the mainwindow display the new time.
     */
    void time_change(int second);

    /**
     * @brief emit a signal that tell the mainwindow display the new score.
     */
    void score_change(int score);

    /**
     * @brief emit a signal that tell the mainwindow display the game is over.
     */
    void game_over(int score);
private :
    const int INI_FALL_VELOCITY = 500;
    using Matrix = std::vector<std::vector<int>>;
    // For randomly selecting the next dropping tetromino
    std::default_random_engine randomEng;
    std::uniform_int_distribution<int> distr;

    //store the pointer that we can represent matrix on the board.
    QGraphicsScene* board;

    //used in counting time that the player has played.
    QTimer* timer;
    int second = 0;

    //time period that tell a tetrominos should be dropped
    QTimer* ticktok;
    int fall_velocity = INI_FALL_VELOCITY;

    //use for drawing blocks
    QPen blackpen;
    QPen whitepen;

    // The main matrix that we use.
    // the matrix have the axes that is similar to math axis
    // ( Ox is to the east and Oy is to the north;
    Matrix matrix;

    // maps that contain types of tetrominos and QBrush that would be used.
    std::unordered_map<int, Tetromino> tetrominos;
    std::unordered_map<int, QBrush> colors;

    //initialize score and other attributes.
    int score = 0;
    bool is_start = false;
    bool is_paused = false;
    int board_height =0;
    int board_width = 0;

    //info of current tetrominos and positions
    Tetromino current_piece;
    Positions current_pos;

    /**
     * @brief initialize tetrominos map
     */
    void initialize_tetrominos();

    /**
     * @brief initialize color map
     */
    void initialize_colors();

    /**
     * @brief draw a block in the geometry coordinate
     */
    void draw_block(const int& x,const  int& y,const int& color);

    /**
     * @brief refresh board everytime makes a change.
     */
    void refresh_board();

    /**
     * @brief check if the tetromino should be put to the matrix.
     * @return true if it should be, otherwise false.
     */
    bool piece_is_landed() const;

    /**
     * @brief give the current tetromino to the matrix by it current pos.
     */
    void show_piece();

    /**
     * @brief check if the considering point belongs to the current piece
     * @return true if it is, false otherwise.
     */
    bool point_is_piece(int x, int y) const;

    /**
     * @brief give the new piece for game.
     */
    void give_new_piece();

    /**
     * @brief check if rows are full, then give score.
     */
    void eliminate_rows();
};

#endif // POOL_HH
