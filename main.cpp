#include <iostream>
#include <iomanip>
#include <fstream>
#include "WaitingCustomerQueue.h"
#include "TellerList.h"

using namespace std;

int main()
{
    ifstream inputFile("CustomersData.txt");

    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open the file.\n";
        return 1;
    }

    // Create a waiting queue and teller list
    WaitingCustomerQueue waitingQueue(100);
    TellerList tellerList(3);
    int customerNumber, arrivalTime, transactionTime;
    int completedTransactions = 0;
    int totalWaitingTimeAllCustomers = 0;
    int customersLeftInServers = 0;
    int totalArrivalTimeDifference = 0; // for calculating average arrival time difference
    int previousArrivalTime = 0;

    // Read customer data from the file and add them to the waiting queue
    while (inputFile >> customerNumber >> arrivalTime >> transactionTime)
    {
        Customer newCustomer(customerNumber, arrivalTime, 0, transactionTime);
        waitingQueue.Add(newCustomer);
    }
    waitingQueue.SortQueue();

    // Set precision for floating-point output
    cout << fixed << setprecision(2);

    // Print table headers
    cout << left << setw(10) << "Teller" << setw(15) << "Customer ID" << setw(15) << "Arrival Time"
         << setw(15) << "Service Time" << setw(15) << "Waiting Time" << setw(15) << "Leaving Time" << endl;

    // Simulation loop
    for (int i = 0; i < 100; i++)
    {
        if (!waitingQueue.IsEmpty())
        {
            int tellerNumber;
            if ((tellerNumber = tellerList.GetFreeTellerNumber()) != -1)
            {
                Customer nextCustomer = waitingQueue.Front();
                waitingQueue.Delete();
                tellerList.SetTellerBusy(tellerNumber, nextCustomer);
                nextCustomer.SetDepartureTime();

                // Print table row
                cout << left << setw(10) << tellerNumber << setw(15) << nextCustomer.GetCustomerNumber()
                     << setw(15) << nextCustomer.GetArrivalTime() << setw(15) << nextCustomer.GetTransactionTime()
                     << setw(15) << nextCustomer.GetWaitingTime() << setw(15) << nextCustomer.GetDepartureTime() << endl;

                // Additional calculations during the simulation

                // Calculate totalArrivalTimeDifference
                totalArrivalTimeDifference += (nextCustomer.GetArrivalTime() - previousArrivalTime);
                previousArrivalTime = nextCustomer.GetArrivalTime();

                completedTransactions++;
                totalWaitingTimeAllCustomers += nextCustomer.GetWaitingTime();
            }
            else if (waitingQueue.Front().GetArrivalTime() == i)
            {
                waitingQueue.UpdateWaitingQueue();
            }
            tellerList.UpdateTellers();
        }
    }

    // Calculate average arrival time difference
    double averageArrivalTimeDifference = static_cast<double>(totalArrivalTimeDifference) / completedTransactions;

    // Calculate average waiting time
    double averageWaitingTime = static_cast<double>(totalWaitingTimeAllCustomers) / completedTransactions;

    // Print statistics
    cout << "\nStatistics:\n";
    cout << "Number of servers: " << 3 << endl;
    // You can replace "/* Calculate average transaction time */" with the actual calculation
    cout << "Average transaction time: " << "/* Calculate average transaction time */" << endl;
    cout << "Average arrival time difference between customers: " << averageArrivalTimeDifference << endl;
    cout << "Total waiting time: " << totalWaitingTimeAllCustomers << endl;
    cout << "Number of customers that completed a transaction: " << completedTransactions << endl;
    cout << "Number of customers left in the servers: " << customersLeftInServers << endl;
    cout << "Average waiting time: " << averageWaitingTime << endl;

    cout << "************** END SIMULATION *************\n";

    inputFile.close();
    return 0;
}
