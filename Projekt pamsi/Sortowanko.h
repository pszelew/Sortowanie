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
	template <class typ>
    static void polacz_posortowane_tablice(typ *tablica, int lewy, int prawy, int ostatni, bool rosnaco);
public:

    template <class typ>
	static void scalanie(typ *tablica, int pierwszy, int ostatni, bool rosnaco); //statyczna metoda scalanie
	template <class typ>
	static void quick_sort(typ *tablica,int pierwszy, int ostatni, bool rosnaco); //statyczna metoda quick_sort
	template <class typ>
	static void intro_sort(typ *tablica,int pierwszy, int ostatni, bool rosnaco); //statyczna metoda intro_sort
};

/*
typ *tablica -> tablica zawierajaca dwie posortowane podtablice
int lewy -> pierwszy element lewej tablicy
int srodek -> ostatni element lewej tablicy
int ostatni -> ostatni element prawej tablicy
bool rosnaco -> true gdy elementy sortowane maja byc rosnaco, false gdy elementy sortowane maja byc malejaco
*/


template <class typ>
void Sortowanko::polacz_posortowane_tablice(typ *tablica, int pierwszy, int srodek, int ostatni, bool rosnaco)
{
    int sortowany=0;
    int prawy=srodek+1;
    int lewy=pierwszy;
    typ tablica_temp[ostatni-lewy+1];

    while (lewy <= srodek && prawy <= ostatni) //petla laczaca dwie posortowane tablice
    {
            if(rosnaco)
            {
                if (tablica[lewy] < tablica[prawy]) //jezeli lewy mniejszy, to on bedzie nastepny w tablicy -> porownaj nastepny lewy
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
                if (tablica[lewy] > tablica[prawy]) //jezeli prawy mniejszy, to on bedzie nastepny w tablicy -> porownaj nastepny element od lewej
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
             tablica_temp[sortowany++] = tablica[prawy++]; //jezeli lewa tablica skonczyla sie szybciej, to uzupelniamy reszte elementami prawej tablicy
        }

        for ( int i = pierwszy, j = 0; i <= ostatni; i++, j++ ) //przepisanie elementow z tablicy_tmp do ostatecznej
            tablica[i] = tablica_temp[j];
}




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

    if (pierwszy<ostatni)
    {
        int srodek = ((pierwszy + ostatni) / 2);
        scalanie(tablica, pierwszy, srodek, rosnaco); //rekurencja dla lewej tablicy
        scalanie(tablica,srodek+1, ostatni,rosnaco); //rekurencja dla prawej tablicy

        polacz_posortowane_tablice(tablica,pierwszy, srodek, ostatni,rosnaco); //laczenie dwoch posortowanych tablic
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
