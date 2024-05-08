// Problem Statement:
// Read the marks obtained by students of second year in an online examination of particular
// subject. Find out minimum marks obtained in that subject. Use heap data structure.
// Analyze the algorithm

#include<iostream>
using namespace std;

// note this function is similar to function in heapsort2.cpp only difference of smallest
void heapify(int arr[], int N , int i){
    int smallest=i;
    int left= 2*i+1;
    int right= 2*i+2;
    if(left<N && arr[smallest]>arr[left]){
        smallest=left;
    }
    if(right<N && arr[smallest]>arr[right]){
        smallest=right;
    }
    if(smallest != i){
        swap(arr[i],arr[smallest]);
        heapify(arr,N , smallest);
    }
}
int main(){
    int n;
    cout<<"Enter the total number of students: ";
    cin>>n;
    cout<<"Enter the marks of "<<n <<" students "<<endl;
    int marks[n];
    for(int i=0;i<n;i++){
        cin>>marks[i];
    }
    //creating a min heap similar to done in heapsort1.cpp
    for(int i=n/2-1;i>=0;i--){
        heapify(marks,n,i);
    }
    cout<<"Minimum marks obtained : "<<marks[0];
}
