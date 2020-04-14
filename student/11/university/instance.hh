/* Class: Instance
    Course : TIE-02201
    Student's name : Hong Nghia Duc
    Student No : 292119
    This Instance class is implemented with functions that have
    been declared in this file.
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
#include "utils.hh"
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
    Instance(Course* course_, std::string instance_name_, Date start_date_ );
    ~Instance();
    
    /**
     * @brief print instance's info.
     */
    void print() const;

    /**
     * @brief listing all students who are attending instance.
     */
    void print_students() const;

    /**
     * @brief compare the instance names.
     * @return true if they are identical, if not, false.
     */
    bool is_named(const std::string& name) const;
    
    /**
     * @brief add a student to an instance.
     * @return true if add student successfully,
     *  if the student is current in the instance, return false.
     */
    bool add_student(Account* new_student, const Date& sign_up_date);

    /**
     * @brief complete a student from the instance.
     */
    void complete_student(Account* student);

    /**
     * @brief print the intance that helps in the PRINT_STUDY_STATE
     */
    void print_course_info() const;

    Course* get_course_ptr() const;
private:
    Course* course_of_;
    std::string instance_name_;
    std::vector<Account*> signups_;
    const Date start_date_;
};

#endif // INSTANCE_HH
