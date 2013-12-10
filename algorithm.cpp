#include "algorithm.h"

// ZMIENNE

list <int> *q;
list <int> *sq;
bool *visited,found=false;
int value=0,shortest_path=0;

										  /// BRUTE FORCE ALGORITHMS ///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
           /////                       /////                       /////                       /////            

void brute_force()
{
	visited = new bool[n];
	q = new list<int>;
	sq = new list<int>;
	for(int i=0;i<n;i++) visited[i]=false;

	hamilton_B(0);

	cout<<"Najkrotsza sciezka to: "<<shortest_path<<endl<<"Cykl: ";

	for(list<int>::iterator it = sq->begin();it!=sq->end();it++)
	{
		cout<<*it<<" ";
	}

	delete visited;
	delete q;
	delete sq;
	shortest_path = 0;
	value = 0;

	getchar();
	getchar();
}

void hamilton_B(int v)
{
	q->push_back(v);

	if( (q->size())==n )
	{
			value+=graph[0][v];
			if( (value<shortest_path) || (shortest_path==0) ) 
			{
				shortest_path = value;
				sq->assign(q->begin(), q->end());
			}
			value-=graph[0][v];
	}
	else
	{
		visited[v]= true;

		for(int i=0;i<n;i++)
		{

			if( visited[i] == false ) 
			{
				value+=graph[v][i];
				hamilton_B(i);
				value-=graph[v][i];
			}
		}
		visited[v] = false;
	}
	
	q->pop_back();
}

										  /// GREEDY ALGORITHMS ///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
           /////                       /////                       /////                       /////       

void greedy()
{
	visited = new bool[n];
	q = new list<int>;
	sq = new list<int>;
	for(int i=0;i<n;i++) visited[i]=false;

	for(int i=0;i<n;i++) hamilton_G(i);

	cout<<"Najkrotsza sciezka to: "<<shortest_path<<endl<<"Cykl: ";

	for(list<int>::iterator it = sq->begin();it!=sq->end();it++)
	{
		cout<<*it<<" ";
	}

	delete visited;
	delete q;
	delete sq;

	shortest_path = 0;
	value = 0;
	found=false;

	getchar();
	getchar();
}

int hamilton_G(int v)
{
	q->push_back(v);

	if( (q->size())==n )
	{
		for(list<Edge>::iterator it = Graph[v].begin(); it != Graph[v].end(); it++)
			if((it->v)==0)
			{
				value+=it->w;
				if( (value<shortest_path) || (shortest_path == 0) ) 
				{
					shortest_path = value;
					sq->assign(q->begin(), q->end());
				}
				value=0;
				found = true;
				return 0;
			}

	}
	else
	{
		visited[v]= true;

		for(list<Edge>::iterator it = Graph[v].begin(); it != Graph[v].end(); it++)
		{
			if( visited[it->v] == false ) 
			{
				value+=it->w;
				hamilton_G(it->v);
				if(found) return 0;
				value-=it->w;
			}
		}
		visited[v] = false;
	}
	q->pop_back();
}

										  /// ANT COLONY ALGORITHMS ///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
           /////                       /////                       /////                       /////       
void ant_colony()
{
	srand(time(NULL));

	const int loop_number = 1000;
    
    int** ants = CreateAnts(); 

    int *best_path = ShortestPath(ants);
    
	double bestLength = CycleLength(best_path);

	double **pheromones = InitializePheromones();

    int counter = 0;
       
	while (counter < loop_number)
    {
       UpdateAnts(ants, pheromones);
       UpdatePheromones(pheromones, ants);
           
       int *currBestTrail = ShortestPath(ants);
       double currBestLength = CycleLength(currBestTrail);

	   if (currBestLength < bestLength)
	   {
		   delete best_path;
		   best_path = NULL;
		   bestLength = currBestLength;
           best_path = currBestTrail;
       }
       counter++;
     }

	cout<<bestLength;
	 
	getchar();
	getchar();
}

int **CreateAnts()
{
	int **ants = new int *[ANT_NUMBER];
	int random;

	for(int i=0;i<ANT_NUMBER;i++)
	{
		random = rand() % n;
		ants[i] = CreateRandomPath(random);
	}

	return ants;
}

int *CreateRandomPath(const int start)
{
	vector <int> trail; // wektor opisuj�cy losow� �cie�k�

	for(int i=0;i<n;i++) trail.push_back(i); // wrzucenie do wektora �cie�ki od 0 do n-1

	random_shuffle(trail.begin(),trail.end()); // wymieszanie losowe warto�ci wektora (�cie�ki)

	int temp = FindIndexOf(start,&trail[0]); // Szuka indeks w kt�rym znajduje si� warto�� 'start'
	
	swap(trail[0],trail[temp]);

	int *tab = new int[n];

	for(int i=0;i<n;i++) 
		tab[i] = trail[i];

	return tab; // zwraca adres pocz�tkowy wektora i przypisuje do jakiej� tablicy int
}

