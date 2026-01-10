// Online C++ compiler to run C++ program online
#include <iostream>

int main()
{
    // Write C++ code here

    bool flag = false;
    int toFind, l = 0, r = 9, mid;
    int num[10] = {10, 22, 34, 45, 58, 69, 72, 81, 99, 101};

    std::cout << "Enter Number to be searched ";
    std::cin >> toFind;

    while (l <= r)
    {
        mid = (l + r) / 2;

        if (toFind == num[mid])
        {
            std::cout << "Found " << num[mid] << " at position " << (mid + 1);
            flag = true;
            break;
        }
        if (toFind > num[mid])
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    if (!flag)
    {
        std::cout << "Not Found " << toFind;
    }
}