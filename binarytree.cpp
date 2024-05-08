// Beginning with an empty binary tree, construct binary tree by inserting the values in the 
// order given. After constructing a binary tree perform following operations on it-  
// • Perform preorder recursive traversal  
// • Postorder, Inorder non-recursive traversal 
// • Count number of leaves, number of internal nodes.  
 
// OR 
 
// Construct an expression tree from the given prefix expression (e.g. +--a*bc/def) and 
// perform following operations on it 
// 1) traverse it using non recursive post order traversal 
// 2) Count and Display operands in given expression 
// 3) Count and display operators in given expression
#include<iostream>
#include<stack>
#include<unordered_map>
#include<queue>
using namespace std;

class Node{
    int data;
    Node* left,*right;
    friend class Tree;
    friend class Function;
    public:
    Node(){
        data=0;
        left=right=nullptr;
    }
    //edit
    Node(int d){
        data=d;
        left=right=nullptr;
    }  
};

class Tree{
    private:
    Node * root;
    Node * makeTree(){
        Node * temp;
        temp= new Node;
        cout<<"Enter the data :"<<endl;
        cin>>temp->data;
        char ch;
        cout<<"Do you want left child "<<temp->data<< "(y/n) :";
        cin>>ch;
        if(ch=='y'){
            temp->left=makeTree();
        }
        cout<<"Do you want right child "<<temp->data<< "(y/n) :";
        cin>>ch;
        if(ch=='y'){
            temp->left=makeTree();
        }
        return temp;
    }
    public:
    //tree constructor with root null
    Tree(){
        root=NULL;
    }
    //to use makeTree() function in public 
    void create(){
        root=makeTree();
    }
    friend class Function;
};

class Function{
    private:
    int count=0;
    Tree T;
    //recursive codes
    void preorder(Node *root){
        if(root==NULL){
            return ;
        }
        cout<<root->data<<endl;
        preorder(root->left);
        preorder(root->right);
    }
    void inorder(Node *root){
        if(root==NULL){
            return ;
        }
        inorder(root->left);
        cout<<root->data<<endl;
        inorder(root->right);
    }  
    void postorder(Node *root){
        if(root==NULL){
            return ;
        }
        postorder(root->left);
        postorder(root->right);
        cout<<root->data<<endl;
    }
    //recursive copy function
    Node * Copy(Node * p){
        if(p== NULL){
            return p;
        }
        Node * root=new Node(); //why Node() and not just Node
        root ->data =p->data;
        root ->left= Copy(p->left);
        root ->right= Copy(p->right);
        return root;
    }

    int Height(Node * p){
        int x=0,y=0;
        if(p==NULL){
            return 0;
        }
        x=Height(p->left);
        y=Height(p->right);
        if(x>y){
            return x+1;
        }
        return y+1;
    }

    void No_leaves(Node *p){
        if(p==NULL){
            return ;
        }
        No_leaves(p->left);
        No_leaves(p->right);
        if(p->left==NULL && p->right==NULL){
            count++;
        }
    }

    void MirrorImage( Node * root){
        if(root==NULL){
            return ;
        }
        MirrorImage(root->left);
        MirrorImage(root->right);
        Node * temp;
        temp=root->left;
        root->left=root->right;
        root->right=temp;
    }

    void Deletetree(Node * root){
        if(root==NULL){
            return ;
        }
        Deletetree(root->left);
        Deletetree(root->right);
        delete root;
    }
    //Non- recursive 
    Node * icopy(Node * root){
        if(root==nullptr){
            return nullptr;
        }
        stack<Node*> nodeStack;
        unordered_map<Node*,Node*>copymap;
        Node* p= new Node(root->data);
        copymap[root]= p;
        nodeStack.push(root);
        while(!nodeStack.empty()){
            Node* curr= nodeStack.top();
            nodeStack.pop();
            Node* currentcopy= copymap[curr];

            if(curr->right){
                Node* rightCopy=new Node(curr->right->data);
                currentcopy->right= rightCopy;
                copymap[curr->right]=rightCopy;
                nodeStack.push(curr->right);
            }
            if(curr->left){
                Node* leftCopy=new Node(curr->left->data);
                currentcopy->left= leftCopy;
                copymap[curr->left]=leftCopy;
                nodeStack.push(curr->left);
            }
        }
        return p;
    } 
    //non-recusive height
    int iHeight(Node * root){
        if(root==nullptr){
            return 0;
        }
        queue<Node*>nodeQueue;
        nodeQueue.push(root);
        int height=0;
        while(!nodeQueue.empty()){
            int size=nodeQueue.size();
            while(size>0){
                Node* curr=nodeQueue.front();
                nodeQueue.pop();
                if(curr->left){
                    nodeQueue.push(curr->left);
                }
                if(curr->right){
                    nodeQueue.push(curr->right);
                }
                size--;
            }
            height++;
        }
        return height;
    }

    //non-recursive leaf count code
    int ileafCount(Node* root){
        if(root==nullptr){
            return 0;
        }
        stack<Node*>nodeStack;
        nodeStack.push(root);
        int leafCount=0;
        //while node stack is not empty
        while(!nodeStack.empty()){
            Node * current =nodeStack.top();
            nodeStack.pop();
            if(current->left==nullptr && current->right==nullptr){
                leafCount++;
            }
            if(current->right){
                nodeStack.push(current->right);
            }
            if(current->left){
                nodeStack.push(current->left);
            }
        }
        return leafCount;
    }

