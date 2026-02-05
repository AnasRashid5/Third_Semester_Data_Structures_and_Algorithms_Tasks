#include <iostream>
using namespace std;
int main()
{
    int arr[5] = {7, 12, 3, 4, 1};

    for (int i = 1; i < size(arr); i++)
    {
        int elem = arr[i], j = i;

        while (j >= 1 && elem < arr[j - 1])
        {

            //so we can remove if() condition b/c our loop will be performing the same thing and work on similar condition.
         
            // if (elem < arr[j - 1])
            // {
                arr[j] = arr[j - 1];
            // }
            
            j--;
        }
        arr[j] = elem;
    }
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << endl;
    }
}