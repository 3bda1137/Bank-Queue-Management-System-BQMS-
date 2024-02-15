#ifndef TELLERLIST_H
#define TELLERLIST_H
#include <queue>
using namespace std;
class TellerList
{
public:
    TellerList(int numberOfTellers)
    {
        this->numOfTellers = numberOfTellers;
        // Initialize the queue with default-constructed Teller objects
        this->tellers = queue<Teller>(deque<Teller>(numberOfTellers));
    }

    int GetFreeTellerNumber()
    {
        int tellerNum = -1;
        int i = 0;
        // Create a copy of the queue
        queue<Teller> tempQueue = this->tellers;
        while (!tempQueue.empty())
        {
            if (tempQueue.front().IsFree())
            {
                tellerNum = i;
                return tellerNum;
            }
            tempQueue.pop();
            i++;
        }
        // All tellers are busy
        return tellerNum;
    }

    int GetNumberOfBusyTellers()
    {
        int busyTellers = 0;
        // Create a copy of the queue
        queue<Teller> tempQueue = this->tellers;
        while (!tempQueue.empty())
        {
            if (!tempQueue.front().IsFree())
            {
                busyTellers++;
            }
            tempQueue.pop();
        }
        return busyTellers;
    }

    void SetTellerBusy(int tellerNum, Customer currentCustomer, int transactionTime)
    {
        // Move tellers from the front to the back until the busy one is reached
        while (tellerNum > 0)
        {
            this->tellers.push(this->tellers.front());
            this->tellers.pop();
            tellerNum--;
        }

        // Set the busy teller's properties
        this->tellers.front().SetBusy();
        this->tellers.front().SetTransactionTime(transactionTime);
        this->tellers.front().SetCurrentCustomer(currentCustomer);

        // Move the busy teller to the back
        this->tellers.push(this->tellers.front());
        this->tellers.pop();
    }

    void SetTellerBusy(int tellerNum, Customer currentCustomer)
    {
        // Move tellers from the front to the back until the busy one is reached
        while (tellerNum > 0)
        {
            this->tellers.push(this->tellers.front());
            this->tellers.pop();
            tellerNum--;
        }

        // Set the busy teller's properties without specifying transactionTime
        this->tellers.front().SetBusy();
        this->tellers.front().SetTransactionTime(currentCustomer.GetTransactionTime());
        this->tellers.front().SetCurrentCustomer(currentCustomer);

        // Move the busy teller to the back
        this->tellers.push(this->tellers.front());
        this->tellers.pop();
    }

    void UpdateTellers(ostream& outF)
    {
        for (int i = 0; i < this->numOfTellers; i++)
        {
            Teller& currentTeller = this->tellers.front();

            if (!currentTeller.IsFree())
            {
                currentTeller.DecreaseTransactionTime();

                if (currentTeller.GetRemainingTransactionTime() == 0)
                {
                    outF << "From Teller number " << (i + 1)
                         << " customer number " << currentTeller.GetCurrentCustomerNumber()
                         << "\n departed at clock unit " << (currentTeller.GetCurrentCustomerArrivalTime()
                                 + currentTeller.GetCurrentCustomerWaitingTime()
                                 + currentTeller.GetCurrentCustomerTransactionTime())
                         << endl;

                    currentTeller.SetFree();
                }
            }

            this->tellers.push(currentTeller);  // Move the processed tellers to the back
            this->tellers.pop();  // Remove the front teller
        }
    }


private:
    int numOfTellers;
    queue<Teller> tellers;
};

#endif // TELLERLIST_H
