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
#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <pool.hh>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>
#include <QString>
#include <string>
#include <algorithm>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

    QGraphicsScene* scene_;

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

    struct move_command
    {
        int key_press;
        void (Pool::*func)();
    };
    const std::vector<move_command> KEY_FUNC =
    {
        {Qt::Key_Left, &Pool::move_left},
        {Qt::Key_Right, &Pool::move_right},
        {Qt::Key_Up, &Pool::rotate},
        {Qt::Key_Down, &Pool::move_down},
        {Qt::Key_A, &Pool::move_left},
        {Qt::Key_D, &Pool::move_right},
        {Qt::Key_W, &Pool::rotate},
        {Qt::Key_S, &Pool::move_down}
    };
    std::string GAME_OVER = "Game over! Your score : ";
    const int SECOND_PER_MINUTE = 60;
    Pool* pool;

    /**
     * @brief set up a new game.
     */
    void new_game();
public slots:
    /**
     * @brief display time
     * @param second : to display mins and secs.
     */
    void display_time(int second);

    /**
     * @brief inform user that game is over and his score.
     * @param score : current score.
     */
    void display_game_over(int score);
protected:

    /**
     * @brief handle the key that pressed by user.
     */
    void keyPressEvent(QKeyEvent* event) override;

};

#endif // MAINWINDOW_HH
