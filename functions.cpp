#include "functions.h"


void problem_menu()
{
	system("cls");

	int choice;

	cout<<"Wybierz jeden z algorytmow:\n";
	cout<<"1. Brute Force\n";
	cout<<"2. Greedy\n";
	cout<<"3. Aunt colony\n";
	cout<<"4. 2-opt\n";
	cout<<"5. 3-opt\n";
	cout<<"0. Wstecz\n";
	cout<<"\nWybor: ";

	cin>>choice;

	switch(choice)
	{
	case 1:
		brute_force();
		break;

	case 2:
		greedy();
		break;

	case 3:
		ant_colony();
		break;

	case 4:
		opt2();
		break;
	case 5:
		opt3();
		break;

	case 0:
		break;

}

void generate()
{
	int m = (n*(n-1))/2 ;

	srand(time(0));

	fstream file;
	file.open("dane/data.txt",ios::out);

	for(int i=0;i<m;i++)
	{
		file << rand() % MAX_WEIGHT;
		file << "\n";
	}

	file.close();
}

void create_graph()
{

	graph = new int *[n];
	
	for(int i=0;i<n;i++) graph[i] = new int[n];

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++) graph[i][j] = INFINITY;

	Graph = new list<Edge>[n];
	
}

void read()
{
	int weight;

	fstream file;

	file.open("dane/data.txt",ios::in);

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i==j) continue;
			else if(graph[i][j]==INFINITY)
			{
				file >> weight; 
				graph[i][j] = weight;
				graph[j][i] = weight;
			}
		}
	}

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i==j) continue;
			insert_sort(i,j,graph[i][j]);

		}
	}

	file.close();
}

int insert_sort(int v1,int v2,int weight)
{

	if(Graph[v1].size()==0)
	{
		Graph[v1].push_front(Edge(v2,weight));
	}
	else
	{
		for(list<Edge>::iterator it=Graph[v1].begin();it!=Graph[v1].end();it++)
		{
			if( weight < it->w)
			{
				Graph[v1].insert(it,Edge(v2,weight));
				return 0;
			}
		}
		Graph[v1].push_back(Edge(v2,weight));
	}


}

void print()
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			cout<<graph[i][j]<<"\t";

		cout<<endl;
	}

	cout<<endl<<endl;

	for(int i=0;i<n;i++)
	{
		cout<<i<<": ";
		for( list<Edge>::iterator it = Graph[i].begin(); it!=Graph[i].end(); it++)
		{
			cout<<it->v<<" ";
		}
		cout<<endl;
	}
}
