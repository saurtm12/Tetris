/* Class: Mainwindow
    Course : TIE-02201
    Student's name : Hong Nghia Duc
    Student No : 292119
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class represents the mainwindow of the game.
 *
 * */
#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // We need a graphics scene in which to draw rectangles.
    scene_ = new QGraphicsScene(this);

    // The graphicsView object is placed on the window
    // at the following coordinates, but if you want
    // different placement, you can change their values.
    int left_margin = 100; // x coordinate
    int top_margin = 150; // y coordinate

    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui->graphicsView->setGeometry(left_margin, top_margin,
                                  BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1, because
    // each square of a tetromino is considered to be inside the sceneRect,
    // if its upper left corner is inside the sceneRect.
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);


    // Add more initial settings and connect calls, when needed.
    pool = new Pool(this, scene_);
    connect(pool, &Pool::score_change, ui->scoreLcdNumber, QOverload<int>::of(&QLCDNumber::display));
    connect(ui->startPushButton, &QPushButton::clicked, pool, &Pool::start_game);
    connect(ui->pausePushButton, &QPushButton::clicked, pool, &Pool::pause_game);
    connect(ui->resumePushButton, &QPushButton::clicked, pool, &Pool::resume_game);
    connect(ui->quitPushButton, &QPushButton::clicked, this, &MainWindow::close);
    connect(pool, &Pool::time_change, this, &MainWindow::display_time);
    connect(pool, QOverload<int>::of(&Pool::game_over),this, QOverload<int>::of(&MainWindow::display_game_over));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::display_time(int second)
{
    ui->secLcdNumber->display(second % SECOND_PER_MINUTE);
    ui->minLcdNumber->display(second / SECOND_PER_MINUTE);
}

void MainWindow::display_game_over(int score)
{
    auto score_ = std::to_string(score);
    std::string info = GAME_OVER;
    for (unsigned int i = 0; i< score_.size(); i++)
    {
        info.push_back(score_[i]);
    }
    QString result(info.c_str());
    QMessageBox::information(this,tr("Message"), result );
    new_game();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (!pool->game_is_start() || pool->game_is_pause())
    {
        return;
    }
    for (auto key : KEY_FUNC)
    {
        if (event->key() == key.key_press)
        {
            (pool->*key.func)();
            return;
        }
    }
}

void MainWindow::new_game()
{
    delete pool;
    scene_->clear();
    pool = new Pool(this, scene_);
    connect(pool, &Pool::score_change, ui->scoreLcdNumber, QOverload<int>::of(&QLCDNumber::display));
    connect(ui->startPushButton, &QPushButton::clicked, pool, &Pool::start_game);
    connect(ui->pausePushButton, &QPushButton::clicked, pool, &Pool::pause_game);
    connect(ui->resumePushButton, &QPushButton::clicked, pool, &Pool::resume_game);
    connect(ui->quitPushButton, &QPushButton::clicked, this, &MainWindow::close);
    connect(pool, &Pool::time_change, this, &MainWindow::display_time);
    connect(pool, QOverload<int>::of(&Pool::game_over),this, QOverload<int>::of(&MainWindow::display_game_over));
    ui->secLcdNumber->display(0);
    ui->minLcdNumber->display(0);
    ui->scoreLcdNumber->display(0);
}
