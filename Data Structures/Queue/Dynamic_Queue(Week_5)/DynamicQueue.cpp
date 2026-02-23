#include <iostream>
using namespace std;

class DynamicQueue
{
private:
    int data;
    DynamicQueue *next = nullptr;

public:
    DynamicQueue *front = nullptr;
    DynamicQueue *rear = nullptr;

    void enqueue(int val)
    {
        DynamicQueue *temp = new DynamicQueue;
        temp->data = val;

        if (front == nullptr)
        {
            front = temp;
            rear = front;
            return;
        }

        rear->next = temp;
        rear = rear->next;
    }
    int dequeue()
    {
        if (front == nullptr)
        {
            cout << "Queue Underflow. ";
            return 404;
        }

        if (front->next == nullptr)
        {
            int elem = front->data;
            // free(rear);
            free(front);
            front = nullptr;
            return elem;
        }

        DynamicQueue *current = front;
        int elem = current->data;
        front = front->next;
        free(current);
        return elem;
    }
};