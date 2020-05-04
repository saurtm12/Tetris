#ifndef TIMER_HH
#define TIMER_HH
#include <QTimer>

class Timer : public QTimer
{
    Q_OBJECT
public:
    int get_minute();
    int get_second();
public slots :
    void reset_time();
    void start_time();
    void pause();
signals:
    void finish_a_second();
private:
    //QTimer* timer_;
    int minute = 0;
    int second = 0;
    int remaining = 1000;
};

#endif // TIMER_HH
