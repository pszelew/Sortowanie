
#include<stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include "Sortowanko.h"
int main()
{
	int rozmiar;
	bool rosnaco = true;
	int tryb;
    std::cout << "Hej, program sortuje sobie tablice, bo moze! !\n";
	std::cout << "Podaj wielkosc tablicy";
	std::cin >> rozmiar;
	std::cout<< "Jesli roznaco, podaj 1, jesli malejaco podaj  0";
	std::cin >> rosnaco;
	std::cout<< "Wybierz tryb sortowania: 1-merge sort, 2-quicksort";
	std::cin >> tryb;
	int *tablica = new int[rozmiar];
	srand(time(NULL));
	for (int i = 0; i < rozmiar; i++)
	{
		tablica[i] = rand();
	}
    int tStart, tStop;

    if(tryb==1)
    {
        tStart = clock();
        Sortowanko::scalanie(tablica, 0, rozmiar - 1, rosnaco);
        tStop=clock();
    }
	else if(tryb==2)
    {
        tStart = clock();
        Sortowanko::quick_sort(tablica, 0, rozmiar - 1, rosnaco);
        tStop=clock();
    }

    std::cout<<tStop-tStart<<"ms";

    delete(tablica);
    system("PAUSE");
}

