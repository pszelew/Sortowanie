#ifndef SORT_H
#define SORT_H
#include <iostream>
class Sortowanko
{
private:
	Sortowanko() {}; //konstrukotr klasy sortowanko
	~Sortowanko() {}; //dekonstruktor klasy sortowanko
    template <class typ>
	static void zamien_elementy(typ *tablica, int pierwszy, int drugi);
public:
    template <class typ>
	static void scalanie(typ *tablica, int pierwszy, int ostatni, bool rosnaco); //statyczna metoda scalanie
	template <class typ>
	static void quick_sort(typ *tablica,int pierwszy, int ostatni, bool rosnaco); //statyczna metoda quick_sort
};


template <class typ>
void Sortowanko::zamien_elementy(typ *tablica, int pierwszy, int drugi)
{
    typ i=tablica[pierwszy];
    tablica[pierwszy]=tablica[drugi];
    tablica[drugi]=i;
}

template <class typ> //sortowanie przez scalanie jako metoda statyczna klasy Sortowanie
void Sortowanko::scalanie(typ *tablica, int pierwszy, int ostatni, bool rosnaco)
{
    int srodek;

    if (pierwszy<ostatni)
    {
        int prawy, lewy, sortowany; //zmienna ustalajaca srodek tablicy ,  zmienne pomocniczne w procesie laczenia tablic
        typ tablica_temp[ostatni-pierwszy+1]; //tablica pomocnicza przy zamianie zmiennych
        srodek = ((pierwszy + ostatni) / 2);
        scalanie(tablica, pierwszy, srodek, rosnaco); //rekurencja dla lewej tablicy
        scalanie(tablica,srodek+1, ostatni,rosnaco); //rekurencja dla prawej tablicy

        /*Laczenie dwoch tablic wraz z sortowaniem*/
        lewy = pierwszy;
        prawy = srodek + 1;
        sortowany = 0;
        while (lewy <= srodek && prawy <= ostatni)
        {
            if(rosnaco)
            {
                if (tablica[lewy] < tablica[prawy]) //jezeli lewy mniejsz, to on bedzie nastepny w tablicy -> porownaj nastepny lewy
                {
                    tablica_temp[sortowany++] = tablica[lewy++];
                }
                else
                {
                    tablica_temp[sortowany++] = tablica[prawy++]; //jezeli prawy mniejszy, to on bedzie nastepny w tablicy -> porownaj nastepny prawy
                }
            }
            else
            {
                if (tablica[lewy] > tablica[prawy]) //jezeli lewy mniejsz, to on bedzie nastepny w tablicy -> porownaj nastepny lewy
                {
                    tablica_temp[sortowany++] = tablica[lewy++];
                }
                else
                {
                    tablica_temp[sortowany++] = tablica[prawy++]; //jezeli prawy mniejszy, to on bedzie nastepny w tablicy -> porownaj nastepny prawy
                }
            }
        }
        while (lewy <= srodek)
        {
             tablica_temp[sortowany++] = tablica[lewy++]; //jezli prawa tablica skonczyla sie szybciej, to nastepne elementy beda pochodzic z lewej tablicy
        }

        while(prawy<=ostatni)
        {
             tablica_temp[sortowany++] = tablica[prawy++]; //jezli prawa tablica skonczyla sie szybciej, to nastepne elementy beda pochodzic z lewej tablicy
        }

        for ( int i = pierwszy, j = 0; i <= ostatni; i++, j++ )
            tablica[i] = tablica_temp[j];
    }
}

template <class typ> //quick sort jako metoda statyczna klasy Sortowanie
void Sortowanko::quick_sort(typ *tablica, int pierwszy, int ostatni, bool rosnaco)
{
    if(pierwszy<ostatni)
    {
        //podziel tablice i na lewo przerzuc elementy mniejsze od i, na prawo wieksze od i
        typ pivot=tablica[ostatni];    //element porownywany
        int i=pierwszy, granica=pierwszy; //zmienne sterujace wypelnianiem tablic
        if(rosnaco)
        {
            while(i<ostatni)
            {
                if(tablica[i]<pivot)
                {
                    zamien_elementy(tablica,i++,granica++);
                }
                else
                {
                    i++;
                }
            }
        }
        else
        {
            while(i<ostatni)
            {
                if(tablica[i]>pivot)
                {
                    zamien_elementy(tablica,i++,granica++);
                }
                else
                {
                    i++;
                }
            }
        }
        zamien_elementy(tablica,ostatni,granica);
        quick_sort(tablica, pierwszy, granica-1,rosnaco);
        quick_sort(tablica, granica+1, ostatni, rosnaco);
    }
}
#endif
