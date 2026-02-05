#include <iostream>
#include <string>
using namespace std;

class Bubble_Sorter
{
private:
    int arr[8] = {33, 55, 44, 11, 10, 8, 4, 3};
    int n = 8;

public:
    void bubble_sort()
    {

        for (int i = 0; i < n-1; i++)
        {
            cout << "Pass " << i+1 << ":" << endl;
            for (int j = 0; j < n -i- 1; j++)
            {
                cout << "  Comparing arr[" << j << "]=" << arr[j]
                     << " and arr[" << j + 1 << "]=" << arr[j + 1];
                if (arr[j] > arr[j + 1])
                {
                    cout << "   SWAP!" << endl;
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    
                }
                else{

                    cout << "   No swap" << endl;
                }
            } 
            cout << "After Pass " << i+1 << ": ";
        for(int k = 0; k < n; k++) {
            cout << arr[k] << " ";
        }
        cout << endl;           
        }
    }

    string toString()
    {
        string result = "{";
        for (int i = 0; i < 8; i++)
        {
            result = result + to_string(arr[i]);
            if (i < 7)
            {
                result = result + ",";
            }
        }
        result = result + "}";
        return result;
    }
};