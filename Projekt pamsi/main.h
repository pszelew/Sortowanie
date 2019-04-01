#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include "Sortowanko.h"
#include<stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>

template <class typ>
bool test_posortowania(typ *tablica, int pierwszy, int ostatni, bool rosnaco)
{
    if(rosnaco)
    {
        for(int i=pierwszy;i<ostatni;i++)
        {
            if(tablica[i]>tablica[i+1])
                return false;
        }
    }
    else
    {
        for(int i=pierwszy;i<ostatni;i++)
        {
            if(tablica[i]<tablica[i+1])
                return false;
        }
    }
    return true;
}

template <class typ>
bool test_wydajnosci(typ *parametry, int ilosc_tablic, bool rosnaco) // parametry[]={sortowanie, tryb, rozmiar}
{
    double TAB_Z[]={0.25,0.5,0.75,0.95,0.99,0.997};
    int ROZMIAR_TAB[]={10000,50000,100000,500000,1000000};
    int rozmiar=ROZMIAR_TAB[parametry[2]-1];
    std::fstream merge_sort;
    std::fstream quick_sort;
    std::fstream intro_sort;
    merge_sort.open("merge_sort.txt", std::ios::out|std::ios::app);
    quick_sort.open("quick_sort.txt", std::ios::out|std::ios::app);
    intro_sort.open("intro_sort.txt", std::ios::out|std::ios::app);
    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;

    srand(time(NULL));

    int wielkosc_tablicy=rozmiar*ilosc_tablic;
    int *tablica = new int[wielkosc_tablicy];

    for(int i=0;i<wielkosc_tablicy;i++) //wypelniam tablice losowo
    {
        tablica[i]=rand();
    }

    if(parametry[1]>1&&parametry[1]<8)
    {
        for(int i=0;i<wielkosc_tablicy;i=i+rozmiar)
        {
            Sortowanko::quick_sort(tablica, i, TAB_Z[parametry[1]-2]*(i+rozmiar)-1, rosnaco);
        }
    }
    if(parametry[1]==8)
    {
        for(int i=0;i<wielkosc_tablicy;i=i+rozmiar)
        {
            Sortowanko::quick_sort(tablica, i, (i+rozmiar)-1, !rosnaco);
        }
    }

     if(parametry[0]==1)
    {
        t1 = std::chrono::high_resolution_clock::now();
        for(int i=0;i<wielkosc_tablicy;i=i+rozmiar)
            Sortowanko::scalanie(tablica, i, (i+rozmiar) - 1, rosnaco);
        t2 = std::chrono::high_resolution_clock::now();
        merge_sort <<parametry[1]<<";" <<rozmiar<< ";"<<ilosc_tablic<<";"<<std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<std::endl;
    }

    else if(parametry[0]==2)
    {
        t1 = std::chrono::high_resolution_clock::now();
        for(int i=0;i<wielkosc_tablicy;i=i+rozmiar)
            Sortowanko::quick_sort(tablica, i, (i+rozmiar) - 1, rosnaco);
        t2 = std::chrono::high_resolution_clock::now();
        quick_sort <<parametry[1]<<";" <<parametry[2]<< ";"<<ilosc_tablic<<";"<<std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<std::endl;
    }

    else if(parametry[0]==3)
    {
        t1 = std::chrono::high_resolution_clock::now();
        for(int i=0;i<wielkosc_tablicy;i=i+rozmiar)
            Sortowanko::intro_sort(tablica, i, (i+rozmiar) - 1, rosnaco);
        t2 = std::chrono::high_resolution_clock::now();
        intro_sort <<parametry[1]<<";" <<parametry[2]<< ";"<<ilosc_tablic<<";"<<std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()<<std::endl;
    }


    for(int i=0;i<wielkosc_tablicy;i=i+rozmiar)
    {
        if(!test_posortowania(tablica, i, (i+rozmiar) - 1, rosnaco))
            return(false);
    }

    delete [] tablica;
    merge_sort.close();
    quick_sort.close();
    intro_sort.close();
    return(true);
}






#endif
