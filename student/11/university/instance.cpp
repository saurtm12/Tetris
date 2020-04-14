#include "instance.hh"
#include "course.hh"
Instance::Instance(Course* course, std::string instance_name, Date start_date ):
    course_of_(course), 
    instance_name_(instance_name), 
    start_date_(start_date)
{

}

Instance::~Instance()
{

}

void Instance::print() const
{
    std::cout<< instance_name_ << "\n";

    std::cout<< INDENT << "Starting date: ";
    start_date_.print();
    std::cout<<"\n";

    std::cout<< INDENT << "Amount of students: "
            << signups_.size() << "\n";
}

void Instance::print_students() const
{
    for ( auto const& account : signups_ ){
        account->print();
    }
}

bool Instance::is_named(const std::string& name) const
{
    return instance_name_ == name;
}

bool Instance::add_student(Account* new_student)
{
    auto iter = std::find(signups_.begin(), signups_.end(), new_student);
    if (iter != signups_.end())
    {   
        std::cout << ALREADY_REGISTERED << "\n";
        return false;
    }
    if (start_date_ < utils::today )
    {
        std::cout << LATE << "\n";
        return false;
    }

    signups_.push_back(new_student);
    return true;
}

void Instance::complete_student(Account* student)
{
    auto iter = std::find(signups_.begin(), signups_.end(), student);
    signups_.erase(iter);
}

void Instance::print_course_info() const
{
    course_of_->print_info(false);
    std::cout<< " " << instance_name_ << "\n";
}

Course* Instance::get_course_ptr() const
{
    return course_of_;
}