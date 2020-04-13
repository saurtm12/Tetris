#include "instance.hh"
#include "course.hh"

Instance::Instance(Course* course_, std::string instance_name_, Date start_date_):
    course_of(course_), 
    instance_name(instance_name_), 
    start_date(start_date_)
{

}

Instance::~Instance()
{

}

void Instance::print()
{
    std::cout << instance_name << "\n";

    std::cout << INDENT << "Starting date: ";
    start_date.print();
    std::cout <<"\n";

    std::cout << INDENT << "Amount of students: "
              << signups.size() << std::endl;
}

void Instance::print_students()
{
    for ( auto const& account : signups ){
        account->print();
    }
}

bool Instance::is_named(std::string name)
{
    return instance_name == name;
}