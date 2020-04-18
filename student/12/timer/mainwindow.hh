#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Normally this member should be in private part of the
    // class, but due to the automated tests it must be more
    // accessible.
    QTimer* timer;

private slots:
    // Add your slots here
    void click_close_button();
    void click_start_button();
    void click_stop_button();
    void click_reset_button();
    void finish_1000ms();
private:
    Ui::MainWindow *ui;
    // Add other necessary members here
    int remain =1000 ;
    int minute ;
    int second ;
};

#endif // MAINWINDOW_HH
