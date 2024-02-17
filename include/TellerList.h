// TellerList.h
#ifndef TELLERLIST_H
#define TELLERLIST_H
#include "Teller.h"
#include "Customer.h"
#include <iostream>

class TellerList
{
public:
    TellerList(int numberOfTellers)
    {
        this->numOfTellers = numberOfTellers;
        tellers = new Teller[numberOfTellers]; // Dynamically allocate an array of Tellers
    }

    int GetFreeTellerNumber()
    {
        for (int i = 0; i < numOfTellers; ++i)
        {
            if (tellers[i].IsFree())
            {
                return i + 1; // Return 1-based index
            }
        }
        return -1;
    }

    int GetNumberOfBusyTellers()
    {
        int busyTellers = 0;
        for (int i = 0; i < numOfTellers; ++i)
        {
            if (!tellers[i].IsFree())
            {
                busyTellers++;
            }
        }
        return busyTellers;
    }

    void SetTellerBusy(int tellerNum, Customer& currentCustomer, int transactionTime)
    {
        if (tellerNum > 0 && tellerNum <= numOfTellers)
        {
            tellers[tellerNum - 1].SetBusy();
            tellers[tellerNum - 1].SetTransactionTime(transactionTime);
            tellers[tellerNum - 1].SetCurrentCustomer(currentCustomer);
        }
    }
    void SetTellerBusy(int tellerNum, Customer& currentCustomer)
    {
        if (tellerNum > 0 && tellerNum <= numOfTellers)
        {
            tellers[tellerNum - 1].SetBusy();
            tellers[tellerNum - 1].SetTransactionTime(currentCustomer.GetTransactionTime());
            tellers[tellerNum - 1].SetCurrentCustomer(currentCustomer);
        }
    }

    void SetTellerFree(int tellerNum, Customer& currentCustomer)
    {
        if (tellerNum > 0 && tellerNum <= numOfTellers)
        {
            tellers[tellerNum - 1].SetFree();
        }
    }

    void UpdateTellers(std::ostream& outF)
    {
        for (int i = 0; i < numOfTellers; i++)
        {
            Teller& currentTeller = tellers[i];

            if (!currentTeller.IsFree())
            {
                currentTeller.DecreaseTransactionTime();

                if (currentTeller.GetRemainingTransactionTime() == 0)
                {
                   /* outF << "From Teller number " << (i + 1)
                         << " customer number " << currentTeller.GetCurrentCustomerNumber()
                         << "\n departed at clock unit " << (currentTeller.GetCurrentCustomerArrivalTime()
                                 + currentTeller.GetCurrentCustomerWaitingTime()
                                 + currentTeller.GetCurrentCustomerTransactionTime())
                         << std::endl;*/

                    currentTeller.SetFree();
                }
            }
        }
    }

    ~TellerList()
    {
        delete[] tellers; // Deallocate the dynamically allocated array
    }

private:
    int numOfTellers;
    Teller* tellers;
};

#endif // TELLERLIST_H
