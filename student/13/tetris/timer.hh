#ifndef TIMER_HH
#define TIMER_HH
#include <QTimer>


class Timer : public QTimer
{
public:
    Timer();
    ~Timer();
    void reset_time();
    void start_time();
    void pause();
    void finish_a_second();
    int get_minute();
    int get_second();
private:
    int minute = 0;
    int second = 0;
    int remaining = 1000;

};

#endif // TIMER_HH
