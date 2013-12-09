#ifndef MAIN_H
#define MAIN_H

#define INFINITY 2147483647
#define MAX_WEIGHT 50
#define ANT_NUMBER 4
#define ALPHA 2
#define BETA 1
#define RHO 0.1;
#define Q 2.0;
// NAGLOWKI

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <time.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <limits>
#include <random>

// PRZESTRZEN NAZW

using namespace std;

// TYPY

struct Edge
{
	int v;
	int w;
	int pheromone;

	Edge(int v,int w):v(v),w(w)
	{
		pheromone = 0;
	};
};

struct Ant
{
	int path_length;
	int *q;
};

// ZMIENNE
extern int **graph,n;
extern list <Edge> *Graph;



#endif // MAIN_H
