// You have a business with several offices; you want to lease phone lines to connect them 
// up with each other; and the phone company charges different amounts of money to 
// connect different pairs of cities. You want a set of lines that connects all your offices with 
// a minimum total cost. Solve the problem by using weighted graph and applying minimum 
// spanning tree algorithm. 

#include<iostream>
using namespace std;

class tree{
    int a[20][20],l,u,w,i,j,v,e,visited[20];
    public:
    void input();
    void display();
    void minimum();
};

void tree::input(){
    cout<<"Enter the total number of company branches: ";
    cin>>v;
    for(i=0;i<v;i++){
        visited[i]=0;//initializing whole visited array to 0
        for(j=0;j<v;j++){
            a[i][j]=999; // initializing the adjacent matrix with 999
        }
    }

    cout<<"Enter the number of connections : ";
    cin>>e;
    for(i=0;i<e;i++){
        cout<<"Enter the end branches of the connections: "<<endl;
        cin>>l>>u;  //enter the branch1 and branch2
        cout<<"Enter the phone company charges for this connection : "<<endl;
        cin>>w;     //weight of each connection
        a[l-1][u-1]=a[u-1][l-1]=w;  //set the value of adj. matrix accordingly

    }
}

void tree::display(){
    cout<<"\n Adjaceny Matrix : ";
    for(i=0;i<v;i++){
        cout<<endl;
        for(j=0;j<v;j++){
            cout<<a[i][j]<<"    ";
        }
        cout<<endl;
    }
}
//***********************************************************//
void tree:: minimum(){
    int p=0,q=0,total=0,min;
    visited[0]=1;//initializing visited array of 1st place with 1
    for(int count=0;count<(v-1);count++){
        min=999;
        for(i=0;i<v;i++){
            if(visited[i]==1){// if one office is visited
                for(j=0;j<v;j++){
                    if(visited[j]!=1){//if another office is not visited
                        if(min> a[i][j]){
                            min=a[i][j];
                            p=i;
                            q=j;
                        }
                    }
                }
            }
        }
        visited[p]=1;
        visited[q]=1;
        total+=min;
        cout<<"Minimum cost of connection for "<<(p+1)<<" --> "<<(q+1)<<" is "<<min<<endl;
    }
    cout<<"The minimum total cost of connections of all branches is: "<<total<<endl;
}

int main(){
    int ch;
    tree T;
    do{
        cout<<"===Prims Algo=== \n";
        cout<<"\n 1. Input \n 2.Display \n 3. Minimum cost"<<endl;
        cout<<"Enter your choice : ";
        cin>>ch;
        switch(ch){
            case 1:
            cout<<" INPUT "<<endl;
            T.input();
            break;
            case 2:
            cout<<" DISPLAY "<<endl;
            T.display();
            break;
            case 3:
            cout<<" MINIMUM COST "<<endl;
            T.minimum();
            break;
        }
    }while(ch!=4);
    return 0;
}
