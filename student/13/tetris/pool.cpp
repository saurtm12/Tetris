#include "pool.hh"
Pool::Pool(QObject *parent, QGraphicsScene* board_):
   QObject(parent), board(board_)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Pool::finish_second);
    ticktok = new QTimer(this);
    connect(ticktok,&QTimer::timeout, this, &Pool::tick);

    connect(this, &Pool::game_over, this, &Pool::pause_game);
    initialize_tetrominos();
    initialize_colors();
    for (auto i = 0; i < COLUMNS; i++)
    {
        matrix.push_back({});
    }
    for (auto& col : matrix)
    {
        for (auto i = 0; i < ROWS; i++)
        {
            col.push_back(Color::WHITE);
        }
    }
    blackpen= QPen(Qt::black);
    blackpen.setWidth(1);
    whitepen = QPen(Qt::white);
    whitepen.setWidth(1);
    // Setting random engine ready for the first real call.
    int seed = time(0);
    randomEng.seed(seed);
    distr = std::uniform_int_distribution<int>(0, NUMBER_OF_TETROMINOS - 1);
    distr(randomEng);
}

Pool::~Pool()
{
    delete timer;
    delete ticktok;
}

void Pool::initialize_tetrominos()
{
    for (auto const& tetromino : TETROMINO_INFO)
    {
        tetrominos.insert({tetromino.get_kind(), tetromino});
    }
}

void Pool::initialize_colors()
{
    for (auto const& color : COLOR_INFO)
    {
        colors.insert({color.first, color.second});
    }
}

void Pool::start_game()
{
    if (is_start)
    {
        return;
    }
    timer->start(MILISECOND_PER_SECOND);
    ticktok->start(fall_velocity);

    second = 0;
    emit time_change(second);
    score = 0;
    emit score_change(score);

    is_start = true;
    is_paused = false;

    current_piece = tetrominos.at(distr(randomEng));
    current_pos = current_piece.get_initial_pos();
    show_piece();
    refresh_board();
}

void Pool::pause_game()
{
    if (is_paused)
    {
        return;
    }
    is_paused = true;
    timer->stop();
    ticktok->stop();
}

void Pool::resume_game()
{
    if (!is_paused)
    {
        return;
    }
    is_paused = false;
    timer->start(MILISECOND_PER_SECOND);
    ticktok->start(fall_velocity);
}

void Pool::finish_second()
{
    ++second;
    emit time_change(second);
}

void Pool::draw_block(const int& x, const int& y, const int& color)
{
    if (color == Color::WHITE)
    {
        return;
    }
    QGraphicsRectItem* block = new QGraphicsRectItem(x*SQUARE_SIDE,BORDER_DOWN- (y+1)*SQUARE_SIDE,
                          SQUARE_SIDE, SQUARE_SIDE);

    block->setBrush(colors.at(color));
    board->addItem(block);
}

void Pool::tick()
{
    fall_velocity = INI_FALL_VELOCITY - score/12;
    ticktok->start(fall_velocity);
    move_down();
}

void Pool::refresh_board()
{
    board->clear();
    for (auto col = 0; col < COLUMNS; col++)
    {
        for (auto row = 0; row < ROWS; row++)
        {
            draw_block(col, row, matrix.at(col).at(row));
        }
    }
}

bool Pool::piece_is_landed() const
{
    for (auto const& point : current_pos)
    {   if (point.second == 0)
        {
            return true;
        }
        if ( !point_is_piece(point.first,point.second-1) && matrix.at(point.first).at(point.second-1) != Color::WHITE)
        {
            return true;
        }
    }
    return false;
}

void Pool::show_piece()
{
    for (auto& point : current_pos)
    {
        matrix.at(point.first).at(point.second) = current_piece.get_color();
    }
}

bool Pool::point_is_piece(int x, int y) const
{
    for (auto const& point : current_pos)
    {
        if (point.first == x && point.second == y)
            return true;
    }
    return false;
}

