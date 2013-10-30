// Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <istream>

using namespace std;

class Room{
public:
	Room(){};
	~Room(){};
	//Room(string _description,bool _visit, Room* _n, Room*_s, Room* _e, Room* _w):description(_description), visit(_visit),n(_n),s(_s),e(_e),w(_w){};
	void setDescription(string _description){ description=_description; };
	void setwskN(Room* _n){n=_n;};
	void setwskS(Room* _s){s=_s;};
	void setwskE(Room* _e){e=_e;};
	void setwskW(Room* _w){w=_w;};

private:
	string description;
	bool visit;
	Room* n;
	Room* s;
	Room* e;
	Room* w;
};

int _tmain(int argc, _TCHAR* argv[])
{

	int size;
	string description;

	//TWORZENIE SIATKI

	cout<<"Rozmiar macierzy pokojow = ";
	cin>>size;

	Room *** tab=new Room**[size];
	for(int i=0;i<size;i++){
		tab[i]=new Room*[size];
	}
		for(int i=0;i<size;i++){
			for(int k=0;k<size;k++){
				tab[i][k]=new Room();
				cout<<"Opis pokoju nr. ["<<i+1<<"]["<<k+1<<"] = ";
				cin >> description;
				tab[i][k]->setDescription(description);
			}
		}

	// USTAWIANIE POKOI

		for(int i=0;i<size;i++){
			for(int k=0;k<size;k++){
				if ((k-1)<0)tab[i][k]->setwskW(NULL);
				if ((k+1)>size-1)tab[i][k]->setwskE(NULL);
				if ((i-1)<0)tab[i][k]->setwskN(NULL);
				if ((i+1)>0)tab[i][k]->setwskS(NULL);
			}
		}


	
}



