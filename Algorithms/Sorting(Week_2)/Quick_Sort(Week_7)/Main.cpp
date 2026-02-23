#include <iostream>
#include "Quick_Sort.cpp"
using namespace std;

int main()
{
    Quick_Sort sorter;

    int arr[10] = {77, 82, 11, 54, 76, 57, 25, 98, 59, 101};
    int left = 0, right = size(arr) - 1;

    cout << "Before Quick Sorting:" << endl;
    // cout<<
    sorter.display(arr);
    cout << endl;

    sorter.quick_sort(arr, left, right);

    cout << "After Sorting:" << endl;
    // cout<<
    sorter.display(arr);
}