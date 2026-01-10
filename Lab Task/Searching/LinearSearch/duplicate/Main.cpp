// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;

int main() {
    // Write C++ code here
    bool flag=false;
    int toFind,count=0;
    int num[10]={77,88,88,88,88,55,87,54,54,10};
    
    std::cout << "Enter Number to be searched ";
    std::cin>>toFind;
           


    for(int i=0;i<10;i++){
        if(toFind==num[i]){
            flag=true;
            std::cout<<"Found at index "<<(i+1)<<endl;
            for (int i = 0; i < 10; i++)
            {
                if (toFind == num[i])
                {
                    count++;
                }
            }
            std::cout << "Found " << count << " times";
            break;
        }
    }
    if(flag==false)
    std::cout<<"Not found " <<toFind;

    return 0;
}