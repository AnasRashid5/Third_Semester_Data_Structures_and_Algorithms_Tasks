#include <iostream>
using namespace std;

/*
QUICK SORT – DIVIDE AND CONQUER ALGORITHM

Idea:
Quick sort works by selecting a pivot element and rearranging the array
so that:

All elements smaller than pivot go to the left

All elements greater than pivot go to the right

Pivot reaches its correct sorted position

After that, the same process is applied recursively
to the left and right subarrays.*/

// TIME COMPLEXITY:

// Best Case: O(n log n)
// Average Case: O(n log n)
// Worst Case: O(n^2) (when selected pivot is either greatest or smallest element in array).

// SPACE COMPLEXITY:

// O(log n) due to recursion stack (average case)

class Quick_Sort
{
public:
    void quick_sort(int *array, int L, int R)
    {

        if (L < R)
        {

            int pivot_index = set_pivot(array, L, R);
            quick_sort(array, L, pivot_index - 1);
            quick_sort(array, pivot_index + 1, R);
        }
    }

    int set_pivot(int *array, int L, int R)
    {
        int piv_idx = (L + R) / 2;

        while (L < R)

        {

            while (piv_idx != R)
            {
                if (array[piv_idx] > array[R])
                {
                    int temp = array[piv_idx];
                    array[piv_idx] = array[R];
                    array[R] = temp;
                    piv_idx = R;
                    // R--;
                    break;
                }
                else
                {
                    R--;
                }
            }

            while (piv_idx > L)
            {
                if (array[piv_idx] < array[L])
                {
                    int temp = array[piv_idx];
                    array[piv_idx] = array[L];
                    array[L] = temp;
                    piv_idx = L;
                    break;
                }
                else
                {
                    L++;
                }
            }
        }
        return piv_idx;
    }
    void display(int *array)
    {
        for (int i = 0; i < 10; i++)
        {
            cout << array[i] << " ";
        }
    }
};