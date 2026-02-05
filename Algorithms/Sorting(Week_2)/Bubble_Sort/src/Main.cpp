#include<iostream>
#include"models/Bubble_Sorter.cpp"
using namespace std;

int main(){
    Bubble_Sorter sorter;

    cout<<"Before Bubble Sorting:"<<endl;
    cout<<sorter.toString()<<endl;
    
    sorter.bubble_sort();
    
    cout<<"After Sorting:"<<endl;
    cout<<sorter.toString()<<endl;

    return 0;
}