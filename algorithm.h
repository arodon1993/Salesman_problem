#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "main.h"

void greedy();
void brute_force();
void ant_colony();
void hamilton_B(int v);
int hamilton_G(int v);

// ANTS
void ant_colony(); // funkcja wywo³ywacza 

int **initialize_Ants(); // zwraca tablicê z mrówkami 'liczba mrówek x liczba_miast'

int *random_Path(const int start); // zwraca losow¹ œciê¿kê

double **Initialize_Pheromones(); // Zwraca tablicê dwuwymiarow¹ 'liczba_miast x liczba_miast' z feromonami 

void Update_Ants(int **ants, double **pheromones); // przypisuje ka¿dej mrówce wygenerowan¹ œcie¿kê

int *Build_Trail(int k, int start, double **pheromones); // buduje œcie¿kê opart¹ na feromonach, d³ugoœci i prawdopodobieñstwie

int Next_City(int k, int city, bool *visited, double **pheromones); // zwraca nastêpne miasto do odwiedzenia wed³ug pewnego kryterium i prawdopodobieñstwa

double *Find_Probabilites(int k,const int city, bool *visited, double **pheromones); // sprawdza warunki krañcowe i wylicza prawdopodobieñstwa wed³ug wzoru

void Update_Pheromones(double **pheromones, int **ants); // Aktualizuje feromony z uwzglêdnieniem parowania

int length(const int a, const int b); // zwraca d³ugoœæ odleg³oœci miêdzy dwoma podanymi wierzcho³kami

int Find_Index(const int idx, int *tab); // zwraca numer poszukiwanego indeksu w danej tablicy

bool EdgeInTrail(int cityX, int cityY, int *path); // sprawdza czy podana krawêdŸ znajduje siê w cyklu

double MaxValue(); // zwraca maksymaln¹ wartoœæ double

double Length(int *ants); // zwraca dlugosc podanej sciezki

int *Best_Path(int **ants); // szuka najlepszej œciezki wœród mrówek

#endif