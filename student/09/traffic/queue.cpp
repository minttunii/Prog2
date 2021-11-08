#include "queue.hh"
#include <iostream>

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle)
    : cycle_(cycle)
{
}

Queue::~Queue()
{
    Vehicle* current = first_;
    Vehicle* next = nullptr;

    while(current != nullptr){
        next = current->next;
        delete current;
        current = next;
    }
}

void Queue::enqueue(const string &reg)
{
    if(is_green_){
        std::cout << "GREEN: The vehicle " << reg <<
                     " need not stop to wait" << std::endl;
        return;
    }

    Vehicle* new_car = new Vehicle{reg, nullptr};

    if(is_empty()){
        first_ = new_car;
        last_ = new_car;
        return;
    }

    Vehicle* old_last = last_;
    old_last->next = new_car;
    last_ = new_car;
}

void Queue::switch_light()
{
    is_green_ = !is_green_;

    if(is_empty()){
        print();
        return;
    }

    if(is_green_){
        string reg_number = "";
        std::cout << "GREEN: Vehicle(s) ";
        for(unsigned i = 0; i < cycle_; ++i){

            if(is_empty()){
                break;
            }
            deque(reg_number);
            std::cout<< reg_number << " ";

        }
        std::cout << "can go on" << std::endl;
        is_green_ = false;
    }
}

void Queue::deque(string &reg_number)
{
    if(!is_empty()){
        reg_number = first_->reg_num;

        if(first_ == last_){
            last_ = nullptr;
        }
        Vehicle* current = first_;
        first_ = first_->next;
        delete current;
    }
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::print() const
{
    if(is_green_){
        std::cout << "GREEN: ";
    }
    else{
        std::cout << "RED: ";
    }

    if(is_empty()){
        std::cout << "No vehicles waiting in traffic lights" << std::endl;
        return;
    }

    std::cout << "Vehicle(s) ";
    Vehicle* current = first_;
    while(current != nullptr){
        std::cout << current->reg_num << " ";
        current = current->next;
    }
    std::cout << "waiting in traffic lights" << std::endl;
}

bool Queue::is_empty() const
{
    return first_ == nullptr;
}
