#include <iostream>
using namespace std;

int main()
{

    int arr[3] = {4, 3, 2};
    
    for (int i = 0; i < size(arr); i++)
    {
        // cout << "First for loop" << endl;
        int smallest = arr[i];
        int smallest_index = i;

        for (int j = i + 1; j < size(arr); j++)
        {
            // cout << "Second for loop" << endl;
            if (smallest > arr[j])
            {
                // cout << "Smallest  is " << smallest << endl;
                smallest = arr[j];
                smallest_index=j;
                // cout << "Smallest now is " << smallest << endl;
                // cout << "Smallest index is " << j << endl;
                //here we founded the smallest element.Now we have to just swap after 2nd loop.
                //b/c if we do inside 2nd loop elements will be swapped not guaranteeing the smallest element. 
            }
        }
        int temp=arr[i];
        arr[i]=arr[smallest_index];
        // cout<<"first elem is: "<<arr[i]<<endl;
        arr[smallest_index]=temp;
        // cout<<"2nd elem is now "<<arr[smallest_index]<<endl<<endl;
    }
    for (int i = 0; i < size(arr); i++)
    {
        /* code */
        cout << arr[i] << " ";
    }
}