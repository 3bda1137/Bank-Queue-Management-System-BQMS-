#ifndef CUSTOMER_H
#define CUSTOMER_H


class Customer
{
private:
    int customerNumber;
    int arrivalTime;
    int waitingTime;
    int transactionTime;
public:
    //constructor
    Customer(int customerNumber, int arrivalTime,int waitingTime, int transactionTime)
    {
        InitializeCustomer(customerNumber, arrivalTime, waitingTime, transactionTime);
    }
    //Initialize field of the Customer
    InitializeCustomer(int customerNumber, int arrivalTime,int waitingTime, int transactionTime)
    {
        this->customerNumber = customerNumber;
        this->arrivalTime = arrivalTime;
        this->waitingTime = waitingTime;
        this->transactionTime = transactionTime;
    }

    // return  the value ofwaitingTime
    int GetWaitingTime()
    {
        return waitingTime;
    }

    // return  the value ofwaitingTime of customer
    IncrementWaitingTime()
    {
        waitingTime++;
    }
     // return  the value ofwaitingTime of customer
    void SetWaitingTime(int waitingTime)
    {
        this->waitingTime=waitingTime;
    }
    // return  the value arrivalTime of customer
    int GetArrivalTime()
    {
        return this->arrivalTime;
    }
    // return  the value transactionTime of customer
    int GetTransactionTime()
    {
        return this->transactionTime;
    }
    // return the Number of Customer
    int GetCustomerNumber()
    {
        return this->customerNumber;
    }
};

#endif // CUSTOMER_H
