// Teller.h
#ifndef TELLER_H
#define TELLER_H

#include "Customer.h"

class Teller
{
public:
    Teller() : isFree(true), transactionTime(0), currentCustomer(nullptr) {}

    bool IsFree() const
    {
        return isFree;
    }

    void SetBusy()
    {
        isFree = false;
    }

    void SetFree()
    {
        isFree = true;
        transactionTime = 0;
        currentCustomer = nullptr;
    }

    void SetTransactionTime(int time)
    {
        transactionTime = time;
    }

    void SetCurrentCustomer(Customer& customer)
    {
        currentCustomer = &customer;
    }

    int GetRemainingTransactionTime() const
    {
        return transactionTime;
    }

    int GetCurrentCustomerNumber() const
    {
        return (currentCustomer != nullptr) ? currentCustomer->GetCustomerNumber() : -1;
    }

    int GetCurrentCustomerArrivalTime() const
    {
        return (currentCustomer != nullptr) ? currentCustomer->GetArrivalTime() : -1;
    }

    int GetCurrentCustomerWaitingTime() const
    {
        return (currentCustomer != nullptr) ? currentCustomer->GetWaitingTime() : -1;
    }

    int GetCurrentCustomerTransactionTime() const
    {
        return (currentCustomer != nullptr) ? currentCustomer->GetTransactionTime() : -1;
    }

    void DecreaseTransactionTime()
    {
        if (transactionTime > 0)
        {
            transactionTime--;
        }
    }

private:
    bool isFree;
    int transactionTime;
    Customer* currentCustomer;
};

#endif // Teller_H
