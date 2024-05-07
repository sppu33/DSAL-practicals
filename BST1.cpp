/*
____________________________________Binary Search Tree____________________________________
Problem Statement:

Construct binary search tree. Provide facility for adding new entries, deleting any element.
Provide facility to display whole data sorted in ascending order using nonrecursive traversal. 
Search an element present in a tree and display number of comparisons required to search.

*/
#include<iostream>
#include<stack>
using namespace std;

class Node{
    int data;
    Node*left,*right;
    public:
    Node(){
        data=0;
        left=nullptr;
        right=nullptr;
    }
    Node(int d){
        data=d;
        left=nullptr;
        right=nullptr;
    }
    friend class BST;
};

class BST
{
private:
    /* data */
    Node* root;
    int cmp=0;
    Node * Insert(int data,Node* root){
        if(root==nullptr){
            root= new Node(data);
        }
        else if(data< root->data){
            root->left= Insert(data,root->left);
        }
        else if(data> root->data){
            root->right= Insert(data,root->right);
        }
        return root;
    }
// iterative inorder
    void iinorder(Node * root){
        stack<Node*> st;
        Node* curr= root;
        while(!st.empty() || curr!=nullptr){
            while(curr!=nullptr){
            st.push(curr);
            curr=curr->left;
            }
            curr=st.top();
            st.pop();
            cout<<curr->data<<" ";
            curr= curr->right;
        }
    }

    bool find(Node * root, int value){
        if(root == NULL || root->data == value){
            cmp++;
            return (root!=NULL);
        }
        if(value < root->data){
            cmp++;
            return find(root->left, value);
        }
        else{
            cmp++;
            return find(root->right,value);
        }
    }

//min value of
    Node* minValue(Node* node){
        Node* curr= node;
        while(curr->left !=nullptr){
            curr= curr->left;
        }
        return curr;
    } 
// deletion code
    Node* deleteSubtree(Node* root, int key){
        if(key < root->data){
            root->left= deleteSubtree(root->left,key);
        }
        else if(key > root->data){
            root->right= deleteSubtree(root->right,key);
        }
        else{
            if(root->right == nullptr || root->left == nullptr){
                Node * temp = root->left ? root->left : root->right; // checks if left child of node exists
                if(temp== nullptr){
                    temp=root;
                    root=nullptr;
                }
                else{
                    root->data= temp->data;
                    root->left= root->right = nullptr;
                }
                delete temp;
            }
            else{
                Node * temp = minValue(root->right);
                root->data = temp->data;
                root->right= deleteSubtree(root->right,temp->data);
            }
        }
        return root;
    }
public:
    BST(){
        root= nullptr;
    }
    void create(){
        int cnt, val;
        cout<<"Enter no. of elements :";
        cin>>cnt;
        for(int i=0;i<cnt;i++){
            cout<<"Enter the element :";
            cin>>val;
            root=Insert(val, root);
        }
        cout<<" BST created successfully !"<<endl;
    }
    void add(){
        int val;
        cout<<"Enter the val to be inserted: ";
        cin>>val;
        Insert(val,root);
    }
    void display(){
        cout<<root->data<<endl;
        iinorder(root);
    }
        
    void search(){
        cmp=0;
        int val;
        cout<<"Enter the element to be searched: ";
        cin>>val;
        bool ans=find(root,val);
        if(ans){
            cout<<"PARTY.."<<endl;
            cout<<"NO. of comparisons:"<<cmp<<endl;
        }
        else{
            cout<<"Element not found";
        }
    }

    void recursivedelete(){
        int k;
        cout<<" Enter the element to be deleted :";
        cin>>k;
        if(find(root,k)){
            root=deleteSubtree(root,k);
        }
        else{
            cout<<"Element not found !"<<endl;
        }
    }
};
int main(){
    BST B;
    B.create();
    B.display();
    B.search();
    B.search();
    B.recursivedelete();
    B.display();
}

