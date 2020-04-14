/*
    Course : TIE-02201
    Student's name : Hong Nghia Duc
    Student No : 292119
    Modify in this file :
    - Line 14 that helps us set the date on leap day.
*/
#include "date.hh"
#include <iostream>

Date::Date(unsigned int day, unsigned int month, unsigned int year):
    day_(day), month_(month), year_(year)
{
    if (!(is_leap_year() && day == 29 && month == 2 ))
    {
        if ( month_ > 12 || month_ < 1){
        month_ = 1;
    }
        if ( day_ > month_sizes[month_ - 1]
            || (month_ == 2 && is_leap_year()
                 && day > month_sizes[month - 1 ] + 1) ){
        day_ = 1;
        }
    }
}
Date::~Date()
{

}

Date::Date( const Date &obj)
{
    day_ = obj.day_;
    month_ = obj.month_;
    year_ = obj.year_;
}

void Date::advance_by_period_length()
{
    advance_by(PERIOD_LENGTH);
}

void Date::advance_by(unsigned int days)
{
    day_ = day_ + days;
    while ( day_ > month_sizes[month_ - 1] ){
        if ( month_ == 2 && day_ == 29 ){
            return;
        }
        day_ = day_ - month_sizes[month_ - 1];
        if ( month_ == 2 && is_leap_year() ){
            day_--;
        }
        month_++;

        if ( month_ > 12 ){
            month_ = month_ - 12;
            year_++;
        }
    }
}

void Date::print() const
{
    std::cout << day_ << "." << month_ << "." << year_;
}

unsigned int Date::get_day() const
{
    return day_;
}

unsigned int Date::get_month() const
{
    return month_;
}

unsigned int Date::get_year() const
{
    return year_;
}

bool Date::operator==(const Date &rhs) const
{
    return day_ == rhs.day_ && month_ == rhs.month_ && year_ == rhs.year_ ;
}

bool Date::operator<(const Date &rhs) const
{
    return (year_ * 10000 + month_ * 100 + day_ ) <
            ( rhs.year_ * 10000 + rhs.month_ * 100 + rhs.day_);
}

bool Date::is_leap_year() const
{
    return (year_ % 4 == 0) && (!(year_ % 100 == 0) || (year_ % 400 == 0));
}

