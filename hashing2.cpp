/*
Problem Statement:
Consider telephone book database of N clients. Make use of a hash table implementation
to quickly look up client‘s telephone number. Make use of two collision handling
techniques and compare them using number of comparisons required to find a set of
telephone numbers (Note: Use linear probing with replacement and without replacement).
Perform following operations
1. Insert
2. Delete
3. Search
4. Display
*/

#include<iostream>
using namespace std;
#define Size 10

class Telephone{
    private:
    int size= Size;
    int Database1[10];
    int Database2[10];
    //hash function;
    int hash(int key){
        return ((key*3)+5)%Size;
    }
    public:
    Telephone(){
        //setting each component of table to -1
        for(int i=0;i<size;i++){
            Database1[i]=-1;
            Database2[i]=-1;
        }
    }

    void insert(int num){
        int index= hash(num);
        // for linear probing without replacement
        if(Database1[index]==-1){
            Database1[index]=num;
        }
        else{
            int temp1=index;
            while(Database1[temp1]!=-1){
                temp1++;
            }
            Database1[temp1]=num;
        }
        //linear probing without replacement
        if(Database2[index]==-1){
            Database2[index]=num;
        }
        else{
            //there will be current number as well
            int temp2=index;
            int curr_num=Database2[index];
            //if element with correct hash key is present at correct position
            if(hash(curr_num)==index){
                while(Database2[temp2]!=-1){
                    temp2++;
                }
                Database2[temp2]=num;
            }
            // if wrong element is present
            else{
                Database2[index]=num;
                while(Database2[index]!=-1){
                    index++;
                }
                Database2[index]=curr_num;
            }
        }
    }

    void display(){
        cout<<"     Database1       Database2"<<endl;
        for(int i=0;i<10;i++){
            cout<<i<<"      "<<Database1[i]<<"      "<<Database2[i]<<endl;
        }
    }
//***********************************************************//
//Search function
    pair<int,int>Search(int key){
        int cmp1=1;
        int cmp2=1;
        int index=hash(key);
        int ind1=-1,ind2=-1;
        //Searching in Database1
        bool flag1=true;
        //starting from the current hash value % 10 till the iterator comes to it again
        while(Database1[index%10]!=key){
            cmp1++;
            //if all elements are searched
            if(cmp1==10){
                ind1=-1;
                flag1=false;
                cout<<"Key Not Found"<<endl;
                break;
            }
            index++;
        }
        // if the element is found
        if(flag1){
            ind1=index%10;
            cout<<"Key found in Database1 at index: "<<(index%10)<<endl;
            cout<<"No. of comparisons: "<<cmp1<<endl;
        }

        //now searching in database with replacement 
        //Searching in Database2
        index=hash(key);
        bool flag2=true;
        //till element at database2 != key 
        while(Database2[index%10]!=key){
            cmp2++;
            // if total comp= 10 i.e. all elements are searched
            if(cmp2==10){
                ind2=-1;
                cout<<"Key Not Found"<<endl;
                flag2=false;
                break;
            }
            index++;
        }
        //if the key was found
        if(flag2){
            ind2=index%10;
            cout<<"key found in Database2 at index: "<<index%10<<endl;
            cout<<"No. of comparisons: "<<cmp2<<endl;
        }
        //make_pair inbuilt function
        return make_pair(ind1,ind2);
    }

    void Delete(int key){
        pair<int, int> index= Search(key);
        if(index.first!=-1){
            Database1[index.first]=-1;
        }
        if(index.second!=-1){
            Database2[index.second]= -1;
        }
    }
};
int main(){
    Telephone S;
    char ch='y';
    while(ch=='y'){
        cout<<"________MENU_________"<<endl;
        cout<<"     1.Insert"<<endl;
        cout<<"     2.Display"<<endl;
        cout<<"     3.Search"<<endl;
        cout<<"     4.Delete"<<endl;
        cout<<"     5.Exit"<<endl;
        cout<<"_____________________"<<endl;
        int choice;
        cout<<"Enter choice: ";
        cin>>choice;
        switch (choice)
        {
        case 1:
            int value;
            cout<<"---INSERT---"<<endl;
            cout<<"Enter the value: ";
            cin>>value;
            S.insert(value);
            break;
        case 2:
            cout<<"---DISPLAY---"<<endl;
            S.display();
            break;
        case 3:
            cout<<"---SEARCH---"<<endl;
            cout<<"Enter the value: ";
            cin>>value;
            S.Search(value);
            break;
        case 4:
            cout<<"---DELETE---"<<endl;
            cout<<"Enter the value: ";
            cin>>value;
            S.Delete(value);
            break;
        case 5:
            cout<<"Exiting......."<<endl;
            ch='n';
            break;
        default:
            cout<<"Invalid input"<<endl;
        }
        cout<<"Do u wanna continue(y/n)? ";
        cin>>ch;
    }
}