    void iDelete(Node* root){
        if(root==nullptr){
            return;
        }
        stack<Node*>nodeStack;
        nodeStack.push(root);
        while(!nodeStack.empty()){
            Node * curr=nodeStack.top();
            nodeStack.pop();
            if(curr->right){
                nodeStack.push(curr->right);
            }
            if(curr->left){
                nodeStack.push(curr->left);
            }
            cout<<"/n Deleting node :"<<curr->data;
            delete curr;
        }
    }

    public:
    //
    Node * root= nullptr;
    //
    Function(){
        T.create(); // from the root make in Tree class
    }
    //inorder without recursion
    void iinorder(){
        Node * curr= root;
        stack<Node*> Stack;
        while(!Stack.empty() || curr!=nullptr){
            while(curr!=nullptr){
                Stack.push(curr);
                curr=curr->left;
            }
            curr= Stack.top();
            Stack.pop();
            cout<<curr->data<<" ";
            curr=curr->right;
        }
    }
    //preorder without recursion
    void ipreorder(){
        if(root==nullptr){
            return ;
        }
        stack<Node*> Stack;
        Stack.push(root);
        while(!Stack.empty()){
            Node* poppedNode= Stack.top();
            Stack.pop();
            cout<<poppedNode->data;
            if(poppedNode->right){
                Stack.push(poppedNode->right);
            }
            if(poppedNode->left){
                Stack.push(poppedNode->left);
            }
        }
    }
    //post order without recursion (iterative )
    void ipostorder(){
        stack<Node*> st;
        Node* curr = root;
        Node* prev = NULL;
        while (curr!= nullptr ||!st.empty()) {
            while (curr!= nullptr) {
                st.push(curr);
                curr = curr->left;
            }
            curr = st.top();
            if (curr->right == nullptr || curr->right == prev) {
                cout << curr->data << " ";
                prev = curr;
                st.pop();
                curr = nullptr;
            } else {
                curr = curr->right;
            }
        // void postorderIterative(node *root){
            // }
        }
    }

    //functions
    void get_Inorder(){
        cout<<"inorder (recursive) :";
        inorder(T.root);
        cout<<"inorder (iterative) :";
        iinorder();
        cout<<endl;
    }
    void get_Preorder(){
        cout<<"preorder (recursive):";
        preorder(T.root);
        cout<<"preorder (iterative) :";
        ipreorder();
        cout<<endl;
    }
    void get_Postorder(){
        cout<<"postorder (recursive) :";
        postorder(T.root);
        cout<<"postorder (iterative) :";
        ipostorder();
        cout<<endl;
    }
    //swapping the tree
    void swap_tree(){
		cout<<"Original Tree: "<<endl;;
		get_Inorder();
		MirrorImage(T.root);
		cout<<"New Tree: "<<endl;
     	get_Inorder();
	}
	void get_height() {
        cout << "Height of the Tree: (recursive) :" << Height(T.root) << endl;
        cout<<"Height of tree ( by iteration ):"<< iHeight(T.root)<<endl;
    }
    //making a copy function
    void  get_copy(){
		Node * temp;
		temp=Copy(T.root);
		cout<<"Original Tree: ";
		inorder(T.root);
		cout<<endl;
		cout<<"New Tree: ";
     	inorder(temp);
		cout<<endl;
    }
    
    void get_Number_of_leafs() {
        No_leaves(T.root);
        cout << "Number of leafs: (recursive) :" << count << endl;
        cout << "Number of leafs: (iterative) :" << ileafCount(T.root) << endl;
    }
    
    void Eraseall(){
        iDelete(T.root);
        T.root=NULL;
        cout<<"Tree is deleted successfully"<<endl;
    }
};

int main(){
    cout<<"Enter the data to Create a tree"<<endl;
    Function F;
    cout<<"-----------MENU------------"<<endl;
    cout<<"1.Inorder Traversal"<<endl;
    cout<<"2.Preorder Traversal"<<endl;
    cout<<"3.Postnorder Traversal"<<endl;
    cout<<"4.Height"<<endl;
    cout<<"5.No of leafs"<<endl;
    cout<<"6.Copy "<<endl;
    cout<<"7.Swap Tree"<<endl;
    cout<<"8.Erase Tree"<<endl;
    cout<<"---------------------------"<<endl;
    
    char ch;
    ch='y';
    while(ch=='y'){
    	cout<<"Enter your Choice: ";
    	int choice;
    	cin>>choice;
    	if(choice==1){
    	    F.get_Inorder();
    	}
    	else if(choice==2){
    	     F.get_Preorder();
    	}
    	else if(choice==3){
    	    F.get_Postorder();
    	}
    	else if(choice==4){
    	    F.get_height();  
    	}
    	else if(choice==5){
    	    F.get_Number_of_leafs();
    	}
    	else if(choice==6){
    	    F.get_copy();
    	}
    	else if(choice==7){
    	    F.swap_tree();
    	}
    	else if(choice==8){
    	    F.Eraseall();
    	}
    	else{
    		cout<<"Invalid Input"<<endl;
    	}
        cout<<"---------------------------"<<endl;
    	cout<<"Do u want to continue (y/n) ?";
    	cin>>ch;
       }
    return 0;
}
