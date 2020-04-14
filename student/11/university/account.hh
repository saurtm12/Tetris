/* Class: Account
  Course : TIE-02201
  Student's name : Hong Nghia Duc
  Student No : 292119
  Modify in this file : 
    *Add functions
      -print_complete_courses()
      -print_study_state()
      -add_instance(Instance* instance)
      -complete_instance(Instance* instance)
      -Account destructor
      -disable assign operator and copy constructor
    *Add a private variable : credit_ to store the total credits have been earned
  * ----------
  * Defines a student or a staff account in the university system.
  *
  * In the project, this class should be expanded to
  * include study history of the account.
  * */
#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include "date.hh"
#include <string>
#include <vector>
#include <map>
#include <iostream>

class Instance;
class Course;

const std::string NO_SIGNUPS = "No signups found on this instance.";
const std::string SIGNED_UP = "Signed up on the course instance.";
const std::string COMPLETED = "Course completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "frontname lastname"
     * @param email
     * @param account_number
     */
    Account(std::string full_name, std::string email, int account_number);
    
    /**
     * @brief Account destructor
     */
    ~Account();
    
    //disable operator= and copy constructor
    Account(const Account& initial_value) = delete;
    Account& operator=(const Account& assignable_value) = delete;
    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email();

    /**
     * @brief print all the courses that have been completed
     */
    void print_complete_courses() const;

    /**
     * @brief print study state (current and completed) of an account
     */
    void print_study_state() const;

    /**
     * @brief add instance to account
     * @param instance as "the instance need to be added"
     */
    void add_instance(Instance* instance);

    /**
     * @brief use to finish an instance
     * @param instance as "the instance need to be completed"
     * @return true if complete successfully, if not, return false
     */
    bool complete_instance(Instance* instance);

private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;

    //store credist have been earned.
    int credit_ = 0;

    std::vector<Instance*> current_;
    std::vector<Course*> completed_;
};

#endif // ACCOUNT_HH
