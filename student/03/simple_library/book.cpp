#include "book.hh"

#include <iostream>

namespace  {
    const int LOAN_PERIOD_LENGHT_DAYS = 28;
}

Book::Book(const std::string &author, const std::string &title):
    author_(author),
    title_(title),
    loan_date_(Date()),
    expiry_date_(Date()),
    is_loaned_(false)
{
}

void Book::print() const
{
    std::cout << author_ << " : " << title_ << std::endl;
    if(!is_loaned_){
        std::cout << "- available" << std::endl;
    }
    else{
        std::cout << "- loaned: ";
        loan_date_.print();
        std::cout <<"- to be returned: ";
        expiry_date_.print();
    }
}

void Book::loan(const Date &loan_date)
{
    if(!is_loaned_){
        std::cout <<"Already loaned: cannot be loaned" << std::endl;
        return;
    }

    loan_date_ = loan_date;
    expiry_date_ = loan_date;
    expiry_date_.advance(LOAN_PERIOD_LENGHT_DAYS);
    is_loaned_ = true;
}

void Book::renew()
{
    if(!is_loaned_){
        std::cout <<"Not loaned: cannot be renewed" << std::endl;
        return;
    }
    expiry_date_.advance(LOAN_PERIOD_LENGHT_DAYS);
}

void Book::give_back()
{
    is_loaned_ = false;
}
