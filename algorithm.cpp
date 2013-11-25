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
	const int loop_number = 1000;
    
    int** ants = initialize_Ants(); 
 
    int *best_path = Best_Path(ants);
    
	double bestLength = Length(best_path);
 
	double **pheromones = Initialize_Pheromones();
 
    int counter = 0;
       
	while (counter < loop_number)
    {
       Update_Ants(ants, pheromones);
       Update_Pheromones(pheromones, ants);
           
       int *currBestTrail = Best_Path(ants);
       double currBestLength = Length(currBestTrail);
       
	   if (currBestLength < bestLength)
	   {
         bestLength = currBestLength;
         best_path = currBestTrail;
       }
       counter++;
     }

	getchar();
	getchar();
}

int **initialize_Ants()
{
	int **ants = new int *[ANT_NUMBER];
	int random;

	for(int i=0;i<ANT_NUMBER;i++)
	{
		random = rand() % n;
		ants[i] = random_Path(random);
	}

	return ants;
}

int *random_Path(const int start)
{
	vector <int> trail; // wektor opisuj¹cy losow¹ œcie¿kê

	for(int i=0;i<n;i++) trail.push_back(i); // wrzucenie do wektora œcie¿ki od 0 do n-1

	random_shuffle(trail.begin(),trail.end()); // wymieszanie losowe wartoœci wektora (œcie¿ki)

	int temp = Find_Index(start,&trail[0]); // Szuka indeks w którym znajduje siê wartoœæ 'start'
	
	swap(trail[0],trail[temp]);

	return &trail[0]; // zwraca adres pocz¹tkowy wektora i przypisuje do jakiejœ tablicy int
}

double **Initialize_Pheromones()
{
	double **pheromones = new double*[n];
	for (int i=0; i<n; i++)
		pheromones[i] = new double[n];
	for (int i=0; i<n; i++)
	   for (int j=0; j<n; j++)
		pheromones[i][j] = 0.01; // tablica dwuwymiarowa ca³a zape³niana wartoœciami 0.01
	return pheromones;
}

void Update_Ants(int **ants, double **pheromones)
{ 
  for (int i = 0; i < ANT_NUMBER; i++) 
  {
    int start = rand() % n;
    ants[i] = Build_Trail(i, start, pheromones);
  }
}

int *Build_Trail(int k, int start, double **pheromones)
{

  int *trail = new int[n];
  bool *visited = new bool[n];

  trail[0] = start;
  visited[start] = true;

  for (int i = 0; i < n-1; ++i) 
  {
    int city = trail[i];
    int next = Next_City(k, city, visited, pheromones);
    trail[i+1] = next;
    visited[next] = true;
  }
  return trail;
}

int Next_City(int k, int city, bool *visited, double **pheromones)
{
  double *probs = Find_Probabilites(k, city, visited, pheromones);
 
  double *cumul = new double[n + 1];
  for (int i = 0; i < n; ++i)
    cumul[i + 1] = cumul[i] + probs[i];
 
  random_device rd;
  default_random_engine e( rd() ); // seed PRNG
  uniform_real_distribution <> liczba( 0.0, 1.0 ); // przedzial liczb

  double p = liczba( e );
 
  for (int i = 0; i < n ; ++i)
    if (p >= cumul[i] && p < cumul[i + 1])
      return i;
}

int *Best_Path(int **ants)
{
   double bestLength = Length(ants[0]); 
   int idxBestLength = 0;
   for (int k = 1; k < ANT_NUMBER ; ++k)
   {
     double len = Length(ants[k]);
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

double Length(int *ants)
{
	double value=0;

	for(int i=0;i<n;i++)
		value+=ants[i];

	return value;
}

double *Find_Probabilites(int k, const int city, bool *visited, double **pheromones)
{
  double *taueta = new double[n];
  double sum = 0.0;
  for (int i = 0; i < n; ++i) 
  {
    if (i == city)
      taueta[i] = 0.0; // Prawdopodobieñstwo przejœcia z miasta x do miasta x wynosi 0
    else if (visited[i] == true)
      taueta[i] = 0.0; // Prawdopodobieñstwo przejœcia z miasta x do miasta odwiedzonego wynosi 0
    else 
	{
      taueta[i] = pow(pheromones[city][i], ALPHA) * pow((1.0 / length(city, i)), BETA); // obliczenie prawdopodobieñstwa wed³ug okreœlonego wzoru
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

void Update_Pheromones(double **pheromones, int **ants)
{
	int rho = RHO;
	int q = Q;
	for (int i = 0; i < n ; ++i)
      {
        for (int j = i + 1; j < n; ++j)
        {
			for (int k = 0; k < ANT_NUMBER; ++k)
          {
            double length = Length(ants[k]);
            double decrease = (1.0 - rho) * pheromones[i][j];
            double increase = 0.0;
            if (EdgeInTrail(i, j, ants[k]) == true) increase = (q / length);

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

bool EdgeInTrail(int cityX, int cityY, int *path)
    {
      int lastIndex = n - 1;
      int idx = Find_Index(cityX, path);

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

int length(const int a, const int b)
{
	return graph[a][b];
}

int Find_Index(const int idx,int *tab)
{
	for(int i=0;i<n;i++)
		if(idx==tab[i]) 
			return i;
}

double MaxValue() 
{
      return numeric_limits<double>::max( );
}

/////////////////////////////
           /////
/////////////////////////////