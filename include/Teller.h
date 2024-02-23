// Teller.h
#ifndef TELLER_H
#define TELLER_H

#include "Customer.h"

class Teller
{
public:
    Teller()
    {
        this->isFree=true;
        this->currentCustomer=nullptr;
        this->transactionTime=0;
    }

    bool IsFree()
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
    void SetTransactionTime()
    {
        if(currentCustomer != nullptr)
            transactionTime = currentCustomer->GetTransactionTime();
    }

    void SetCurrentCustomer(Customer& customer)
    {
        currentCustomer = &customer;
        SetTransactionTime();
    }

    int GetRemainingTransactionTime()
    {
        return this->transactionTime;
    }

    int GetCurrentCustomerNumber()
    {
        if (currentCustomer != nullptr)
        {
            return currentCustomer->GetCustomerNumber();
        }
        else
        {
            return -1;
        }
    }

    int GetCurrentCustomerArrivalTime()
    {
        if (currentCustomer != nullptr)
        {
            return currentCustomer->GetArrivalTime();
        }
        else
        {
            return -1;
        }
    }

    int GetCurrentCustomerWaitingTime()
    {
        if (currentCustomer != nullptr)
        {
            return currentCustomer->GetWaitingTime();
        }
        else
        {
            return -1;
        }
    }

    int GetCurrentCustomerTransactionTime()
    {
        if (currentCustomer != nullptr)
        {
            return currentCustomer->GetTransactionTime();
        }
        else
        {
            return -1;
        }
    }


    void DecreaseTransactionTime()
    {
        if (transactionTime > 0)
        {
            transactionTime--;
        }
    }
    void SetLevingTime()
    {
     levingTime=currentCustomer->GetDepartureTime();
    }
    int GetLevingTime()
    {
        return levingTime;
    }

private:
    bool isFree;//false or true
    int transactionTime;// transaction Time of customer
    Customer* currentCustomer;
    int levingTime;
};

#endif