double **InitializePheromones()
{
	double **pheromones = new double*[n];
	for (int i=0; i<n; i++)
		pheromones[i] = new double[n];
	for (int i=0; i<n; i++)
	   for (int j=0; j<n; j++)
		pheromones[i][j] = 1.0; // tablica dwuwymiarowa ca�a zape�niana warto�ciami 0.01
	return pheromones;
}

void UpdateAnts(int **ants, double **pheromones)
{ 
  for (int i = 0; i < ANT_NUMBER; i++) 
  {
    int start = rand() % n;
    ants[i] = BuildNewPath(i, start, pheromones);
  }
}

int *BuildNewPath(int k, int start, double **pheromones)
{
  int *trail = new int[n];
  bool *visited = new bool[n];

  trail[0] = start;
  visited[start] = true;

  for (int i = 0; i < n-1; ++i) 
  {
    int city = trail[i];
    int next = ChooseNextCity(k, city, visited, pheromones);
    trail[i+1] = next;
    visited[next] = true;
  }

  return trail;
}

int ChooseNextCity(int k, int city, bool *visited, double **pheromones)
{
  double *probabilites = FindProbabilites(k, city, visited, pheromones);
 
  double *cumul = new double[n + 1];
  cumul[0] = 0.0;
  for (int i = 0; i < n; ++i)
    cumul[i + 1] = cumul[i] + probabilites[i];
 
  random_device rd;
  default_random_engine e( rd() ); // seed PRNG
  uniform_real_distribution <> liczba( 0.0, 1.0 ); // przedzial liczb

  double p = liczba( e );
 
  for (int i = 0; i < n ; i++)
    if (p >= cumul[i] && p < cumul[i + 1])
      return i;
}

int *ShortestPath(int **ants)
{
   double bestLength = CycleLength(ants[0]); 
   int idxBestLength = 0;
   for (int k = 1; k < ANT_NUMBER ; ++k)
   {
     double len = CycleLength(ants[k]);
     if (len < bestLength)
     {
       bestLength = len;
       idxBestLength = k;
     } 
   }

   int *bestPath = new int[n];
   for(int i=0; i<n; i++)
	   bestPath[i] = ants[idxBestLength][i];

   return bestPath;
}

double CycleLength(int *ants)
{
	double value=0;

	for(int i=0;i<n-1;i++)
		value+=EdgeLength(ants[i],ants[i+1]);

	value+=EdgeLength(ants[0],ants[n-1]);

	return value;
}

double *FindProbabilites(int k, const int city, bool *visited, double **pheromones)
{
  double *taueta = new double[n];
  double sum = 0.0;
  for (int i = 0; i < n; ++i) 
  {
    if (i == city)
      taueta[i] = 0.0; // Prawdopodobie�stwo przej�cia z miasta x do miasta x wynosi 0
    else if (visited[i] == true)
      taueta[i] = 0.0; // Prawdopodobie�stwo przej�cia z miasta x do miasta odwiedzonego wynosi 0
    else 
	{
      taueta[i] = pow(pheromones[city][i], ALPHA) * pow((1.0 / EdgeLength(city, i)), BETA); // obliczenie prawdopodobie�stwa wed�ug okre�lonego wzoru
      if (taueta[i] < 0.0001)
        taueta[i] = 0.0001;
      else if (taueta[i] > (MaxValue() / (n * 100)))
        taueta[i] = MaxValue() / (n * 100);
    }
    sum += taueta[i];
  }
 
  double *probs = new double[n];
  for (int i = 0; i <n; ++i)
    probs[i] = taueta[i] / sum;
 
  return probs;
}

void UpdatePheromones(double **pheromones, int **ants)
{
	int rho = RHO;
	int q = Q;
	for (int i = 0; i < n ; ++i)
      {
        for (int j = i + 1; j < n; ++j)
        {
			for (int k = 0; k < ANT_NUMBER; ++k)
			  {
				double length = CycleLength(ants[k]);
				double decrease = (1.0 - rho) * pheromones[i][j];
				double increase = 0.0;
				if (IsEdgeInTrail(i, j, ants[k]) == true) increase = (q / length);

				pheromones[i][j] = decrease + increase;

				if (pheromones[i][j] < 0.0001)
				  pheromones[i][j] = 0.0001;
				else if (pheromones[i][j] > 100000.0)
				  pheromones[i][j] = 100000.0;

				pheromones[j][i] = pheromones[i][j];
			  }
        }
      }
}

bool IsEdgeInTrail(int cityX, int cityY, int *path)
    {
      int lastIndex = n - 1;
      int idx = FindIndexOf(cityX, path);

      if (idx == 0 && path[1] == cityY) return true;
      else if (idx == 0 && path[lastIndex] == cityY) return true;
      else if (idx == 0) return false;
      else if (idx == lastIndex && path[lastIndex - 1] == cityY) return true;
      else if (idx == lastIndex && path[0] == cityY) return true;
      else if (idx == lastIndex) return false;
      else if (path[idx - 1] == cityY) return true;
      else if (path[idx + 1] == cityY) return true;
      else return false;
    }

int EdgeLength(const int a, const int b)
{
	return graph[a][b];
}

