// Problem Statement:
// Implement the Heap sort algorithm for demonstrating heap data structure with modularity
// of programming language (consider integer data)

#include<iostream>
using namespace std;
//N  is size of heap
// a subtree rooted with node i
//*********************************************************//
void heapify(int arr[], int N, int i){
    //let largest as i
    int largest= i;
    //left=2i+1 and right=2i+2
    int l=2*i+1;
    int r=2*i+2;
    //if left child is larger than root, then largest = left
    if(l<N && arr[l]>arr[largest]){
        largest=l;
    }
    //similarly
    if(r<N && arr[r]>arr[largest]){
        largest=r;
    }
    //if largest is not root then 
    if(largest !=i){
        swap(arr[i],arr[largest]);
        //recursively heapify the affected subtree
        heapify(arr, N, largest);
    }
}
//main functions to do a heap sort
//*************************************************************//
void heapsort(int arr[], int N){
    //build the heap i.e. rearrange array
    for(int i=N/2-1;i>=0;i--){
        heapify(arr, N, i);
    }
    // extract an element one by one from the heap
    for(int i=N-1;i>0;i--){
        //move the current root to end
        swap(arr[0],arr[i]);
        //call max heapify on the reduced heap
        heapify(arr,i,0);
    }
}
//utility function to print array of size N
void printarr(int arr[], int N){
    for(int i=0;i<N;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}
int main(){
    int arr[]={21,10,13,5,8,7};
    int N= sizeof(arr)/sizeof(arr[0]);
    heapsort(arr,N);
    cout<<"Sorted array is \n";
    printarr(arr,N);
}
