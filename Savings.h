#ifndef SAVINGS_H
#define SAVINGS_H

#include "Account.h"

class Savings : public Account {
public:
    void deposit(double, string) override;
    void withdraw(double, string) override;
    void display() override;
};

#endif // SAVINGS_H
