#include "main.h"


using namespace std;

int main()
{
    remove("intro_sort.txt");
    remove("merge_sort.txt");
    remove("quick_sort.txt");
	bool rosnaco = true;
	int ilosc_tablic=100;
    int *parametry = new int[3];

    cout << "Program rozpoczyna prace..."<<endl;

    for(int x=1;x<=3;x++)
        for(int y=1;y<=8;y++)
            for(int z=1;z<=5;z++)
            {
                parametry[0]=x;
                parametry[1]=y;
                parametry[2]=z;
                if(!test_wydajnosci(parametry, ilosc_tablic,rosnaco))
                    return -1;
            }

    delete[] parametry;
    cout<<" Program zakonczyl prace"<<endl;
    system("PAUSE");

}







