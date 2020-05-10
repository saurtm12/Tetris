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



