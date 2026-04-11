#include <iostream>
using namespace std;

int arr[15];
int i = 0, sizeArr = 0;

void upHeapify(int array[], int index)
{

    // index out of bounds bc when it will reach to parent or index=-1
    if (index == 0)
    {
        return;
    }

    int parent = (index - 1) / 2;

    if (arr[index] > arr[parent])
    {
        swap(arr[index], arr[parent]);
    }
    else
    {
        return;
    }
    upHeapify(arr, parent);
}

void downHeapify(int arr[], int index, int size)
{
    int child1 = (2 * index) + 1;
    int child2 = (2 * index) + 2;

    int largestIdx = index;

    // first we will compare the two child of a parent the largest among them will be compared with parent and if parent small then it will be swapped

    if (child1 < size && arr[child1] > arr[largestIdx])
    {
        largestIdx = child1;
    }
    if (child2 < size && arr[child2] > arr[largestIdx])
    {
        largestIdx = child2;
    }
    if (largestIdx != index)
    {
        swap(arr[largestIdx], arr[index]);
        downHeapify(arr, largestIdx, size);
    }
}

void insert(int val)
{
    arr[i] = val;
    i++;
    sizeArr = i;
    if (i > 0)
    {
        upHeapify(arr, i - 1);
    }
}

void del()
{
    // int sizeofArr = sizeof(arr) / sizeof(arr[0]);
    swap(arr[0], arr[i - 1]);
    i--;
    // sizeArr = i;
    downHeapify(arr, 0, i);
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
        cout << arr[i] << endl;
    }
}

void display()
{
    for (int i = 0; i < sizeArr; i++)
    {
        cout << arr[i] << " -> " << arr[(2 * i) + 1] << "," << arr[(2 * i) + 2] << endl;
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
