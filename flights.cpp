#include<iostream>
#include<string.h>
using namespace std;

class flight
{ 	 
	public:
		int am[10][10]; //array for amount
		char city_index[10][10]; // array for city
		flight();
	   	int create();
	   	void display(int city_count);
		void inOutDegree(int city_count);
		bool isConnected(int city_count);
		void dfs(int v, bool visited[], int city_count, int &count);
};

flight::flight()
{
	int i,j;
	for(i=0;i<10;i++)
	{
		strcpy(city_index[i],"xx");
	}
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			am[i][j]=0;
		}
	}
}

int flight::create()
{
	int city_count=0,j,si,di,wt;
	char s[10],d[10],c;
	do
	{
		cout<<"\n\tEnter Source City      : ";
		cin>>s;
		cout<<"\n\tEnter Destination City : ";
		cin>>d;
		for(j=0;j<10;j++)
		{
			//if source city is already present in city_index
			if(strcmp(city_index[j],s)==0)
			break;
		}
		if(j==10)	// source city is not present in city_index
		{
			strcpy(city_index[city_count],s);
			city_count++;
		}

		for(j=0;j<10;j++)
		{
			if(strcmp(city_index[j],d)==0)
			break;
		}

		if(j==10)
		{
			strcpy(city_index[city_count],d);
			city_count++;
		}

		cout<<"\n\t Enter Distance From "<<s<<" And "<<d<<": ";
		cin>>wt;

		for(j=0;j<10;j++)
		{
			if(strcmp(city_index[j],s)==0)
				si=j;
			if(strcmp(city_index[j],d)==0)
				di=j;
		}

		am[si][di]=wt;
		cout<<"\n\t Do you want to add more cities.....(y/n) : ";
		cin>>c;	
	}while(c=='y'||c=='Y');
	return(city_count);
}

void flight::display(int city_count)
{
	int i,j;
	cout<<"\n\t Displaying Adjacency Matrix :\n\t";
	for(i=0;i<city_count;i++)
		cout<<"\t"<<city_index[i];
	cout<<"\n";

	for(i=0;i<city_count;i++)
	{
		cout<<"\t"<<city_index[i];
		for(j=0;j<city_count;j++)
		{
		  	cout<<"\t"<<am[i][j];	
		}
		cout<<"\n";
	}
}

void flight::inOutDegree(int city_count)
{
	int inDegree[10] = {0};
	int outDegree[10] = {0};
    //note here we used ++i and not i++
	for (int i = 0; i < city_count; ++i)
	{
		for (int j = 0; j < city_count; ++j)
		{
			if (am[j][i] != 0)
				inDegree[i]++;
			if (am[i][j] != 0)
				outDegree[i]++;
		}
	}

	cout << "\n\tVertex\tIn-Degree\tOut-Degree\n";
	for (int i = 0; i < city_count; ++i)
	{
		cout << "\t" << city_index[i] << "\t" << inDegree[i] << "\t\t" << outDegree[i] << "\n";
	}
}

bool flight::isConnected(int city_count)
{
	bool visited[10];
  //memset is used to initialize the visited array to false, 
  //ensuring that all vertices are initially marked as not visited before performing the depth-first search traversal
	memset(visited, false, sizeof(visited));

	// DFS traversal
	int count = 0;
	dfs(0, visited, city_count, count);

	return count == city_count;
}

void flight::dfs(int v, bool visited[], int city_count, int &count)
{
	visited[v] = true;
	count++;

	for (int i = 0; i < city_count; ++i)
	{
		if (am[v][i] && !visited[i])
			dfs(i, visited, city_count, count);
	}
}

int main()
{
	flight f;
	int n,city_count;
	char c;
	do
	{
		cout<<"\n\t*** Flight Main Menu *****";
		cout<<"\n\t1. Create \n\t2. Adjacency Matrix\n\t3. In-Degree and Out-Degree\n\t4. Check Connectivity\n\t5. Exit";
		cout<<"\n\t.....Enter your choice : ";
		cin>>n;
		switch(n)
		{
			case 1:
					city_count=f.create();
					break;
			case 2:
					f.display(city_count);
					break;
			case 3:
					f.inOutDegree(city_count);
					break;
			case 4:
					if (f.isConnected(city_count))
						cout << "\n\tThe graph is connected.\n";
					else
						cout << "\n\tThe graph is not connected.\n";
					break;
			case 5:
					return 0;
		}
		cout<<"\n\t Do you Want to Continue in Main Menu....(y/n) : ";
		cin>>c;
	}while(c=='y'||c=='Y');
	return 0;
}
