#ifndef CHECKINGS_H
#define CHECKINGS_H

#include "Account.h"

class Checkings : public Account {
public:

    void deposit(double, string) override;
    void withdraw(double, string) override;
    void display() override;
};

#endif // CHECKINGS_H
