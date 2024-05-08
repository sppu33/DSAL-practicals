//TBST- inorder, postorder, lbit, rbit, deletion, min and max value

#include<iostream>
using namespace std;

class Node{
    int data;
    Node* left,* right;
    bool lbit,rbit;
    public:
    Node(){
        data=0;
        left=right=nullptr;
        lbit=0;
        rbit=0;
    }
    Node(int d){
        data=d;
        left=right=nullptr;
        lbit=0;
        rbit=0;
    }
    friend class TBST;
};

class TBST{
    Node* head, *root;
    public:
    TBST(){
        head=root=nullptr;
    }
    Node* getRoot(){
        return root;
    }
    //to insert node
    void insert(int key){
        //tree is empty
        if(root==nullptr){
            head=new Node(-999); //creating a dummy node called head node
            head->right= head;
            root= new Node(key);
            head->left=root;
            //set lbit of head to 1
            head->lbit=1;
            root->left=head;
            root->right=head;
            return ;
        }
        //if tree is not empty
        else{
            //make a node named parent pointing to root 
            Node* parent=root;
            Node * temp= new Node(key);
            while(true){
                if(key==parent->data){
                    delete temp;
                    return; //duplicate key
                }
                else if( key< parent->data){
                    //explore left subtree
                    if(parent->lbit ==1){
                        //lbit=1 means child exist
                        parent= parent->left;
                    }
                    //add temp to end
                    else{
                        temp->left= parent->left;
                        temp->right= parent;
                        parent->left= temp;
                        parent->lbit=1;
                        return;
                    }
                }
                else{
                    //when key >parent->data
                    if(parent->rbit==1){
                        //right child exist
                        parent= parent->right;
                    }
                    else{
                        temp->right=parent->right;
                        temp->left=parent;
                        parent->right= temp;
                        parent->rbit=1;
                        return;
                    }
                }
            }
        }
    }
    // Inorder Traversal
    void inorder(){
        Node * temp= root;
        while(temp->lbit==1){
            temp=temp->left;
        }
        while(temp!=head){
            cout <<"["<<temp->lbit<<"  "<< temp->data << "  "<<temp->rbit<<"]";            // It has right child
            if(temp->rbit==1){
                temp=temp->right;
                //again the left most node
                while(temp->lbit==1){
                    temp=temp->left;
                }
            }
            else{
                temp=temp->right;
            }
        }
        cout<<endl;
    }

    void preorder(){
        bool flag=0;
        Node* temp=root;
        while(temp!=head){
            if(flag==0){
                cout <<"["<<temp->lbit<<"  "<< temp->data << "  "<<temp->rbit<<"]";
            }
            if(flag==0 && temp->lbit==1){
                temp=temp->left;
            }
            else{
                flag=(temp->rbit==1)?(0):(1);
                temp=temp->right;
            }
        }
        cout<<endl;
    }
    //search 
    //why *& find out
    // what is use of parent here
    bool search(int key, Node *& current, Node *&parent){
        while(current!=head){
            if(current->data== key){
                return true;
            }
            else{
                parent= current;
                if(key< current->data){
                    current= current->left;
                }
                else{
                    current=current->right;
                }
            }
        }
        return false;
    }
    //delete function 
    //*************************************************************//
    //?????????????????????????????
    //what is p and t
    void deleteNode(Node *&p,Node *&t){
        if(t->lbit==1 && t->rbit==1){
            Node * cs = t->right;
            p=t;
            //inorder successor?
            while(cs->lbit==1){
                p=cs;
                cs=cs->left;
            }
            t->data=cs->data;
            t= cs;
            cout<<"Deleting node having two links "<<endl;
        } 
        //deleting leaf nodes
        if(t->lbit==0 && t->rbit==0){
            if(p->left=t){
                cout<<"Deleting the left leaf"<<endl;
                p->left=t->left;
                p->lbit=0;
            }
            else{
                cout<<"Deleting the right leaf"<<endl;
                p->right=t->right;
                p->rbit=0;
            }
            delete t;
        }
        //left linked and right threaded
        if(t->lbit==1 && t->rbit==0){
            Node* temp= t->left;
            if(p->left==t){
                p->left=temp;
            }
            else{
                p->right=temp;
            }
            //finding inorder succesor?
            while(temp->rbit==1){
                temp=temp->right;
            }
            temp->right=t->right;
            cout<<"Deleting Node with left link "<<endl;
            delete t;
        }
        // right link, left thread
        if (t->lbit == 0 && t->rbit == 1)
        {
            Node *temp = t->right;
            if (p->left == t){
                p->left = temp;
            }
            else{
                p->right = temp;
            }
            //finding inorder succesor?
            while (temp->lbit == 1){
                temp = temp->left;
            }
            temp->left = t->left;
            cout << "Deleting Node with right link" << endl;
            delete t;
        }
    }

    void min_max(){
        Node* temp=root;
        while(temp->lbit==1){
            temp=temp->left;
        }
        cout<<"Minimum value is :"<<temp->data<<endl;
        temp=root;
        while(temp->rbit==1){
            temp=temp->right;
        }
        cout<<"Maximum value is :"<<temp->data<<endl;
    }
};
int main(){
    TBST tbst;
    int choice = -1;
    int temp;
    char c = 'y';
    while (c=='y')
    {
        cout << "-----------------MENU--------------------" << endl;
        cout << "1. Inserting a Node in a TBST" << endl;
        cout << "2. In-Order Traversal of TBST" << endl;
        cout << "3. Pre-Order Traversal of TBST" << endl;
        cout << "4. Deleting Node in TBST" << endl;
        cout << "5. Min and max in TBST "<<endl;
        cout << "6. Exit" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "\nEnter Your choice: ";
        cin >> choice;
        int value;
        switch (choice)
        {
        case 1:
        { // Insert Node
            cout << "Enter no. of nodes:" << endl;
            cin >> temp;
            while (temp--)
            {
                cout << "Enter node: ";
                cin >> value;
                tbst.insert(value);
            }
            cout << "Nodes Inserted!" << endl;
            break;
        }
        case 2:
        { // Inorder Traversal
            cout << "Inorder Taversal : " << endl;
            tbst.inorder();
            break;
        }
        case 3:
        {
            cout << "Preorder Traversal: " << endl;
            tbst.preorder();
            break;
        }
        //**********************************************//
        case 4:
        {
            cout << "Enter node to delete: " << endl;
            cin >> temp;
            Node *parent = NULL;
            Node *current = tbst.getRoot();
            if (tbst.search(temp, current, parent))
            {
                tbst.deleteNode(parent, current);
                cout << temp << "deleted!" << endl;
            }
            else
            {
                cout << temp << " not present!" << endl;
            }
        }
        break;
        case 5:
        {
            tbst.min_max();
            break;
        }
        case 6:
        {
            cout << "Exiting....ThankYou:)" << endl;
            c='n';
            break;
        }
        default:
        {
            cout << "Invalid Input" << endl;
            break;
        }
        }
        cout<<"Do you want to continue (y/n) ? :";
        cin>>c;
    }
    return 0;    
}
