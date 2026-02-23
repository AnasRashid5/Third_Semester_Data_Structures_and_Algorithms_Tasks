#include <iostream>
using namespace std;

class StaticQueue
{
    // LINEAR QUEUE::

    // QUEUE HAS TWO ACCESS POINTS. 1)REAR FROM WHERE VALUE ENTERS. 2) FRONT FROM WHERE VALUE EXITS.
    // WE CAN TAKE THE EXAMPLE OF REAL LIFE QUEUE MADE IN BANKS,SCHOOLS ETC.USER ENTER FROM REAR SERVED AND THEN EXITS FROM FIRST.
    // BASICALLY, QUEUE OPERATES ON FIFO(FIRST IN FIRST OUT) PRINCIPLE.

    // private:
    //     int arr[4];
    //     int size = 4;
    //     int count = 0;
    //     // FRONT,REAR ARE FOR TRACKING THE ELEMENTS IN QUEUE.BOTH REAR,FRONT=-1 MEANS QUEUE IS EMPTY.
    //     int rear = -1, front = -1;

    // public:
    //     // ENQUEUE FUNCTION IS FOR INSERTING ELEMENTS INSIDE QUEUE.
    //     // DEQUEUE FOR REMOVING THEM.
    //     void enqueue(int val)
    //     {

    //         if (front == -1 && rear == -1)
    //         {
    //             front++, rear++;
    //         }

    //         if (rear == size)
    //         {
    //             cout << "Queue Overflow" << endl;
    //             return;
    //         }

    //         arr[rear] = val;
    //         rear++;
    //         count++;
    //     }
    //     int dequeue()
    //     {
    //         // DEQUEUE REMOVES THE FIRST ELEMENT INSERTED INSIDE ARRAY.

    //         if (count == 0)
    //         {
    //             cout << "Queue Underflow" << endl;
    //             rear = -1;
    //             front = -1;
    //             return 404;
    //         }

    //         int elem = arr[front];
    //         front++;
    //         count--;
    //         return elem;
    //     }

    //     void display()
    //     {

    //         if (count == 0)
    //         {
    //             cout << "empty queue";
    //             return;
    //         }
    //         for (int i = front; i < rear; i++)
    //         {

    //             cout << arr[i] << " ";
    //         }
    //         cout << endl;
    //     }

    // Circular Queue::

private:
    int arr[4];
    int size = 4;
    int count = 0;
    // FRONT,REAR ARE FOR TRACKING THE ELEMENTS IN QUEUE.BOTH REAR,FRONT=-1 MEANS QUEUE IS EMPTY.
    int rear = -1, front = -1;

public:
    // ENQUEUE FUNCTION IS FOR INSERTING ELEMENTS INSIDE QUEUE.
    // DEQUEUE FOR REMOVING THEM.
    void enqueue(int val)
    {

        if (front == -1 && rear == -1)
        {
            front++, rear++;
        }

        if (count == size)
        {
            cout << "Queue Overflow" << endl;
            return;
        }

        if (rear == size && count < 4)
        {
            rear = 0;
        }

        arr[rear] = val;
        rear++;
        count++;
    }
    int dequeue()
    {
        // DEQUEUE REMOVES THE FIRST ELEMENT INSERTED INSIDE ARRAY.

        if (count == 0)
        {
            cout << "Queue Underflow" << endl;
            rear = -1;
            front = -1;
            return 404;
        }
        if (front == size)
        {
            front = -1;
        }

        int elem = arr[front];
        front++;
        count--;
        return elem;
    }

    void display()
    {

        if (count == 0)
        {
            cout << "empty queue";
            return;
        }

        for (int i = front; i < rear; i++)
        {

            cout << arr[i] << " ";
        }
        cout << endl;
    }
};