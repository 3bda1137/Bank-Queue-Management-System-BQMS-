#include <iostream>
#include "Customer.h"
using namespace std;

int main()
{
    Customer* regularCustomer = new Customer(1, 0); // ID: 1, Arrival Time: 0

    // Creating a priority customer
    Customer* priorityCustomer = new Customer(2, 5, Customer::VIP); // ID: 2, Arrival Time: 5, Type: Priority
    cout << "Priority Customer Details: " << *priorityCustomer << "\n";

    // Don't forget to delete the allocated memory to prevent memory leaks
    delete regularCustomer;
    delete priorityCustomer;
    return 0;
}
