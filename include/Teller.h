#ifndef TELLER_H
#define TELLER_H
#include <string>
using namespace std;
class Teller
{
public:
    //constructor
    Teller()
    {
        status = "free";
        transactionTime = 0;
    }
    //Check if Teller is free or not
    bool IsFree()
    {
        return this->status=="free";
    }
    // make the teller 'busy'
    void SetBusy()
    {
        this->status="busy";
    }
    // make the teller 'free'
    void SetFree()
    {
        this->status="free";
    }
    // set transaction Time
    void SetTransactionTime(int transactionTime)
    {
        this->transactionTime = transactionTime;//currentCustomer.GetTransactionTime();
    }
    //Decrease Transaction Time of customer
    void DecreaseTransactionTime()
    {
        if (transactionTime > 0)
            this->transactionTime--;
    }
    //assign customer to teller
    void SetCurrentCustomer(const Customer& customer)
    {
        currentCustomer = customer;
    }

    int GetCurrentCustomerNumber()
    {
        return currentCustomer.GetCustomerNumber();
    }

    int GetCurrentCustomerArrivalTime()
    {
        return currentCustomer.GetArrivalTime();
    }
    //return the Transaction Time of Current Customer
    int GetCurrentCustomerTransactionTime()
    {
        return this->transactionTime;
    }

private:
    Customer currentCustomer;
    string status;
    int transactionTime;
};

#endif // TELLER_H
