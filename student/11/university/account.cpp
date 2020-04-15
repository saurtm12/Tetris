/*
Course : TIE-02201
  Student's name : Hong Nghia Duc
  Student No : 292119
  Modify in this file : 
    *Implement functions
      -print_complete_courses()
      -print_study_state()
      -add_instance(Instance* instance)
      -complete_instance(Instance* instance)
      -Account destructor
*/
#include "account.hh"
#include "utils.hh"
#include "instance.hh"
#include "course.hh"

Account::Account(std::string full_name, std::string email, int account_number):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    email_(email),
    account_number_(account_number)
{
    std::vector<std::string> name = utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();
}

Account::~Account()
{
    
}

void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

std::string Account::get_email()
{
    return email_;
}

void Account::print_complete_courses() const
{
    for ( Course* course : completed_ ){
        course->print_info(true);
    }
    std::cout << "Total credits: " << credit_ << std::endl;
}

void Account::print_study_state() const
{
    std::cout << "Current:" << std::endl;
    for ( Instance* instance: current_ )
    {
        instance->print_course_info();
    }
    std::cout << "Completed:" << std::endl;
    print_complete_courses();
}

void Account::add_instance(Instance* new_instance)
{
    current_.push_back(new_instance);
    std::cout << SIGNED_UP << std::endl;
}

bool Account::complete_instance(Instance* instance)
{
    auto iter =  std::find(current_.begin(), current_.end(), instance);
    if (iter == current_.end())
    {
        std::cout << NO_SIGNUPS << std::endl;
        return false;
    }
    credit_ += instance->get_course_ptr()->get_credits();
    std::cout << COMPLETED << std::endl;
    completed_.push_back(instance->get_course_ptr());
    current_.erase(iter);
    return true;
}