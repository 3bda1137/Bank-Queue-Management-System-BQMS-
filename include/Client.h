#ifndef CLIENT_H
#define CLIENT_H


class Customer
{
public:
    enum CustomerType { REGULAR, PRIORITY };

private:
    int id;
    int arrivalTime;
    int serviceTime;
    int completionTime;
    CustomerType type;

public:
    Customer(int _id, int _arrivalTime, CustomerType _type = REGULAR)
        : id(_id), arrivalTime(_arrivalTime), serviceTime(rand() % 10 + 1), type(_type), completionTime(-1) {}

    int getID() const
    {
        return id;
    }
    int getArrivalTime() const
    {
        return arrivalTime;
    }
    int getServiceTime() const
    {
        return serviceTime;
    }
    int getCompletionTime() const
    {
        return completionTime;
    }
    CustomerType getType() const
    {
        return type;
    }

    void setCompletionTime(int time)
    {
        completionTime = time;
    }

    friend std::ostream& operator<<(std::ostream& os, const Customer& customer)
    {
        os << "Customer " << customer.id << " (Type: " << (customer.type == REGULAR ? "Regular" : "Priority")
           << ", Arrival: " << customer.arrivalTime << ", Service: " << customer.serviceTime
           << ", Completion: " << (customer.completionTime == -1 ? "Not Completed" : std::to_string(customer.completionTime)) << ")";
        return os;
    }
};
#endif // CLIENT_H
