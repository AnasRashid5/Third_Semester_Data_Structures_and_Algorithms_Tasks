
#include <iostream>
#include <cmath>
using namespace std;

int heap[15];
int i = 0, sizeArr = 0;

void upHeapify(int array[], int index)
{

    // index out of bounds bc when it will reach to parent or index=-1
    if (index == 0)
    {
        return;
    }

    int parent = (index - 1) / 2;

    if (heap[index] > heap[parent])
    {
        swap(heap[index], heap[parent]);
    }
    else
    {
        return;
    }
    upHeapify(heap, parent);
}

void downHeapify(int heap[], int index, int size)
{
    int child1 = (2 * index) + 1;
    int child2 = (2 * index) + 2;

    int largestIdx = index;

    // first we will compare the two child of a parent the largest among them will be compared with parent and if parent small then it will be swapped

    if (child1 < size && heap[child1] > heap[largestIdx])
    {
        largestIdx = child1;
    }
    if (child2 < size && heap[child2] > heap[largestIdx])
    {
        largestIdx = child2;
    }
    if (largestIdx != index)
    {
        swap(heap[largestIdx], heap[index]);
        downHeapify(heap, largestIdx, size);
    }
}

void insert(int val)
{
    heap[i] = val;
    i++;
    sizeArr = i;
    if (i > 0)
    {
        upHeapify(heap, i - 1);
    }
}

void del()
{
    // int sizeofArr = sizeof(arr) / sizeof(arr[0]);
    swap(heap[0], heap[i - 1]);
    i--;
    // sizeheap = i;
    downHeapify(heap, 0, i);
}

void swap(int &greater, int &smaller)
{
    int temp = greater;
    greater = smaller;
    smaller = temp;
}

void heapSort(int size)
{
    int sizeArr = i;
    while (i > 1)
    {
        del();
    }
    for (int i = 0; i < sizeArr; i++)
    {
        cout << heap[i] << endl;
    }
}

// void display()
// {
//     for (int i = 0; i < sizeArr; i++)
//     {
//         cout << arr[i] << " -> " << arr[(2 * i) + 1] << "," << arr[(2 * i) + 2] << endl;
//     }
// }

void displayTree(int i)
{
    // basically we have calculated height using log base2 log2(sizeofarr)=log(size)/log(2)
    int heightFloat = log(sizeArr) / log(2); // this will give height of tree if we round down it using floor function..
    int height = floor(heightFloat);
    // here height is denoted.

    // level tells where are you currently in tree.
    // height tells total no of nodes present inside tree. Height=max no of edges from root to leaf node.
    // For printing each row we have to determine the level so spaces can be printed accordingly to no of nodes present in that level.

    // i am assuming tree/arr is {1,2,3,4,5,6,7}
    int level = 0, lvl = height;
    for (int j = 0; j <= height; j++)
    {
        int m = 0;
        while (m < lvl)
        {
            cout << " ";
            m++;
        }
        // int noOfNodes = 2 ^ level;//wrong due to syntax issue..
        int noOfNodes = pow(2, level);
        for (int k = 0; k < noOfNodes; k++)
        {
            if (i <= sizeArr)
            {
                cout << "  " << heap[i];
                i = i + 1;
            }
        }

        level = level + 1;
        lvl--;
        cout << endl; // we should change the line after one level
    }
}

void display()
{
    int c = 0;
    cout << "Press 1 for normal display.2 for tree structure display!: ";
    cin >> c;
    if (c == 1)
    {
        for (int i = 0; i < sizeArr; i++)
        {
            cout << heap[i] << endl;
        }
    }
    else if (c == 2)
    {
        displayTree(0);
    }
}

int main()
{
    int n, value, choice;
    bool exitProgram = false, heapsort = false;

    // int arr[6] = {1, 2, 3, 4, 5, 5};
    // cout<<sizeof(arr)/sizeof(arr[0]);

    while (!exitProgram)
    {
        cout << "\n===== HEAP MENU =====" << endl;
        cout << "1. Insert values" << endl;
        cout << "2. Delete a value" << endl;
        cout << "3. Heap Sort " << endl;
        cout << "4. Display" << endl;
        cout << "5. Exit program" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {

        case 1: // Insert
        {
            if (heapsort)
            {
                cout << "Cannot use insert functions as heap not follows heap property now!" << endl;
                break;
            }
            cout << "enter value to insert: ";
            cin >> value;
            insert(value);
            break;
        }

        case 2: // Delete
        {
            if (heapsort)
            {
                cout << "Cannot use delete functions as heap not follows heap property now!" << endl;
                break;
            }

            del();
            break;
        }

        case 3: // Heapsort
        {
            heapSort(i);
            heapsort = true;
            break;
        }
        case 4:
        {
            if (heapsort)
            {
                cout << "! Cannot use display functions as heap not follows heap property now!" << endl;
                break;
            }
            display();
            break;
        }
        case 5:
        {
            exitProgram = true;
            break;
        }

        default:
            cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
            break;
        }
    }

    return 0;
}