int FindIndexOf(const int idx,int *tab)
{
	for(int i=0;i<n;i++)
		if(idx==tab[i]) 
			return i;
}

double MaxValue() 
{
      return numeric_limits<double>::max( );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                  2-Opt    //przyrost czasu przy liczbie wierzcholkow z zakresu 70-75         ///                                             ///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void opt2()
{
    int *path = new int[n];

    for(int i=0; i<n; i++)
        {
            path[i]=i;
        }
    random_shuffle(path,path+n);

    int b1, c1, e1, f1, nr = 0, temp; 
 
    do
    {
        flaga:
        b1 = path[nr]; 
        c1 = path[nr+1]; 
        for (int g=nr+2; g<n-1; g++) 
          {
            e1 = path[g];  
            f1 = path[g+1];  
            if ( (graph[b1][c1]+graph[e1][f1]) > (graph[b1][e1]+graph[c1][f1]) )
              {
                   temp = path[nr+1];
                   path[nr+1] = path[g];
                   path[g] = temp;
                   goto flaga; 
              }
          }
        nr++; 
    }
    while (nr<n-2);
 
    //clock tutaj;
 
    int waga=0;
    for(int i=n-2; i>-1; i--)
    {
        waga+=graph[path[i]][path[i+1]];
    }
 
    cout<<endl<<endl<<"Najkrotsza sciezka to: "<<waga<<endl;
     
    cout<<"Cykl po optymalizacji: ";
        for(int i=0; i<n; i++)
    {
        cout<<path[i]<<" ";
    }
 
    delete path;
    cout<<endl<<endl;
    system("pause");
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                    3-Opt   //u mnie powyżej 13 wierzcholkow duze czasy                       ///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void opt3()
{
	int *path3 = new int[n];

	for(int i=0; i<n; i++)
		{
			path3[i]=i;
		}
	random_shuffle(path3,path3+n);

	int a3, b3, c3, d3, e3, f3, nr3 = 0, temp3, min3; 
	int fixed[7];
	int switcher;

	do
	{
		flaga3:
		a3 = path3[nr3];
		b3 = path3[nr3+1]; 
		for (int g=nr3+2; g<n-3; g++) 
		  {
				c3 = path3[g];  
				d3 = path3[g+1];  
				for (int h=g+2; h<n-1; h++) 
				{
					switcher = 7;
					e3 = path3[h];
					f3 = path3[h+1];
					min3 = graph[a3][b3] + graph[c3][d3] + graph[e3][f3];
					fixed[0]=graph[a3][d3] + graph[e3][b3] + graph[c3][f3];
					fixed[1]=graph[a3][c3] + graph[b3][e3] + graph[d3][f3];
					fixed[2]=graph[a3][d3] + graph[e3][c3] + graph[b3][f3];
					fixed[3]=graph[a3][e3] + graph[d3][b3] + graph[c3][f3];
					//
					fixed[4]=graph[a3][e3] + graph[d3][c3] + graph[b3][f3];
					fixed[5]=graph[a3][b3] + graph[c3][e3] + graph[d3][f3];
					fixed[6]=graph[a3][c3] + graph[b3][d3] + graph[e3][f3];
	
					for (int i=0; i<7; i++)
					{
						if (fixed[i] < min3 )
						{
						   min3 = fixed[i];
							switcher = i;
						}
					}
	
					switch(switcher)
					{
						case 0:
							swap(path3[nr3+1],path3[g+1]);
							swap(path3[g],path3[h]);
							goto flaga3; 
	
						case 1:
							swap(path3[nr3+1],path3[g]);
							swap(path3[g+1],path3[h]);
							goto flaga3; 
	
						case 2:
							temp3=path3[nr3+1];
							path3[nr3+1]=path3[g+1];
							path3[g+1]=path3[g];
							path3[g]=path3[h];
							path3[h]=temp3;
							goto flaga3; 
	
						case 3:
							temp3=path3[nr3+1];
							path3[nr3+1]=path3[h];
							path3[h]=path3[g];
							path3[g]=path3[g+1];
							path3[g+1]=temp3;
							goto flaga3; 
	
						case 4:
							swap(path3[nr3+1],path3[h]);
							swap(path3[g],path3[g+1]);
							goto flaga3; 
	
						case 5:
							swap(path3[g+1],path3[h]);
							goto flaga3; 
	
						case 6:
							swap(path3[nr3+1],path3[g]);
							goto flaga3; 
	
						case 7:
							break;
					}
				}
		  }
		nr3++; 
	}
	while (nr3<n-4);

	int waga3=0;
	for(int i=n-2; i>-1; i--)
	{
		waga3+=graph[path3[i]][path3[i+1]];
	}

	cout<<endl<<endl<<"Najkrotsza sciezka to: "<<waga3<<endl;
	
	cout<<"Cykl po optymalizacji: ";
	    for(int i=0; i<n; i++)
    {
		cout<<path3[i]<<" ";
	}

	delete path3;
	cout<<endl<<endl;
	system("pause");
}
