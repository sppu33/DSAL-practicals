//ascending and descending order avl
#include<iostream>
#include<queue>
#include<stack>
#include<cmath>
#include<cstring>
using namespace std;

struct node{
    int key;
    string value;
    int height=1;
    node* left=nullptr;
    node* right=nullptr;
};
class avltree{
    node* root=nullptr;

    int getbalancefactor(node* n){
        if(n == nullptr){
            return 0;
        }
        return nodeHeight(n->left)-nodeHeight(n->right);
    }

    int nodeHeight(node* n){
        if(n==nullptr){
            return 0;
        }
        return n->height;
    }

    void updateHeight(node* n){
        n->height= 1+ max(nodeHeight(n->left),nodeHeight(n->right));
    }

    node* LLRotation(node* n){
        node* newRoot= n->left;
        newRoot->right=n;
        n->left=nullptr;
        updateHeight(n);
        updateHeight(newRoot);
        return newRoot;
    }

    node* RRrotation(node* n){
        node * newRoot= n->right;
        newRoot->left=n;
        n->right=nullptr;
        updateHeight(n);
        updateHeight(newRoot);
        return newRoot;
    }

    node* RLRotation(node * n){
        n->right=LLRotation(n->right);
        return RRrotation(n);
    }

    node* LRRotation(node* n){
        n->left=RRrotation(n->left);
        return LLRotation(n); 
    }

    node* balance(node* n){
        if(getbalancefactor(n)==2){
            if(getbalancefactor(n->left)<0){
                n= LRRotation(n);
            }
            else{
                n=LLRotation(n);
            }
        }
        else if(getbalancefactor(n)==-2){
            if(getbalancefactor(n->right)>0){
                n=RLRotation(n);
            }
            else{
                n=RRrotation(n);
            }
        }
        updateHeight(n);
        return(n);
    }

    //recursive inorder / ascending
    void inorder(node* root){
        if(root==nullptr){
            return;
        }
        inorder(root->left);
        cout<<root->key<<" ";
        inorder(root->right);
    }

    //finding min value node
    node* minValuenode(node* n){
        node* curr=n;
        while(curr->left!=nullptr){
            curr=curr->left;
        }
        return curr;
    }

    //for inserting new values
    node* insertSubtree(node* curr, int key, string value){
        if(curr==nullptr){
            node* newNode= new node();
            newNode->key=key;
            newNode->value=value;
            return newNode;
        }
        if(curr->key > key){
            curr->left= insertSubtree(curr->left,key,value);
        }
        else if(curr->key < key){
            curr->right= insertSubtree(curr->right,key,value);
        }
        //updating th current nodes value
        else{
            curr->value= value;
            return curr;
        }
        return balance(curr);
    }

    void recDescending(node* root){
        if(root==nullptr){
            return ;
        }
        recDescending(root->right);
        cout<<root->key<<" ";
        recDescending(root->left);
    }
//not asked still if time then do it
    node* deleteSubtree(node* root, int key){
        if(key > root->key){
            root->right= deleteSubtree(root->right,key);
        }
        else if(key < root->key){
            root->left = deleteSubtree(root->left,key);
        }
        else{
            if(root->right==nullptr || root->left==nullptr){
                node* temp=root->left ? root->left : root->right;
                if(temp==nullptr){
                    temp=root;
                    root=nullptr;
                }
                else{
                    root->key=temp->key;
                    root->value=temp->value;
                    root->left= root->right = nullptr;
                }
                delete temp;
            }
            //if both the left and right node are not null
            else{
                node* temp=minValuenode(root->right);//inorder predecessor
                root->key=temp->key;
                root->value=temp->value;
                root->right=deleteSubtree(root->right,temp->key);
            }
        }
        if(root==nullptr){
            return root;
        }//else
        return balance(root);
    }
 
public:
    void insert( int key, string value ) {
        root = insertSubtree( root, key, value);
    }
    void del(int key) {
        root = deleteSubtree(root, key);
    }
    void iinorder() {
        cout<< "\nInorder:(ascending order: )"<<endl;
        inorder( root );
        cout<<endl;
    }
    //non-recursive search
    // Node* search( int key ) {
    int search(int key){
    int count=0;
        node *curr = root;
        while( curr != nullptr ) {
        count++;
            if( key > curr->key )
                curr = curr->right;
            else if( key < curr->key )
                curr = curr->left;
            else
                // display_comp(count);
                // return curr;
                return count;
        }
        return -1;
    }
    void display_comp(int count){
        cout<<" The number of comparisons are "<<count<<endl;
    }
//bfs non - recursive
    void BFS() {
        cout<< "\nBFS: " <<endl;
        queue<node*> Queue;
        Queue.push( root ) ;
        while( !Queue.empty() ) {
            node* poppedNode = Queue.front() ;
            cout << poppedNode -> key << " " ;
            Queue.pop() ;
            if( poppedNode -> left != nullptr )
                Queue.push( poppedNode -> left ) ;
            if( poppedNode -> right != nullptr )
                Queue.push( poppedNode -> right ) ;
        }
        cout<<endl;
    }
    //************************************************//
//non-recursive ascending order/ inorder
    void nonRecursiveAscendingOrder() {
        cout << "\nNon-Recursive Ascending Order: " << endl;
        stack<node*> Stack;
        node* current = root;
        while (current != nullptr || !Stack.empty()) {
            while (current != nullptr) {
                Stack.push(current);
                current = current->left;
            }
            current = Stack.top();
            Stack.pop();
            cout << current->key << " ";
            current = current->right;
        }
        cout << endl;
    }

    void Descendingorder(){
        cout<<"Descendingorder: ";
        recDescending(root);
        cout<<endl;
    }
} ;

int main(){
    avltree Tree;
    int choice;
    do{
        cout<<" 1. insert\n 2. delete\n 3. no. of comparisons\n 4. ascending\n 5. desceding\n 6. bfs\n 7. quit\n ";
        cin>>choice;
        switch(choice){
            case 1:{
                int key;
                string value;
                cout<<" Enter the key and value :";
                cin>>key>>value;
                Tree.insert(key,value);
                break;
            }
            case 2:{
                int key;
                cout<<" Enter the key to delete :";
                cin>>key;
                Tree.del(key);
                break;
            }
            case 3:{
                int key;
                cout<<" Enter the key to be found :";
                cin>>key;
                Tree.display_comp(Tree.search(key));
                break;
            }
            case 4:{
                Tree.nonRecursiveAscendingOrder();
                Tree.iinorder();
                break;
            }
            case 5:{
                Tree.Descendingorder();
                break;
            }
            case 6:{
                Tree.BFS();
                break;
            }
            case 7:{
                cout<<"Thank u"<<endl;
                break;
            }
            default:{
                cout<<"invalid";
                break;
            }
        }
    }while(choice!=7);
    return 0;
}
