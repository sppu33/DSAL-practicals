/*
Problem Statement:(same as hashing one only diff. is one extra display function)
Implement all the functions of a dictionary (ADT) using open hashing technique:
separate chaining using linked list Data: Set of (key, value) pairs, Keys are mapped to
values, Keys must be comparable, and Keys must be unique. Standard Operations: Insert
(key, value), Find(key), Delete(key), Display
*/

#include<iostream>
#define MAX 10
using namespace std;


class node{
    private:
    int key;
    string value;
    node *next;

    public:
        node(int key,string value){
            this->key=key;
            this->value=value;
            this->next=nullptr;
        }
    friend class Hashtable;
};

class Hashtable{
    private:
        node* table[MAX];
        int hash(int key){
            return((3*key)+5)%MAX;
        }


    public:
    Hashtable(){
        //initialise
        for(int i=0;i<MAX;i++){
            table[i]=nullptr;
        }
    }
    
    void insert(int key,string value){
        int index = hash(key);
        node *new_node= new node(key,value);
        if(table[index]==nullptr){
            table[index] = new_node;
        }
        else{
            //collision handling
            node *head = table[index];
            while(head->next!=NULL){
                head=head->next;
            }
            head->next=new_node;
        }
        cout<<"Insertion Successfull"<<endl;

    }

    string Find(int key){
        int index=hash(key);
        if(table[index]==nullptr){
            cout<<"DOESN'T EXISTS"<<endl;
            return "";
        }
        else{
            node* head=table[index];
            while(head->next!=NULL){
                head=head->next;
            }
            return head->value;

        }
    }

    void Delete(int key){
        int index=hash(key);
        node *head= table[index];
        node *prev = nullptr;
        while(head != nullptr){
            if(head->key == key){
                if(prev==nullptr){
                    table[index]=head->next;
                }
                else{
                    prev->next=head->next;
                }
                delete head;
                cout<<"Deletion Successfull"<<endl;;
            }
            prev=head;
            head=head->next;
        }
    }
    //**************************************************//
    //display function
    void Display(){
        for(int i=0;i<MAX;i++){
            node* head = table[i];
            cout<<i<<"]";
            while(head!=nullptr){
                cout<<"{"<<head->key<<":"<<head->value<<"}"<<" ";
                head=head->next;
            }
            cout<<endl;
        }
    }
};

int main(){
    Hashtable hashTable;
    hashTable.insert(1, "apple");
    hashTable.insert(20, "banana");
    hashTable.insert(20, "grapes");
    hashTable.insert(3, "cherry");
    hashTable.Display();

    string value = hashTable.Find(1);
    cout << "Value for key 1: " << value << endl;

    value = hashTable.Find(3);
    cout << "Value for key 3 before deletion: " << value << endl;
    hashTable.Delete(3);

    value = hashTable.Find(3);
    cout << "Value for key 3 after deletion: " << value << endl;

}
