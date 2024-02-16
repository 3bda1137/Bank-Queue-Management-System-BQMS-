#ifndef MYQUEUE_H
#define MYQUEUE_H



template<class T>
class MyQueue
{
public:
    MyQueue(int size)
    {
        if(size>0)
            MaxSize=size;
        else
            MaxSize=30;
        cont=0;
        front=0;
        rear=MaxSize-1;
        arr= new T[MaxSize];
    }
    bool IsEmpty()
    {
        return cont==0;
    }
    bool IsFull()
    {
        return cont==MaxSize;
    }
    bool Add(T item)
    {
        if(!IsFull())
        {
            cont++;
            rear=(rear+1)%MaxSize;
            arr[rear]=item;
            return true;
        }
        return false;
    }
    T Delete()
    {
        if(!IsEmpty())
        {
            cont--;
            T deletedElement=arr[front];
            front=(front+1)%MaxSize;

            return deletedElement;
        }
        throw std::runtime_error("Qeue is empty");
    }

    T Front()const
    {
        return arr[front];
    }
    T Rear()const
    {
        return arr[rear];
    }
    ~MyQueue()
    {
        delete []arr;
    }

private:
    int cont;
    int MaxSize;
    int front;
    int rear;
    T * arr;

};

#endif // MYQUEUE_H

