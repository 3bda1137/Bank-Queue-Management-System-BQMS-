#ifndef WAITINGCUSTOMERQUEUE_H
#define WAITINGCUSTOMERQUEUE_H
#include "MyQueue.h"

class WaitingCustomerQueue:public MyQueue<Customer>
{
public:
    WaitingCustomerQueue(int size):MyQueue<Customer>(size) {}

    void UpdateWaitingQueue()
    {
        Customer cust;
        cust.SetWaitingTime(-1);
        int wTime = 0;
        Add(cust);
        while (wTime !=-1)
        {
            Delete();
            wTime = cust.GetWaitingTime();
            if (wTime ==-1)
                break;
            cust.IncrementWaitingTime();
            Add(cust);
        }
    }
    void SortQueue()
    {
        // Bubble sort based on arrival time
        for (int i = 0; i < this->GetCurrentSize(); ++i)
        {
            for (int j = 0; j < this->GetCurrentSize() - 1; ++j)
            {
                if (this->arr[j].GetArrivalTime() > this->arr[j + 1].GetArrivalTime())
                {
                    // Swap customers
                    Customer temp = this->arr[j];
                    this->arr[j] = this->arr[j + 1];
                    this->arr[j + 1] = temp;
                }
            }
        }
    }
protected:

private:
};

#endif // WAITINGCUSTOMERQUEUE_H
