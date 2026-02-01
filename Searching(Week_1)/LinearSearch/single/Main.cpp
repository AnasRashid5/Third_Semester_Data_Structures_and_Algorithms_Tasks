// Online C++ compiler to run C++ program online
#include <iostream>

int main() {
    // Write C++ code here
    bool flag=false;
    int toFind;
    int num[10]={77,98,88,75,22,55,87,54,45,10};
    
    std::cout << "Enter Number to be searched ";
    std::cin>>toFind;
    
    for(int i=0;i<10;i++){
        if(toFind==num[i]){
            flag=true;
            std::cout<<"Found at index "<<(i+1);
        }
    }
    if(flag==false)
    std::cout<<"Not found " <<toFind;

    return 0;
}