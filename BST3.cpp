// Problem Statement:

// A dictionary stores keywords and its meanings. Provide facility for adding new
// keywords, updating values of any entry, delete any entry. Provide facility to display
// whole data sorted in ascending/ Descending order. Also find how many maximum
// comparisons may require for finding any keyword. Use Binary Search Tree for
// implementation.
//                                   OR
// Beginning with an empty binary search tree. Construct the binary search tree by inserting
// the values in given order. After constructing binary search tree perform following
// operations 1) Find numbers of node in longest path 2) Minimum and maximum data value
// found in tree 3) Change a tree so that the roles of the left and right pointers are swapped at
// every node. 4) Display in level order.

#include<iostream>
#include<stack>
using namespace std;

class Node{
    public:
    string key;
    string meaning;
    Node* left;
    Node* right;

    Node(const string& k, const string& m){
    string key=k;
    string meaning=m;
    Node* left=nullptr;
    Node* right=nullptr;
    }
};

class Dict{
    private:
    Node* root;
    Node* insert(Node* root,const string& k, const string& m){
        if(root== nullptr){
            return new Node(k,m);
        }
        if (k< root->key) {
            root->left = insert(root->left, k, m);
        } else if (k > root->key) {
        root->right = insert(root->right, k, m);
        } else {
        // Update meaning for existing key i.e update function
        root->meaning = m;
        }
        return root;
    }

    Node* findmin(Node* root){
        while(root->left!=nullptr){
            root=root->left;
        }
        return root;
    }

    Node* findmax(Node* root){
        while(root->right!=nullptr){
            root=root->right;
        }
        return root;
    }
//************************************************************//
    Node* remove(Node* root,const string& key){
        if(root==nullptr){
            return root;
        }
        if(key<root->key){
            root->left=remove(root->left, key);
        }
        else if(key>root->key){
            root->right=remove(root->right,key);
        }
        //if the node with equal key is found
        else{
            if(root->left==nullptr){
                Node* temp= root->right;
                delete root;
                return temp;
            }
            else if(root->right==nullptr){
                Node* temp= root->left;
                delete root;
                return temp;
            }
            // in case of roots with both children we need to get min. right subtree
            Node* temp= findmin(root->right);
            root->key=temp->key;
            root->meaning=temp->meaning;
            root->right= remove(root->right,temp->key);
        }
        return root;
    }
    void inOrder(Node* root) const {
        if (root != nullptr) {
            inOrder(root->left);
            cout << root->key << ": " << root->meaning << endl;
            inOrder(root->right);
        }
    }

  void reverseInOrder(Node* root) const {
        if (root != nullptr) {
            reverseInOrder(root->right);
            cout << root->key << ": " << root->meaning << endl;
            reverseInOrder(root->left);
        }
    }
//*************************************************************//
//use of constant and string&
    int maxcomp(Node* root) const{
        if(root==nullptr){
            return 0;
        }
        int leftcomp=maxcomp(root->left);
        int rightcomp= maxcomp(root->right);
        return max(leftcomp+1,rightcomp+1);
    }

    public:
    Dict(){
        Node* root= nullptr;
    }

    void add(const string& key, const string& meaning) {
        root = insert(root, key, meaning);
    }

    void update(const string& key, const string& meaning) {
        root = insert(root, key, meaning);
    }

    void remove(const string& key) {
        root = remove(root, key);
    }

    void displayAscending() const {
        inOrder(root);
    }

    void displayDescending() const {
        reverseInOrder(root);
    }

    int getMaxComparisons() const {
        return maxcomp(root);
    }
};
int main(){
    Dict D;
    int choice;
    cout<<"\n 1. add "<<"\n 2. update"<<"\n 3. remove"<<" \n 4.ascending"<<"\n 5.descending"<<"\n 6. max comparisons"<<" 7. exit"<<endl;
    cin>>choice;
    string k,m;
    switch(choice)
    {
    case 1:
    cout<<" Enter key and meaning";
        cin>>k;
        cin>>m;
        D.add(k,m);
        break;
    case 2:
    cout<<" Enter key and meaning";
        cin>>k;
        cin>>m;
        D.update(k,m);
        break;
    case 3:
        cout<<" Enter key";
        cin>>k;
        D.remove(k);
        break;
    case 4:
        D.displayAscending();
        break;
    case 5:
        D.displayDescending();
        break;
    case 6:
        D.getMaxComparisons();
        break;
    default:
        return 0;
    }
}