void Pool::move_down()
{
    if (piece_is_landed())
    {
        eliminate_rows();
        give_new_piece();
        show_piece();
        return;
    }
    for (auto const& point : current_pos)
    {
        if (point.second == 0)
        {
            return;
        }
    }
    for (auto& point : current_pos)
    {
        matrix.at(point.first).at(point.second) = Color::WHITE;
        point.second--;
    }
    show_piece();
    refresh_board();
}

void Pool::move_right()
{
    for (auto const& point : current_pos)
    {
        if (point.first == COLUMNS - 1)
        {
            return;
        }
        else
        {
            if (matrix.at(point.first+1).at(point.second) != Color::WHITE
                    && !point_is_piece(point.first+1, point.second))
            {
                return;
            }
        }
    }
    for (auto& point : current_pos)
    {
        matrix.at(point.first).at(point.second) = Color::WHITE;
        point.first++;
    }
    show_piece();
    refresh_board();
}

void Pool::move_left()
{
    for (auto const& point : current_pos)
    {
        if (point.first == 0)
        {
            return;
        }
        else
        {
            if (matrix.at(point.first-1).at(point.second) != Color::WHITE
                    && !point_is_piece(point.first-1, point.second))
            {
                return;
            }
        }
    }

    for (auto& point : current_pos)
    {
        matrix.at(point.first).at(point.second) = Color::WHITE;
        point.first--;
    }
    show_piece();
    refresh_board();
}

void Pool::rotate()
{
    if (current_piece.get_kind() == SQUARE)
    {
        return;
    }
    Positions temp_pos = current_pos;
    auto origin = current_pos.at(0);
    for (unsigned int i = 1; i < current_pos.size(); i++)
    {
        temp_pos.at(i) = {origin.first+ (temp_pos.at(i).second-origin.second), origin.second + (origin.first - temp_pos.at(i).first)};
    }


    for (auto& point : temp_pos)
    {
        while (point.first < 0)
        {
            for (auto& temp_point : temp_pos)
            {
                temp_point.first++;
            }
        }
        while (point.first >= COLUMNS)
        {
            for (auto& temp_point : temp_pos)
            {
                temp_point.first--;
            }
        }
        while (point.second >= ROWS)
        {
            for (auto& temp_point : temp_pos)
            {
                temp_point.second--;
            }
        }
        if (point.second < 0)
        {
            while (point.second <0)
            {
                for (auto& temp_point : temp_pos)
                {
                    temp_point.second++;
                }
            }
            give_new_piece();
        }
    }

    for (auto& point : current_pos)
    {
        matrix.at(point.first).at(point.second) = Color::WHITE;
    }

    for (auto const& point : temp_pos)
    {
        if (matrix.at(point.first).at(point.second) != Color::WHITE)
        {
            show_piece();
            return;
        }
    }
    for (auto& point : current_pos)
    {
        matrix.at(point.first).at(point.second) = Color::WHITE;
    }
    current_pos = temp_pos;
    show_piece();

    refresh_board();
}
void Pool::give_new_piece()
{
    current_piece = tetrominos.at(distr(randomEng));
    current_pos = current_piece.get_initial_pos();
    for (auto point : current_pos)
    {
        if (matrix.at(point.first).at(point.second) != Color::WHITE)
        {
            emit game_over(score);
            return;
        }
    }
    show_piece();
    refresh_board();
}

bool Pool::game_is_start() const
{
    return is_start;
}
bool Pool::game_is_pause() const
{
    return is_paused;
}

void Pool::eliminate_rows()
{
    int i = 0;
    for (i = 0; i < ROWS; i++)
    while (i < ROWS)
    {
        bool col_is_full = true;
        for (auto j = 0; j < COLUMNS; j++)
        {
            if (matrix.at(j).at(i) == Color::WHITE)
            {
                col_is_full = false;
                i++;
                break;
            }
        }
        if (col_is_full)
        {
            score+=COLUMNS;
            emit score_change(score);
            for (auto k = i; k < ROWS-1; k++)
            {
                for (auto h = 0; h < COLUMNS; h++)
                {
                    matrix.at(h).at(k) = matrix.at(h).at(k+1);
                }
            }
            for (auto h = 0; h < COLUMNS; h++)
            {
                matrix.at(h).at(ROWS-1) = Color::WHITE;
            }
        }
    }
    refresh_board();
}


