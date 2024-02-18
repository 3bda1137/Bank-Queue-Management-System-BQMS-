#include <iostream>
#include <iomanip>
#include <fstream>
#include "WaitingCustomerQueue.h"
#include "TellerList.h"

using namespace std;

// Function to read customer data from the file and add them to the waiting queue
void readCustomerData(ifstream& inputFile, WaitingCustomerQueue& waitingQueue) {
    int customerNumber, arrivalTime, transactionTime;
    while (inputFile >> customerNumber >> arrivalTime >> transactionTime) {
        Customer newCustomer(customerNumber, arrivalTime, 0, transactionTime);
        waitingQueue.Add(newCustomer);
    }
    waitingQueue.SortQueue();
}

// Function to print table headers to console and file
void printTableHeaders(ofstream& outputFile) {
    cout << left << setw(10) << "Teller" << setw(15) << "Customer ID" << setw(15) << "Arrival Time"
         << setw(15) << "Service Time" << setw(15) << "Waiting Time" << setw(15) << "Leaving Time" << endl;

    outputFile << left << setw(10) << "Teller" << setw(15) << "Customer ID" << setw(15) << "Arrival Time"
               << setw(15) << "Service Time" << setw(15) << "Waiting Time" << setw(15) << "Leaving Time" << endl;
}

// Function to perform the simulation
void simulate(WaitingCustomerQueue& waitingQueue, TellerList& tellerList, ofstream& outputFile) {
    int completedTransactions = 0;
    int totalWaitingTimeAllCustomers = 0;
    int totalServiceTimeAllCustomers = 0;
    int maximumWaitingTime = 0;
int numberOfTellers=3;
    int totalArrivalTimeDifference = 0; // for calculating average arrival time difference
    int previousArrivalTime = 0;

    for (int i = 0; i < 100; i++) {
        if (!waitingQueue.IsEmpty()) {
            int tellerNumber;
            if ((tellerNumber = tellerList.GetFreeTellerNumber()) != -1) {
                Customer nextCustomer = waitingQueue.Front();
                waitingQueue.Delete();
                tellerList.SetTellerBusy(tellerNumber, nextCustomer);
                nextCustomer.SetDepartureTime();

                // Print table row to console and file
                cout << left << setw(10) << tellerNumber << setw(15) << nextCustomer.GetCustomerNumber()
                     << setw(15) << nextCustomer.GetArrivalTime() << setw(15) << nextCustomer.GetTransactionTime()
                     << setw(15) << nextCustomer.GetWaitingTime() << setw(15) << nextCustomer.GetDepartureTime() << endl;

                outputFile << left << setw(10) << tellerNumber << setw(15) << nextCustomer.GetCustomerNumber()
                           << setw(15) << nextCustomer.GetArrivalTime() << setw(15) << nextCustomer.GetTransactionTime()
                           << setw(15) << nextCustomer.GetWaitingTime() << setw(15) << nextCustomer.GetDepartureTime() << endl;

                // Additional calculations during the simulation

                // Calculate totalArrivalTimeDifference
                totalArrivalTimeDifference += (nextCustomer.GetArrivalTime() - previousArrivalTime);
                previousArrivalTime = nextCustomer.GetArrivalTime();

                completedTransactions++;
                totalWaitingTimeAllCustomers += nextCustomer.GetWaitingTime();
                totalServiceTimeAllCustomers += nextCustomer.GetTransactionTime();

                // Track maximum waiting time
                if (nextCustomer.GetWaitingTime() > maximumWaitingTime) {
                    maximumWaitingTime = nextCustomer.GetWaitingTime();
                }
            } else if (waitingQueue.Front().GetArrivalTime() == i) {
                waitingQueue.UpdateWaitingQueue();
            }
            tellerList.UpdateTellers();
        }
    }

    // Calculate and print statistics
    double averageArrivalTimeDifference = static_cast<double>(totalArrivalTimeDifference) / completedTransactions;
    double averageWaitingTime = static_cast<double>(totalWaitingTimeAllCustomers) / completedTransactions;
    double averageServiceTime = static_cast<double>(totalServiceTimeAllCustomers) / completedTransactions;
    double percentageCustomersServed = (completedTransactions > 0) ?
                                   (static_cast<double>(completedTransactions) / (completedTransactions + waitingQueue.GetCurrentSize())) * 100 : 0.0;
 cout << "\nStatistics:\n";
    cout << "Number of Tellers: " << numberOfTellers << endl;
    cout << "Average arrival time difference between customers: " << averageArrivalTimeDifference << endl;
    cout << "Total waiting time: " << totalWaitingTimeAllCustomers << endl;
    cout << "Number of customers that completed a transaction: " << completedTransactions << endl;
    cout << "Average waiting time: " << averageWaitingTime << endl;
    cout << "Total Service Time: " << totalServiceTimeAllCustomers << endl;
    cout << "Maximum Waiting Time: " << maximumWaitingTime << endl;
    cout << "Average Service Time: " << averageServiceTime << endl;
    cout << "Percentage of Customers Served: " << percentageCustomersServed << "%" << endl;

    outputFile << "\nStatistics:\n";
    outputFile << "Number of Tellers: " << numberOfTellers << endl;
    outputFile << "Average arrival time difference between customers: " << averageArrivalTimeDifference << endl;
    outputFile << "Total waiting time: " << totalWaitingTimeAllCustomers << endl;
    outputFile << "Number of customers that completed a transaction: " << completedTransactions << endl;
    outputFile << "Average waiting time: " << averageWaitingTime << endl;
    outputFile << "Total Service Time: " << totalServiceTimeAllCustomers << endl;
    outputFile << "Maximum Waiting Time: " << maximumWaitingTime << endl;
    outputFile << "Average Service Time: " << averageServiceTime << endl;
    outputFile << "Percentage of Customers Served: " << percentageCustomersServed << "%" << endl;
}

int main() {

    ifstream inputFile("CustomersData.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file.\n";
        return 1;
    }

    int numberOfTellers = 3;
    WaitingCustomerQueue waitingQueue(100);
    TellerList tellerList(numberOfTellers);

    // Read customer data and add to the waiting queue
    readCustomerData(inputFile, waitingQueue);

    // Set precision for floating-point output
    cout << fixed << setprecision(2);

    // Open the file for writing results
    ofstream outputFile("SimulationResults.txt");
    if (!outputFile.is_open()) {
        cerr << "Error: Could not open the output file.\n";
        return 1;
    }

    // Print table headers to console and file
    printTableHeaders(outputFile);

    // Simulate and calculate statistics
    simulate(waitingQueue, tellerList, outputFile);

    // Close the output file
    outputFile.close();

    inputFile.close();
    return 0;
}
