// Problem Statement:
// Construct binary search tree. Provide facility for adding new entries. Provide facility to
// display whole data sorted in descending order using non-recursive traversal.
// Find Minimum and maximum data value in tree. Also find how many maximum
// comparisons may require for finding any keyword

#include<iostream>
#include<stack>
using namespace std;

class node{
    private:
        int data;
        node *left,*right;
    public:
    node(){
        data=0;
        left=nullptr;
        right= nullptr;
    }
    node(int d){
        data=d;
        left=nullptr;
        right= nullptr;
    }
    friend class BST;
};

class BST{
    private:
        node *root;
        int cmp=0;
        node* insert(int data,node* p){
            if(p==nullptr){
                p=new node(data);
            }
            else if(p->data > data){
                p->left=insert(data,p->left);
            }
            else if(p->data < data){
                p->right=insert(data,p->right);
            }
            return p;
        }
        //******************************************************************//
        void rev_inorder(node* root){
            stack<node*> s;
            node* curr = root;
            while(!s.empty() || curr!=nullptr){
                while(curr!=nullptr){
                    s.push(curr);
                    curr=curr->right;
                }
                curr=s.top();
                s.pop();
                cout<<curr->data<<" ";
                curr=curr->left;
            }
        }
        void min(node *root){
            node* curr=root;
            while(curr->left!=nullptr){
                curr=curr->left;
            }
            cout<<"Minimum: "<<curr->data<<endl;

        }
        void max(node* root){
            node* curr=root;
            while(curr->right!=nullptr){
                curr=curr->right;
            }
            cout<<"Maximum: "<<curr->data<<endl;
        }
        //******************************************************************//
        bool find(int key,node* root){
            if(root==nullptr || root->data==key){
                cmp++;
                return (root!=nullptr);
            }
            if(root->data > key){
                cmp++;
                return find(key,root->left);
            }
            else if(root->data < key){
                cmp++;
                return find(key,root->right);
            }
        }
        public:
        BST(){
            root=nullptr;
        }
        void create(){
            int cnt,val;
            cout<<"Enter the no of Elements: ";
            cin>>cnt;
            for(int i=0;i<cnt;i++){
                cout<<"Enter the data: ";
                cin>>val;
                root=insert(val,root);
            }
            cout<<"Tree created successfully..."<<endl;
        }
        void add(){
            int val;
            cout<<"Enter the value to be inserted: ";
            cin>>val;
            insert(val,root);
        }
        void display(){
            cout<<"reverse order: ";
            rev_inorder(root);
            cout<<endl;
        }
        void get_min_max(){
            min(root);
            max(root);
        }
        void search(){
            int ans,key;
            cout<<"Enter the key: ";
            cin>>key;
            ans=find(key,root);
            if(ans){
                cout<<"Key found ;)"<<endl;
                cout<<"No. of comparisons: "<<cmp<<endl;
            }
            else{
                cout<<"Key not found :"<<endl;;
            }
            cmp=0;
        }
};

int main(){
    BST B;
    B.create();
    B.add();
    B.display();
    B.search();
    B.get_min_max();
    B.display();

}
