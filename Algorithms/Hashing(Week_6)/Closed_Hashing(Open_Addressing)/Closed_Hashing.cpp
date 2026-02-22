#include <iostream>
using namespace std;

int arr[10], idx = 0;
bool occupied[10];
int length = 10;

// SIZE MATTERS IN HASHING BECAUSE IT DETERMINES HOW MANY SLOTS ARE AVAILABLE.
// A SMALL OR NON-PRIME SIZE CAN CAUSE MORE COLLISIONS, MAKING HASHING SLOWER.
// USING A PRIME SIZE HELPS SPREAD KEYS MORE UNIFORMLY, REDUCING COLLISIONS.
// EXAMPLE: IF TABLE SIZE = 10 AND KEYS = 5, 10, 15, 20 THEN ALL MAP TO INDEX 0 (COLLISION).
// BUT IF TABLE SIZE = 11 (PRIME), KEYS MAP TO 5, 10, 4, 9 RESPECTIVELY, REDUCING COLLISIONS.
    
int linearProbing(int value, int i)
{
    // int idx = value % length;
    if (i >= length)
    {
        return -1;
    }

    idx = (value % length + i) % length;

    if (occupied[idx] == false)
    {
        occupied[idx] = true;
        return idx;
    }

    else
    {
        idx = linearProbing(value, i + 1);
        return idx;
    }
}
// SO WHAT QUADRATIC PROBING DOES IS IT INCREASES BY i^2 INSTEAD OF JUST i+1 LIKE IN LINEAR PROBING WHEN THAT INDEX IS FILLED IN ORDER TO DEAL WITH COLLISION.

int quadraticProbing(int val, int i)
{
    if (i >= length)
    {
        return -1;
    }

    idx = (val % length + (i * i)) % length;

    if (occupied[idx] == false)
    {
        occupied[idx] = true;
        return idx;
    }

    else
    {
        idx = quadraticProbing(val, i + 1);
        return idx;
    }
}
void insert(int val)
{
    idx = linearProbing(val, 0);
    // idx = quadraticProbing(val, 0);
    if (idx == -1)
    {
        cout << "No Space Left Inside Table";
        return;
    }
    arr[idx] = val;
}

void display(int *arr, int i)
{
    if (i >= 10)
    {
        return;
    }
    cout << arr[i] << " ";
    display(arr, i + 1);
}
bool search(int val, int i)
{
    if (i >= length)
    {
        return false;
    }
    idx = (val % length + i) % length;

    if (occupied[idx] == false)
    {
        return false;
    }

    if (val == arr[idx])
    {
        return true;
    }
    else
    {
        return search(val, i + 1);
    }
}
void remove(int val, int i)
{
    if (!search(val, i))
    {
        cout << "Value not found to delete";
        return;
    }
    occupied[idx] = false;
    arr[idx] = 0;
    cout << "Deleted Successfully";
}

void insertQuadratic(int val)
{
    idx = quadraticProbing(val, 0);
    if (idx == -1)
    {
        cout << "No Space Left Inside Table";
        return;
    }
    arr[idx] = val;
}

bool searchQuadratic(int val, int i)
{
    if (i >= length)
    {
        return false;
    }
    idx = (val % length + (i * i)) % length;

    if (occupied[idx] == false)
    {
        return false;
    }

    if (val == arr[idx])
    {
        return true;
    }
    else
    {
        return searchQuadratic(val, i + 1);
    }
}

void removeQuadratic(int val, int i)
{
    if (!searchQuadratic(val, i))
    {
        cout << "Value not found to delete";
        return;
    }
    occupied[idx] = false;
    arr[idx] = 0;
    cout << "Deleted Successfully";
}
