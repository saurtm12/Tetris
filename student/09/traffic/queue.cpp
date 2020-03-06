#include "queue.hh"
#include <iostream>

Queue::Queue(unsigned int cycle)
{
    cycle_ = cycle;
    length_ = 0;
}
Queue::~Queue()
{
    while (first_!= nullptr)
    {
        Vehicle* temp = first_;
        delete temp;
        first_ = first_->next;
    }
}
void Queue::enqueue(string reg)
{
    if (is_green_)
    {
        std::cout<<"GREEN: The vehicle "<<reg <<" need not stop to wait\n";
        return;
    }
    Vehicle* new_Vehicle = new Vehicle;
    new_Vehicle->reg_num = reg;
    new_Vehicle->next = nullptr;

    if (length_ ==0)
    {
        first_ = new_Vehicle;
    }
    else
    {
    last_->next = new_Vehicle;
    }
    last_ = new_Vehicle;
    length_++;
}
void Queue::switch_light()
{
    if (length_ ==0)
    {
        is_green_ = ! is_green_;
        if (is_green_)
        {
            std::cout<<"GREEN: ";
        }
        else
        {
            std::cout<<"RED: ";
        }
        std::cout<<"No vehicles waiting in traffic lights\n";
        return;
    }
    is_green_ = true;
    std::cout<<"GREEN: ";
    if (length_ ==0)
    {
        std::cout<<"No vehicles waiting in traffic lights\n";
        return;
    }
    std::cout<<"Vehicle(s) ";
    if (length_ <= cycle_)
    {
        while (first_ != nullptr)
        {
            Vehicle* temp = first_;
            std::cout<< temp->reg_num<<" ";
            delete temp;
            first_= first_-> next;
        }
        length_=0;
    }
    else
    {
        int i = cycle_;
        while (i!= 0)
        {
            Vehicle* temp = first_;
            std::cout<< temp->reg_num<<" ";
            delete temp;
            first_= first_-> next;
            i--;
        }
        length_ = length_ -3;
    }
    std::cout<<"can go on\n";
    is_green_ = false;
}
void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}
void Queue::print()
{
    if (is_green_)
    {
        std::cout<<"GREEN: ";
    }
    else
    {
        std::cout<<"RED: ";
    }
    if (first_ == nullptr)
    {
        std::cout<<"No vehicles waiting in traffic lights\n";
    }
    else
    {
        auto temp= first_;
        std::cout<<"Vehicle(s) ";
        while (temp != nullptr)
        {
            std::cout<< temp->reg_num<<" ";
            temp=temp->next;
        }
        std::cout<<"waiting in traffic lights\n";
    }

}
// Implement the member functions of Queue here
