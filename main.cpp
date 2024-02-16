#include <iostream>
#include "TellerList.h"
#include "Customer.h"

using namespace std;

int main()
{
    // Create a TellerList with 2 tellers
    TellerList tellerList(3);

    // Create sample customers
    const int numCustomers = 7;
    Customer customers[numCustomers] = {
        {1, 5, 0, 3},
        {2, 8, 0, 6},
        {3, 10, 0, 4},
        {4, 15, 0, 8},
        {5, 18, 0, 5},
        {6, 20, 0, 7},
        {7, 25, 0, 10}
    };

    // Simulate customers arriving and being served
    for (int i = 0; i < numCustomers; ++i)
    {
        int freeTellerNum = tellerList.GetFreeTellerNumber();

        if (freeTellerNum != -1)
        {
            tellerList.SetTellerBusy(freeTellerNum, customers[i]);
            cout << "Teller " << freeTellerNum << " is now busy with customer " << customers[i].GetCustomerNumber() << "." << endl;
        }
        else
        {
            cout << "All tellers are busy. Customer " << customers[i].GetCustomerNumber() << " has to wait." << endl;
        }

        // Simulate the passage of time
        tellerList.UpdateTellers(cout);
    }

    return 0;
}
