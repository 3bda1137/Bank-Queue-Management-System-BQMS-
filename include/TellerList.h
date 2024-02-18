// TellerList.h
#ifndef TELLERLIST_H
#define TELLERLIST_H
#include "Teller.h"
#include "Customer.h"
#include <iostream>
using namespace std;
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
                return i + 1;
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


    void UpdateTellers()
    {
        for (int i = 0; i < numOfTellers; i++)
        {
            Teller& currentTeller = tellers[i];

            if (!currentTeller.IsFree())
            {
                currentTeller.DecreaseTransactionTime();
                //cout<<"Teller: "<<i+1<<"\tRemaining Time: "<<currentTeller.GetRemainingTransactionTime()<<endl;

                if (currentTeller.GetRemainingTransactionTime() == 0)
                {
                    currentTeller.SetFree();
                }
            }
        }
    }

    Teller GetTeller(int i)
    {
        return tellers[i];
    }

    ~TellerList()
    {
        delete[] tellers;
    }

private:
    int numOfTellers;
    Teller* tellers;
};

#endif // TELLERLIST_H
