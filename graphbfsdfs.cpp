/*
________________________________GRAPH_____________________________________

Problem Statement:
Write menu driven C++ program to
1) Represent a given graph using adjacency list/Adjacency Matrix. Use the map of the
area around the college as the graph
2) Display Graph
3) Perform DFS traversal using recursive/non-recursive algorithm.
4) Perform BFS traversal.
                                OR
There are fight paths between the cities. If there is a fight between the city A and B then
there is an edge between the city A to B. The cost of an edge represents the time required
or fuel required to travel from city A to B. Represent this as a graph using adjacency list
where every node of graph represented by city name. 
Perform following operations 
1) calculate in degree, out degree of vertices 
2) check whether graph is connected or not

*/
#include<iostream>
#include<queue>
#include<stack>
// #include<bits/stdc++.h>
using namespace std;

class node{
	private:
		int data;
		node *next;
	public:
	node(){
		//constructor
		this->data=0;
		this->next=nullptr;
	}
	friend class Graph;
};

class Graph{
	private:
		int *visit;
		node **head;

	public:
		int vertices;
		Graph(){
			//constructor
			cout<<"Enter the no. of vertices: ";
			cin>>vertices;
			visit = new int[vertices];
			head = new node*[vertices];
			for(int i=0;i<vertices;i++){
				head[i]=new node();
				head[i]->data=i;
			}
			//cout<<"Constructor call completed"<<endl;
		}

		void create(){
			// for creating a graph
			int no;
			for(int i=0;i<vertices;i++){
				node *p =head[i];
				cout<<"Enter the no. of vertices adjacent to "<<i<<" :";
				cin>>no;
				if(no==0){
					head[i]=NULL;
				}
				else{
					int v =-1;
					for(int i=0;i<no;i++){
						node* temp=new node();
						cout<<"Enter vertex number"<<endl;
						cin>>v;
						if(v<0 || v>=vertices)
						{
							cout<<"Invalid vertex"<<endl;
						}
						else{
							temp->data=v;
							temp->next=NULL;
							p->next=temp;
							p=temp;
						}
					}
				}
			}
		}
		void show(){
			for(int i=0;i<vertices;i++){
				node *temp=head[i];
				while(temp!=NULL){
					cout<<temp->data<<"->";
					temp=temp->next;
				}
				cout<<endl;
			}
		}

		void clear(){
			for(int i=0;i<vertices;i++){
				visit[i]=0;
			}
		}

		void BFS(int x){
			node *temp;
			queue<node*> q;
			cout<<head[x]->data<<endl;
			visit[x]=1;
			q.push(head[x]);
			while(q.empty()==0){
				temp=q.front();
				q.pop();
				temp=temp->next;
				while(temp!=NULL){
					if(visit[temp->data]==0){
						q.push(head[temp->data]);
						cout<<temp->data<<" ";
						visit[temp->data]=1;
					}
					temp=temp->next;
				}
				cout<<endl;
				
			}
		}

		void DFS(int v){
				node *temp;
				temp=head[v];
				cout<<temp->data<<" ";
				visit[v]=1;
				temp=temp->next;
				while(temp!=NULL){
					if(visit[temp->data]==0){
						DFS(temp->data);
					}
					temp=temp->next;
				}
		}

		void DFS_Non(int v)
		{
			stack<node*> s;
			node* temp=head[v];
			s.push(temp);
			while(s.empty()==0)
			{
				node* p=s.top();
				s.pop();
				if(visit[p->data]==0)
				{
					cout<<p->data<<" ";
					visit[p->data]=1;
					p=head[p->data]->next;
					while(p!=NULL)
					{
						if(visit[p->data]==0)
						{
							s.push(p);
						}
							p=p->next;
					}
				}
			}
		}
		
};


int main()
{	Graph G;
	G.create();
	cout<<"_____GRAPH_____"<<endl;
	G.show();
	cout<<"_____BFS_____"<<endl;
	G.BFS(1);
	G.clear();
	cout<<endl;
	cout<<"_____DFS_____"<<endl;
	G.DFS(1);
	G.clear();
	cout<<endl;
	cout<<"_____DFS_Non_____"<<endl;
	G.DFS_Non(1);
	cout<<endl;
	return 0;
}
