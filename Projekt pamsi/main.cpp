
#include "main.h"
#include "Sortowanko.h"

using namespace std;



int main()
{
	int rozmiar;
	bool rosnaco = true;
	int tryb;
    cout << "Hej, program sortuje sobie tablice, bo moze! !\n";
	cout << "Podaj wielkosc tablicy";
	cin >> rozmiar;
	cout<< "Jesli roznaco, podaj 1, jesli malejaco podaj  0";
	cin >> rosnaco;
	cout<< "Wybierz tryb sortowania: 1-merge sort, 2-quicksort";
	cin >> tryb;
	int *tablica = new int[rozmiar];
	srand(time(NULL));
	for (int i = 0; i < rozmiar; i++)
	{
		tablica[i] = rand();
	}
    chrono::high_resolution_clock::time_point t1;
    chrono::high_resolution_clock::time_point t2;

    if(tryb==1)
    {
        t1 = chrono::high_resolution_clock::now();
        Sortowanko::scalanie(tablica, 0, rozmiar - 1, rosnaco);
        t2 = chrono::high_resolution_clock::now();
    }
	else if(tryb==2)
    {
        t1 = chrono::high_resolution_clock::now();
        Sortowanko::quick_sort(tablica, 0, rozmiar - 1, rosnaco);
        t2 = chrono::high_resolution_clock::now();
    }
    else if(tryb==3)
    {
        t1 = chrono::high_resolution_clock::now();
        Sortowanko::quick_sort(tablica, 0, rozmiar - 1, rosnaco);
        t2 = chrono::high_resolution_clock::now();
    }
    cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << "ms";
    if(test_posortowania(tablica, rozmiar, rosnaco))
        cout<<"Tablica posortowana poprawnie"<<endl;
    else
        cout<<"Blad sortowania"<<endl;



    delete(tablica);
    system("PAUSE");
}

