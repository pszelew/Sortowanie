#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include<stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

template <class typ>
bool test_posortowania(typ *tablica, int rozmiar, bool rosnaco)
{
    if(rosnaco)
    {
        for(int i=0;i<rozmiar-1;i++)
        {
            if(tablica[i]>tablica[i+1])
                return false;
        }
    }
    else
    {
        for(int i=0;i<rozmiar-1;i++)
        {
            if(tablica[i]<tablica[i+1])
                return false;
        }
    }
    return true;
}



#endif
