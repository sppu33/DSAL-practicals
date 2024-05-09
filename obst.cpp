// Given sequence k = k1 <k2 < … <kn of n sorted keys, with a successful and unsuccessful 
// search probability pi and qi for each key ki. Build the Binary search tree that has the least 
// search cost given the access probability for each key.
//optimal binary search tree
//dynamic progrramming
#include<iostream>
using namespace std;

class Node{
    int key;
    Node* left=nullptr,* right=nullptr;
    public:
    friend class obst;
};

class obst{
    int R[100][100]; 
    int C[100][100];
    Node* root= nullptr;
//This function calculates the sum of frequencies of keys within a specified range of indices in the freqs array.
    int SumofFrequencies(int * arr, int low, int high){
        int sum=0;
        for(int i=low;i<high ;i++ ){
            sum+=arr[i];
        }
        return sum;
    }
//This function finds the optimal subtree for a given range of keys and updates the cost and root arrays 
//numNodes==>no. of nodes being considered
//n==> total no. of nodes in subtree
/*The function will consider all possible subtrees of length 3.
For each subtree, it will calculate the cost of the left and right subtrees and the sum of frequencies within the subtree range.
It will then select the root that minimizes the total cost of the subtree.
Finally, it will update the cost and root arrays (C and R) with the minimum cost 
and its corresponding root for the subtree range.*/ 
    void findOptimalSubtree(int * freqs, int numNodes, int n){
        // Loop over all possible subtrees of length numNodes within the range of the tree
        for( int i=0;i< n-numNodes;i++){
            //from numNodes till n for j
            int j= numNodes + i;
            //setting the mincost to 9999
            int minCost=9999;
            int minRoot=R[i][j-1];
            //from i+1 to j 
            for(int k=i+1;k<=j;k++){
                //The cost of the subtree is calculated by adding the costs of left and right subtrees and the sum of frequencies of keys within the subtree range.
                int cost = C[i][k-1]+C[k][j];
                if(cost<minCost){
                    minCost=cost;
                    minRoot=k;
                }
            }
            C[i][j]= minCost+SumofFrequencies(freqs,i,j);
            R[i][j]= minRoot;
        }
    }

    Node* constructOBST(int i, int j, int * values){
        if(i==j){
            return nullptr;
        }
        else{
            Node * node= new Node();
            node->key= values[R[i][j]-1];
            node->left=constructOBST(i,R[i][j]-1,values);
            node->right=constructOBST(R[i][j],j,values);
            return node;
        }
    }

    void inOrder(Node * node){
        if(node== nullptr){
            return;
        }
        inOrder(node->left);
        cout<<node->key<<" ";
        inOrder(node->right);
    }

    void preOrder(Node * node){
        if(node== nullptr){
            return;
        }
        cout<<node->key<<" ";
        preOrder(node->left);
        preOrder(node->right);
    }
    public:
    void display(){
        inOrder(this -> root);
        cout<<endl;
        preOrder(this->root);
    }

    void findOBST(int * values, int * freqs, int totalNodes){
        int n=totalNodes+1;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                C[i][j]=0;
                R[i][j]=0;
            }
        }
        for(int i=0;i<n;i++){
            int j=i+1;
            //initilizing the elements above the diagonal
            C[i][j]=freqs[i];
            R[i][j]=j;
        }
        for(int i=2;i<n;i++){
            findOptimalSubtree(freqs,i,n);
        }
        //cout top- roghtmost element of cost array
        cout<<"Cost of OBST is "<<C[0][n-1]<<endl;
        this->root= new Node();
        this->root= constructOBST(0,n-1,values);
    }
};

int main(){
    obst t;
    int nodes;
    cout<<"Enter no of nodes: ";
    cin>>nodes;
    int values[nodes];
    int frequencies[nodes];
    for(int i=0;i<nodes;i++){
        cout<<"Enter value and frequency: ";
        cin>>values[i]>>frequencies[i];
    }
    cout<<endl;
    t.findOBST(values , frequencies , nodes);
    t.display();

    return 0;
}
