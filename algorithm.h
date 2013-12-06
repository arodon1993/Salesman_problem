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
void ant_colony(); // funkcja wywo�ywacza 

int **initialize_Ants(); // zwraca tablic� z mr�wkami 'liczba mr�wek x liczba_miast'

int *random_Path(const int start); // zwraca losow� �ci��k�

double **Initialize_Pheromones(); // Zwraca tablic� dwuwymiarow� 'liczba_miast x liczba_miast' z feromonami 

void Update_Ants(int **ants, double **pheromones); // przypisuje ka�dej mr�wce wygenerowan� �cie�k�

int *Build_Trail(int k, int start, double **pheromones); // buduje �cie�k� opart� na feromonach, d�ugo�ci i prawdopodobie�stwie

int Next_City(int k, int city, bool *visited, double **pheromones); // zwraca nast�pne miasto do odwiedzenia wed�ug pewnego kryterium i prawdopodobie�stwa

double *Find_Probabilites(int k,const int city, bool *visited, double **pheromones); // sprawdza warunki kra�cowe i wylicza prawdopodobie�stwa wed�ug wzoru

void Update_Pheromones(double **pheromones, int **ants); // Aktualizuje feromony z uwzgl�dnieniem parowania

int length(const int a, const int b); // zwraca d�ugo�� odleg�o�ci mi�dzy dwoma podanymi wierzcho�kami

int Find_Index(const int idx, int *tab); // zwraca numer poszukiwanego indeksu w danej tablicy

bool EdgeInTrail(int cityX, int cityY, int *path); // sprawdza czy podana kraw�d� znajduje si� w cyklu

double MaxValue(); // zwraca maksymaln� warto�� double

double Length(int *ants); // zwraca dlugosc podanej sciezki

int *Best_Path(int **ants); // szuka najlepszej �ciezki w�r�d mr�wek

#endif
