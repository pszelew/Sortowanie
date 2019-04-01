#ifndef SORT_H
#define SORT_H
#include <iostream>
#include <cmath>
class Sortowanko
{
    private:
        Sortowanko() {}; //konstrukotr klasy sortowanko
        ~Sortowanko() {}; //destruktor klasy sortowanko
        template <class typ>
        static int podziel_tablice(typ *tablica, int pierwszy, int ostatni, bool rosnaco);
        template <class typ>
        static void zamien_elementy(typ *tablica, int pierwszy, int drugi);
        template <class typ>
        static void polacz_posortowane_tablice(typ *tablica, int lewy, int prawy, int ostatni, bool rosnaco);
        template <class typ>
        static void heapify(typ *tablica, int pierwszy, int ostatni, int node, bool rosnaco);
        template <class typ>
        static void intro_sort_temp(typ *tablica,int pierwszy, int ostatni, bool rosnaco, int glebokosc); //statyczna metoda intro_sort
        template <class typ>
        static int wybierz_pivot(typ *tablica, int pierwszy, int ostatni);
    public:
        template <class typ>
        static void heap_sort(typ *tablica, int pierwszy, int ostatni, bool rosnaco); //statyczna metoda kopcowanie
        template <class typ>
        static void scalanie(typ *tablica, int pierwszy, int ostatni, bool rosnaco); //statyczna metoda scalanie
        template <class typ>
        static void quick_sort(typ *tablica,int pierwszy, int ostatni, bool rosnaco); //statyczna metoda quick_sort
        template <class typ>
        static void intro_sort(typ *tablica,int pierwszy, int ostatni, bool rosnaco); //statyczna metoda intro_sort
};

template <class typ>
int Sortowanko::wybierz_pivot(typ *tablica, int pierwszy, int ostatni)
{
    int srodek=(pierwszy+ostatni)/2;
    int a=tablica[pierwszy];
    int b=tablica[srodek];
    int c=tablica[ostatni];
    if (a < b && b < c)
        return (srodek);
    if (a < c && c <= b)
        return (ostatni);
    if (b <= a && a < c)
        return (pierwszy);
    if (b < c && c <= a)
        return (ostatni);
    if (c <= a && a < b)
        return (pierwszy);
    if (c <= b && b <= a)
        return (srodek);
    return 0;
}


template <class typ>
int Sortowanko::podziel_tablice(typ *tablica, int pierwszy, int ostatni, bool rosnaco)
{
    //podziel tablice i na lewo przerzuc elementy mniejsze od i, na prawo wieksze od i
        int pivot_idx=wybierz_pivot(tablica,pierwszy,ostatni);
        int pivot = tablica[pivot_idx];   //element porownywany
        int i=pierwszy, j=ostatni; //zmienne sterujace wypelnianiem tablic
        if(rosnaco)
        {
            while(true)
            {
                while(tablica[j]>pivot)
                {
                    j--;
                }
                while(tablica[i]<pivot)
                {
                    i++;
                }

                if (i < j) // gdy liczniki sie jeszcze nie minely, ale trzeba zamienic liczby
                {
                    zamien_elementy(tablica, i, j);
                    i++;
                    j--;
                }
                else
                    return j; //poszukiwana granica podzialu
            }
        }
        else
        {
             while(true)
            {
                while(tablica[j]<pivot)
                {
                    j--;
                }
                while(tablica[i]>pivot)
                {
                    i++;
                }

                if (i < j) // gdy liczniki sie jeszcze nie minely, ale trzeba zamienic liczby
                {
                    zamien_elementy(tablica, i, j);
                    i++;
                    j--;
                }
                else
                    return j; //poszukiwana granica podzialu
            }
        }
}




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
/*Budujemy kopiec poczawszy od dolu*/

template <class typ>
void Sortowanko::heapify(typ *tablica, int pierwszy, int ostatni, int node, bool rosnaco)
{
    int maximum=node;
    int lewy=2*node-pierwszy+1;
    int prawy=2*node-pierwszy+2;
    if(rosnaco)
    {
        if(lewy<=ostatni&&tablica[lewy]>tablica[maximum])
        {
            maximum=lewy;
        }
        if(prawy<=ostatni&&tablica[prawy]>tablica[maximum])
        {
            maximum=prawy;
        }

        if(node!=maximum)
        {
            zamien_elementy(tablica, maximum, node);
            heapify(tablica, pierwszy, ostatni, maximum, rosnaco);
        }
    }
    else
    {
        if(lewy<=ostatni&&tablica[lewy]<tablica[maximum])
        {
            maximum=lewy;
        }
        if(prawy<=ostatni&&tablica[prawy]<tablica[maximum])
        {
            maximum=prawy;
        }

        if(node!=maximum)
        {
            zamien_elementy(tablica, maximum, node);
            heapify(tablica, pierwszy, ostatni, maximum, rosnaco);
        }
    }
}

template <class typ>
void Sortowanko::heap_sort(typ *tablica, int pierwszy, int ostatni, bool rosnaco)
{
    /*Z drzewa binarnego tworzymy kopiec */
    for(int i=((ostatni+pierwszy-1)/2);i>=pierwszy;i--)
    {
            heapify(tablica, pierwszy, ostatni, i, rosnaco);
    }

    for(int i=ostatni;i>=pierwszy;i--)
    {
        zamien_elementy(tablica, pierwszy, i);
        /*Wywolanie kopcowania dla zredukowanego kopca*/
        heapify(tablica, pierwszy, i-1, pierwszy, rosnaco);
    }
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

        int granica=podziel_tablice(tablica, pierwszy, ostatni,rosnaco);
        quick_sort(tablica, pierwszy, granica,rosnaco);
        quick_sort(tablica, granica+1, ostatni, rosnaco);
    }
}
/*Sortowanie hybrydowe-> quick sort i heap sort*/
template <class typ> //quick sort jako metoda statyczna klasy Sortowanie
void Sortowanko::intro_sort_temp(typ *tablica, int pierwszy, int ostatni, bool rosnaco, int glebokosc)
{
	if (pierwszy < ostatni)
	{
		if(glebokosc <= 0)
		{
			heap_sort(tablica, pierwszy, ostatni, rosnaco);
			return;
        }
        int granica=podziel_tablice(tablica, pierwszy, ostatni,rosnaco);
        intro_sort_temp(tablica, pierwszy, granica,rosnaco, glebokosc-1);
        intro_sort_temp(tablica, granica+1, ostatni,rosnaco, glebokosc-1);
    }
}


template <class typ> //quick sort jako metoda statyczna klasy Sortowanie
void Sortowanko::intro_sort(typ *tablica, int pierwszy, int ostatni, bool rosnaco)
{
    int glebokosc=2*log(ostatni-pierwszy);
	intro_sort_temp(tablica, pierwszy, ostatni, rosnaco, glebokosc);
}
#endif
