#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <ctime>
#include "TellerList.h"
#include "WaitingCustomerQueue.h"
using namespace std;

void setSimulationParameters(int& sTime, int& numOfServers, int& tBetweenCArrival)
{
    cout << "Enter the simulation time: ";
    cin >> sTime;
    cout << "Enter the number of servers: ";
    cin >> numOfServers;
    cout << "Enter the average time between customer arrivals: ";
    cin >> tBetweenCArrival;
}

void runSimulation(int simulationTime, int numOfServers, int tBetweenCArrival)
{
    TellerList tellerList(numOfServers);
    WaitingCustomerQueue waitingCustomersQueue(100);

    int clock;
    int totalWait = 0;
    int numOfCustomers = 0;
    int numOfServedCustomers = 0;

    srand(time(0));
    vector<Customer> servedCustomers;
    vector<int> clientsServedByServer(numOfServers, 0);

    cout << "------------------------------------------------------------------------------" << endl;
    cout << "| Customer ID | Arrival Time | Service Time | Waiting Time | Departure Time |" << endl;
    cout << "------------------------------------------------------------------------------" << endl;

    for (clock = 1; clock <= simulationTime; clock++)
    {
        // Step 2.1: Update the server list to decrement the transaction time of each busy server by one time unit.
        tellerList.UpdateTellers(cout);

        // Step 2.2: If the customer’s queue is nonempty, increment the waiting time of each customer by one time unit.
        waitingCustomersQueue.UpdateWaitingQueue();

        // Step 2.3: If a customer arrives, increment the number of customers by 1 and add the new customer to the queue.
        int arrivalInterval = rand() % tBetweenCArrival + 1;  // Random arrival time interval
        if (clock % arrivalInterval == 0)
        {
            // Generate a random transaction time between 2 and 20 for each arriving customer
            int transactionTime = rand() % 19 + 2;

            // Create a new customer with a random transaction time and arrival time
            Customer newCustomer(numOfCustomers + 1, clock, 0, transactionTime);

            // Add the new customer to the waiting queue
            waitingCustomersQueue.Add(newCustomer);

            numOfCustomers++;
        }

        // Step 2.4: If a server is free and the customer’s queue is nonempty,
        // remove a customer from the front of the queue and send the customer to the free server.
        int freeTellerNum = tellerList.GetFreeTellerNumber();
        if (freeTellerNum != -1 && !waitingCustomersQueue.IsEmpty())
        {
            Customer servedCustomer = waitingCustomersQueue.Front();
            waitingCustomersQueue.Delete();

            totalWait += clock - servedCustomer.GetArrivalTime();

            // Calculate departure time
            int departureTime = clock + servedCustomer.GetTransactionTime();

            // Update the server list and track the number of clients served
            tellerList.SetTellerBusy(freeTellerNum, servedCustomer);
            clientsServedByServer[freeTellerNum]++;

            // Store detailed information for later analysis
            servedCustomer.SetDepartureTime(departureTime);
            servedCustomers.push_back(servedCustomer);

            // Print customer details in a table
            cout << "| " << setw(12) << "ID-" + to_string(servedCustomer.GetCustomerNumber())
                 << " | " << setw(13) << servedCustomer.GetArrivalTime()
                 << " | " << setw(12) << servedCustomer.GetTransactionTime()
                 << " | " << setw(13) << clock - servedCustomer.GetArrivalTime()
                 << " | " << setw(16) << servedCustomer.GetDepartureTime() << " |" << endl;

            numOfServedCustomers++;
        }
    }

    // Print how many clients each server served
    cout << "Number of clients served by each server:" << endl;
    for (int i = 0; i < numOfServers; i++)
    {
        cout << "Server " << i + 1 << ": " << clientsServedByServer[i] << " clients" << endl;
    }

    // Find the server that served the most clients
    int maxClientsServed = 0;
    int maxClientsServedServer = -1;
    for (int i = 0; i < numOfServers; i++)
    {
        if (clientsServedByServer[i] > maxClientsServed)
        {
            maxClientsServed = clientsServedByServer[i];
            maxClientsServedServer = i;
        }
    }

    // Print the server that served the most clients
    cout << "Server that served the most clients: Server " << maxClientsServedServer + 1
         << " with " << maxClientsServed << " clients served" << endl;

    // Print the results
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "Simulation ran for " << simulationTime << " time units." << endl;
    cout << "Number of servers: " << numOfServers << endl;
    cout << "Average arrival time difference between customers: " << tBetweenCArrival << endl;
    cout << "Total waiting time: " << totalWait << endl;
    cout << "Number of customers that completed a transaction: " << numOfServedCustomers << endl;
    cout << "Number of customers left in the servers: " << tellerList.GetNumberOfBusyTellers() << endl;
    cout << "The number of customers left in the queue: " << waitingCustomersQueue.GetCurrentSize() << endl;
    cout << "Average waiting time: " << (numOfServedCustomers > 0 ? static_cast<double>(totalWait) / numOfServedCustomers : 0) << endl;
    cout << "************** END SIMULATION *************" << endl;
}

int main()
{
    // Seed the random number generator
    srand(static_cast<unsigned>(time(0)));

    int simulationTime, numOfServers, tBetweenCArrival;

    // Set simulation parameters
    setSimulationParameters(simulationTime, numOfServers, tBetweenCArrival);

    // Run the simulation
    runSimulation(simulationTime, numOfServers, tBetweenCArrival);

    return 0;
}
