
#include "functions.h"

// ZMIENNE
list <Edge> *Graph = NULL; // zmienna reprezentujaca graf w postaci listy
int **graph = NULL; // zmienna reprezentujaca graf
int n; // zmienna okreslajaca ilosc wierzcholkow



using namespace std;

int main()
{
	srand(time(NULL));
	int choice;
	bool test=true;

	generate();
	create_graph();
	read();
	print();


	while(test)
	{
		cout<<"\tPROGRAM ROZWIAZUJACY PROBLEM KOMIWOJAZERA\n\n";

		cout<<"Wybierz jedna z opcji:";
		cout<<"\n1.Wygeneruj graf do pliku";
		cout<<"\n2.Wczytaj dane z pliku";
		cout<<"\n3.Wypisz graf";
		cout<<"\n4.Rozwiaz problem komiwojazera jednym z algorytmow";
		cout<<"\n5.Zakoncz";
		cout<<"\n\nWybor:";

		cin>>choice;

		switch(choice)
		{
		case 1:
			system("cls");
			cout<<"Podaj ilosc wierzcholkow: ";
			cin>>n;
			generate();
			break;

		case 2:
			create_graph();
			read();
			break;

		case 3:
			print();
			getchar();
			getchar();
			break;

		case 4:
			problem_menu();
			break;

		case 5:
			test=false;
			break;

		}

		system("cls");
	}

}

