// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;

int main()
{
    // Write C++ code here

    bool flag = false;
    int toFind, l = 0, r = 9, mid,checkerR,counter=0,checkerL;
    int num[10] = {10, 22, 22, 45, 45, 45, 45, 81, 99, 101};

    std::cout << "Enter Number to be searched ";
    wcin >> toFind;

    while (l <= r)
    {
        mid = (l + r) / 2;
        checkerR=mid+1;
        checkerL=mid-1;
        

        if (toFind == num[mid])
        {
            flag = true;
            counter++;
            // break;

            while (checkerR<=9 && checkerL>=0)
            {
                /* code */
                if (toFind==num[checkerR])
                {
                    /* code */
                    counter++;
                }
                if (toFind==num[checkerL])
                {
                    /* code */
                    counter++;
                }
                checkerL--;
                checkerR++;
                
            }
           break;
        }




        if (toFind > num[mid])
        {
            l = mid + 1;

            checkerR=l;
            
            while (checkerR<=9)
            {
                /* code */
                if (toFind==num[checkerR])
                {
                    counter++;
                }
                checkerR++;                
            }
            break;
            
        }
        else
        {
            r = mid - 1;
            checkerL=r;
            
            while (checkerL>=0)
            {
                /* code */
                if (toFind==num[checkerL])
                {
                    counter++;
                }
                checkerL--;                
            }
            break;
        }
    }

    std::cout<<"Count is: "<<counter<<endl;
    if (!flag)
    {
        std::cout << "Not Found " << toFind;
    }
    else{
        std::cout<<"Found At "<<toFind;
    }
}