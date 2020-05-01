#include "timer.hh"

Timer::Timer()
{

}

Timer::~Timer()
{

}

void Timer::reset_time()
{
    this->stop();
    minute = 0;
    second = 0;
}

void Timer:: start_time()
{
    this->start(remaining);
}

void Timer::pause()
{
    remaining = this->remainingTime();
    this->stop();
}

void Timer::finish_a_second()
{
    this->start(1000);
    second++;
    if (second == 60)
    {
        second =0;
        minute++;
    }
}

int Timer::get_minute()
{
    return minute;
}

int Timer::get_second()
{
    return second;
}
