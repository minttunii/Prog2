#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), has_credit_(has_credit), balance_(0), iban_(""),
    credit_limit_(0)
{
    generate_iban();
}

void Account::print() const
{
    std::cout << owner_ << " : " << iban_ << " : " << balance_ << std::endl;
}

void Account::set_credit_limit(int credit_limit)
{
    // Vain luottokortti-tilille voi asettaa luottorajan
    if(has_credit_){
        credit_limit_ = credit_limit;
    }
    else{
        std::cout <<"Cannot set credit limit: the account has no credit card" << std::endl;
    }
}

void Account::save_money(int save)
{

}

void Account::take_money(int take)
{

}

void Account::transfer_to(const Account &savings_account, int transfer)
{

}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}
