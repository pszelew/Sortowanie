#ifndef SORT_H
#define SORT_H
#include <iostream>
#include <cmath>

/*
Klasa sortowanko, modeluj¹ca pojêcie sortowania tablicy





*/

class sortowanko
{
    private:
        sortowanko() {}; //konstrukotr klasy sortowanko
        ~sortowanko() {}; //destruktor klasy sortowanko
        template <class typ>
        static int podziel_tablice(typ *tablica, int pierwszy, int ostatni, bool rosnaco); //dzieli tablice na dwie podtablice z elementami mniejszymi/wiekszymi niz piovot
        template <class typ>
        static void zamien_elementy(typ *tablica, int pierwszy, int drugi); //zamienia miejscami dwa elemenety tablicy
        template <class typ>
        static void polacz_posortowane_tablice(typ *tablica, int lewy, int prawy, int ostatni, bool rosnaco); //laczy dwie posortowane tablice w jedna posortowana calosc
        template <class typ>
        static void heapify(typ *tablica, int pierwszy, int ostatni, int node, bool rosnaco); //tworzy kopiec maksymalny/minimalny
        template <class typ>
        static void intro_sort_temp(typ *tablica,int pierwszy, int ostatni, bool rosnaco, int glebokosc); //statyczna metoda intro_sort_temp - sortowanie intro_sort z parametrem "glebokosc"
        template <class typ>
        static int wybierz_pivot(typ *tablica, int pierwszy, int ostatni); //zwraca mediane z trzech elementow tablicy
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

/*Funkcja zwraca element pivot potrzebny do podzialu tablicy
typ *tablica -> tablica zawierajaca elementy do posortowania
int pierwszy -> pierwszy indeks tablicy do posortowania
int ostatni -> ostatni indeks tablicy do posortowania
*/
template <class typ>
int sortowanko::wybierz_pivot(typ *tablica, int pierwszy, int ostatni)
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
/*
typ *tablica -> tablica zawierajaca tablice do podzialu
int lewy -> pierwszy element tablicy do podzialu
int ostatni -> ostatni element tablicy do podzialu
bool rosnaco -> true gdy elementy sortowane maja byc rosnaco, false gdy elementy sortowane maja byc malejaco
*/

template <class typ>
int sortowanko::podziel_tablice(typ *tablica, int pierwszy, int ostatni, bool rosnaco)
{

        int pivot_idx=wybierz_pivot(tablica,pierwszy,ostatni);
        int pivot = tablica[pivot_idx];   //element porownywany
        int i=pierwszy, j=ostatni; //zmienne sterujace wypelnianiem tablic
        //podziel tablice i na lewo przerzuc elementy mniejsze od pivota, na prawo wieksze od pivota
        if(rosnaco)
        {
            while(true)
            {
                while(tablica[j]>pivot) //jesli kolejnosc ulozenia jest poprawna
                {
                    j--; //dekrementacja prawego wskaznika -> zostaw tak jak bylo
                }
                while(tablica[i]<pivot) ////jesli kolejnosc ulozenia jest poprawna
                {
                    i++; //dekrementacja lewego wskaznika -> zostaw tak jak bylo
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
        else //gdy sortujemy w kolejnosci malejacej
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
void sortowanko::polacz_posortowane_tablice(typ *tablica, int pierwszy, int srodek, int ostatni, bool rosnaco)
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





/*
Metoda zamienia kolejnoœcia dwa elementy tablicy
typ *tablica -> tablica zawierajaca elementy do podzialu
int pierwszy -> pierwszy element do zamiany
int drugi -> drugi element do zamiany
*/

template <class typ>
void sortowanko::zamien_elementy(typ *tablica, int pierwszy, int drugi)
{
    typ i=tablica[pierwszy];
    tablica[pierwszy]=tablica[drugi];
    tablica[drugi]=i;
}
/*
Metoda buduje kopiec maksymalny
typ *tablica -> tablica zawierajaca elementy do podzialu
int pierwszy -> pierwszy indeks kopca
int ostatni -> ostatni indeks kopca
int node -> aktualna galaz
bool rosnaco -> true, gdy sortujemy w kolejnosci rosnacej/ false gdy w kolejnosci malejacej
*/

template <class typ>
void sortowanko::heapify(typ *tablica, int pierwszy, int ostatni, int node, bool rosnaco)
{
    int maximum=node;
    int lewy=2*node-pierwszy+1;
    int prawy=2*node-pierwszy+2;
    if(rosnaco) //jesli tworzymy kopiec maksymalny
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
    else //jesli tworzymy kopiec minimalny
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

/*
Sortowanie przez kopcowanie
typ *tablica -> tablica zawierajaca elementy do posortowania
int pierwszy -> pierwszy indeks tablicy do posortowania
int ostatni -> ostatni indeks tablicy do posortowania
bool rosnaco -> true, gdy sortujemy w kolejnosci rosnacej/ false gdy w kolejnosci malejacej
*/

template <class typ>
void sortowanko::heap_sort(typ *tablica, int pierwszy, int ostatni, bool rosnaco)
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

/*
Sortowanie przez scalanie
typ *tablica -> tablica zawierajaca elementy do posortowania
int pierwszy -> pierwszy indeks tablicy do posortowania
int ostatni -> ostatni indeks tablicy do posortowania
bool rosnaco -> true, gdy sortujemy w kolejnosci rosnacej/ false gdy w kolejnosci malejacej
*/


template <class typ> //sortowanie przez scalanie jako metoda statyczna klasy Sortowanie
void sortowanko::scalanie(typ *tablica, int pierwszy, int ostatni, bool rosnaco)
{

    if (pierwszy<ostatni)
    {
        int srodek = ((pierwszy + ostatni) / 2);
        scalanie(tablica, pierwszy, srodek, rosnaco); //rekurencja dla lewej tablicy
        scalanie(tablica,srodek+1, ostatni,rosnaco); //rekurencja dla prawej tablicy

        polacz_posortowane_tablice(tablica,pierwszy, srodek, ostatni,rosnaco); //laczenie dwoch posortowanych tablic
    }

}

/*
Sortowanie quicksort
typ *tablica -> tablica zawierajaca elementy do posortowania
int pierwszy -> pierwszy indeks tablicy do posortowania
int ostatni -> ostatni indeks tablicy do posortowania
bool rosnaco -> true, gdy sortujemy w kolejnosci rosnacej/ false gdy w kolejnosci malejacej
*/
template <class typ> //quick sort jako metoda statyczna klasy Sortowanie
void sortowanko::quick_sort(typ *tablica, int pierwszy, int ostatni, bool rosnaco)
{
    if(pierwszy<ostatni)
    {

        int granica=podziel_tablice(tablica, pierwszy, ostatni,rosnaco);
        quick_sort(tablica, pierwszy, granica,rosnaco);
        quick_sort(tablica, granica+1, ostatni, rosnaco);
    }
}
/*
Sortowanie hybrydowe -> domyslnie quicksort/ dla glebokich rekurencji heapsort
typ *tablica -> tablica zawierajaca elementy do posortowania
int pierwszy -> pierwszy indeks tablicy do posortowania
int ostatni -> ostatni indeks tablicy do posortowania
bool rosnaco -> true, gdy sortujemy w kolejnosci rosnacej/ false gdy w kolejnosci malejacej
int glebokosc -> maksymalna glebokosc rekurencji dla algorytmu quicksort
*/

template <class typ> //quick sort jako metoda statyczna klasy Sortowanie
void sortowanko::intro_sort_temp(typ *tablica, int pierwszy, int ostatni, bool rosnaco, int glebokosc)
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

/*Sortowanie hybrydowe -> domyslnie quicksort/ dla glebokich rekurencji heapsort, domyslnie ustawiona maksymalna glebokosia rekurenji
typ *tablica -> tablica zawierajaca elementy do posortowania
int pierwszy -> pierwszy indeks tablicy do posortowania
int ostatni -> ostatni indeks tablicy do posortowania
bool rosnaco -> true, gdy sortujemy w kolejnosci rosnacej/ false gdy w kolejnosci malejacej
*/
template <class typ> //quick sort jako metoda statyczna klasy Sortowanie
void sortowanko::intro_sort(typ *tablica, int pierwszy, int ostatni, bool rosnaco)
{
    int glebokosc=2*log(ostatni-pierwszy);
	intro_sort_temp(tablica, pierwszy, ostatni, rosnaco, glebokosc);
}
#endif
