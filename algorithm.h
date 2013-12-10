#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "main.h"

void greedy();
void brute_force();
void ant_colony();
void hamilton_B(int v);
int hamilton_G(int v);
void opt2();
void opt3();

// ANTS
void ant_colony(); // funkcja wywoływacza 

int **CreateAnts(); // zwraca tablicę z mrówkami 'liczba mrówek x liczba_miast'

int *CreateRandomPath(const int start); // zwraca losową ścieżkę

double **InitializePheromones(); // Zwraca tablicę dwuwymiarową 'liczba_miast x liczba_miast' z feromonami 

void UpdateAnts(int **ants, double **pheromones); // przypisuje każdej mrówce wygenerowaną ścieżkę

int *BuildNewPath(int k, int start, double **pheromones); // buduje ścieżkę opartą na feromonach, długości i prawdopodobieństwie

int ChooseNextCity(int k, int city, bool *visited, double **pheromones); // zwraca następne miasto do odwiedzenia według pewnego kryterium i prawdopodobieństwa

double *FindProbabilites(int k,const int city, bool *visited, double **pheromones); // sprawdza warunki krańcowe i wylicza prawdopodobieństwa według wzoru

void UpdatePheromones(double **pheromones, int **ants); // Aktualizuje feromony z uwzględnieniem parowania

int EdgeLength(const int a, const int b); // zwraca długość odległości między dwoma podanymi wierzchołkami

int FindIndexOf(const int idx, int *tab); // zwraca numer poszukiwanego indeksu w danej tablicy

bool IsEdgeInTrail(int cityX, int cityY, int *path); // sprawdza czy podana krawędź znajduje się w cyklu

double MaxValue(); // zwraca maksymalną wartość double

double CycleLength(int *ants); // zwraca dlugosc podanej sciezki

int *ShortestPath(int **ants); // szuka najlepszej ściezki wśród mrówek

#endif
