#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>

class Account
{
public:
    // Constructor
    Account(const std::string& owner, bool has_credit = false);

    // More methods

    void print() const;
    void set_credit_limit(int credit_limit);
    void save_money(int save);
    void take_money(int take);
    void transfer_to(const Account& savings_account, int transfer);

private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();

    // Used for generating IBAN.
    // Static keyword means that the value of running_number_ is the same for
    // all Account objects.
    // In other words, running_number_ is a class-wide attribute, there is
    // no own copies of it for each object of the class.
    static int running_number_;

    // More attributes/methods

    const std::string& owner_;
    bool has_credit_;
    int balance_;
    std::string iban_;
    int credit_limit_;

};

#endif // ACCOUNT_HH
