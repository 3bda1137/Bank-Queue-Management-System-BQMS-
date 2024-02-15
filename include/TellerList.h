#ifndef TELLERLIST_H
#define TELLERLIST_H


class TellerList
{
public:
    TellerList(int numberOfTellers)
    {
        this->numOfTellers=numberOfTellers;
    }

    int GetFreeTellerNumber()
    {
        int tellerNum =-1;
        for (int i = 0; i < this->numOfTellers; i++)
        {
            if (this->tellers[i].IsFree())
            {
                tellerNum = i;
                return tellerNum;
            }
        }
        //all teller are busy
        return tellerNum;
    }

    int GetNumberOfBusyTellers()
    {
        int busyTellers = 0;
        for (int i = 0; i < this->numOfTellers; i++)
        {
            if (!this->tellers[i].IsFree())
            {
                busyTellers++;
            }
        }
        return busyTellers;
    }
    void SetTellerBusy(int tellerNum, Customer currentCustomer,int transactionTime)
    {
        this->tellers[tellerNum].SetBusy();
        this->tellers[tellerNum].SetTransactionTime(transactionTime);
        this->tellers[tellerNum].SetCurrentCustomer(currentCustomer);
    }
    void SetTellerBusy(int tellerNum, Customer currentCustomer)
    {
        this->tellers[tellerNum].SetBusy();
        this->tellers[tellerNum].SetTransactionTime(currentCustomer.GetTransactionTime());
        this->tellers[tellerNum].SetCurrentCustomer(currentCustomer);
    }

private:
    int numOfTellers;
    Teller *tellers;
};

#endif // TELLERLIST_H
