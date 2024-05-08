// Problem Statement:
// Implement all the functions of a dictionary (ADT) using open hashing technique: separate
// chaining using linked list Data: Set of (key, value) pairs, Keys are mapped to values, Keys
// must be comparable, and Keys must be unique. 
// Standard Operations: Insert (key, value),Find(key), Delete(key).
// Use hash function as H(x) = (3x+5) %10
#include<iostream>
using namespace std;
#define MAX 10

class node{
    private:
    int key;
    string value;
    node *next;     //singly LL

    public:
        node(int k,string v){
            key=k;
            value=v;
            next=nullptr;
        }
    friend class Hashtable;
};

class Hashtable{
    private:
    node* table[MAX];
    //*****************************************************//
    //hash function
    int hash(int key){
        return ((3*key)+5)%MAX;
    }
    public:
    Hashtable(){
        for(int i=0;i<MAX;i++){
            table[i]=nullptr;
        }
    }

    //insert function
    void insert(int key,string value){
        int index=hash(key);
        node* new_node= new node(key,value);
        if(table[index]==nullptr){
            table[index]=new_node;
        }
        //handling the collsion
        else{
            node *head= table[index];
            while(head->next!=nullptr){
                head=head->next;
            }
            head->next=new_node;
        }
        cout<<"Insertion successful !"<<endl;
    }

    string Find(int key){
        int index=hash(key);
        if(table[index]==nullptr){
            cout<<"No value exist"<<endl;
            return "";
        }
        else{
            node* head= table[index];
            // while(head->next!=nullptr){
            while(head->key != key){
                head=head->next;
            }
            return head->value;
        }
    }

    void Delete(int key){
        int index=hash(key);
        node* head=table[index];
        node* prev= nullptr;
        while(head!=nullptr){
            if(head->key == key){
                if(prev==nullptr){
                    table[index]=head->next;
                }
                else{
                    prev->next=head->next;
                }
                delete head;
                cout<<"Deletion successful!"<<endl;
            }
            prev=head;
            head=head->next;
        }
    }
//this display function is not perfect and does not satisfy test cases
    void display(){
        cout<<"Table :"<<endl;
        for(int i = 0; i < MAX; ++i){
            node* head = table[i];
            while(head != nullptr){
                cout<<head->key<<":"<<head->value<<endl;
                head = head->next;
            }
        }
    }
};
int main(){
    Hashtable hashTable;
    hashTable.insert(1, "apple");
    hashTable.insert(20, "banana");
    hashTable.insert(3, "cherry");

    string value = hashTable.Find(1);
    cout << "Value for key 1: " << value << endl;

    value = hashTable.Find(3);
    cout << "Value for key 3 before deletion: " << value << endl;
    hashTable.Delete(3);

    value = hashTable.Find(3);
    cout << "Value for key 3 after deletion: " << value << endl;

    hashTable.display();
}
