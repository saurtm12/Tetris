/* Class: Instance
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class that represent a single instance.
 *
 * Note: Students should make changes to this class, and add their info and
 * specifics of the class to this comment.
 * */
#ifndef INSTANCE_HH
#define INSTANCE_HH

#include "account.hh"
#include "date.hh"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

// Forward-declaration of Course, so that instance can point to the course it belongs to.
class Course;

const std::string ALREADY_REGISTERED = "Error: Student has already registered on this course.";
const std::string LATE = "Error: Can't sign up on instance after the starting date.";
const std::string INDENT = "    ";

class Instance
{
public:
    Instance(Course* course_, std::string instance_name_, Date start_date_);
    ~Instance();
    void print();
    void print_students();
    bool is_named(std::string name);
private:
    Course* course_of;
    std::string instance_name;
    std::vector<Account*> signups;
    Date start_date;
};

#endif // INSTANCE_HH
