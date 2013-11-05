// Lab4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <istream>

using namespace std;

class Room{
public:
        Room(){visit = false;};
        ~Room(){delete n; delete s; delete e; delete w; };
        void setDescription(string _description){ description=_description; };
		void getDescription();
        void setwskN(Room* _n){n=_n;};
        void setwskS(Room* _s){s=_s;};
        void setwskE(Room* _e){e=_e;};
        void setwskW(Room* _w){w=_w;};
		Room* getwskN(){return n;};
		Room* getwskS(){return s;};
		Room* getwskE(){return e;};
		Room* getwskW(){return w;};
		void setVisit();
		bool getVisit();

private:
		string description;
		bool visit;
		Room* n;
        Room* s;
        Room* e;
        Room* w;
};


void showTab(Room*** tab);
void step(Room*** tab, char road[]);

int _tmain(int argc, _TCHAR* argv[])
{
	string description="opis";

        Room *** tab=new Room**[3];
        for(int i=0;i<3;i++){
                tab[i]=new Room*[3];
        };
              
		for(int i=0; i<3; i++){
			for(int k=0; k<3; k++){
				tab[i][k] = new Room;

				tab[i][k]->setDescription(description);
				if((k-1) < 0) tab[i][k]->setwskW(NULL);
					else tab[i][k]->setwskW(tab[i][k-1]);
				if((k+1) > 2) tab[i][k]->setwskE(NULL);
					else tab[i][k]->setwskE(tab[i][k+1]);
				if((i-1) < 0) tab[i][k]->setwskN(NULL);
					else tab[i][k]->setwskN(tab[i-1][k]);
				if((i+1) > 2) tab[i][k]->setwskS(NULL);
					else tab[i][k]->setwskS(tab[i+1][k]);
		}
	}
				

	showTab(tab);
	step(tab, "e e s s");
	cout << endl;
	showTab(tab);
	cout << endl;
	getchar();

	return 0;

}

//##########################################################################################################################################################

void Room::getDescription(){
	cout<<description;
};

void Room::setVisit(){
	if (visit==0) visit=1;
};

bool Room::getVisit(){

	return visit;
};

void showTab(Room*** tab){
	char tabF[5][5];

		for(int i=0;i<3;i++){
			for(int k=0;k<3;k++){
				
				if (tab[i][k]->getwskN()==NULL){
					tabF[i][k+1]='X';
					if (tab[i][k]->getwskW()==NULL) tabF[i][k]='X';
					if (tab[i][k]->getwskE()==NULL) tabF[i][k+2]='X';
				};


				if (tab[i][k]->getwskS()==NULL){
					tabF[i+2][k+1]='X';
					if (tab[i][k]->getwskW()==NULL) tabF[i+2][k]='X';
					if (tab[i][k]->getwskE()==NULL) tabF[i+2][k+2]='X';
				};


				if (tab[i][k]->getwskW()==NULL)	tabF[i+1][k]='X';
				if (tab[i][k]->getwskE()==NULL) tabF[i+1][k+2]='X';

				if(tab[i][k]->getVisit()==false) tabF[i+1][k+1] = '0';
					else tabF[i+1][k+1] ='1';

			};
		};

		for(int i=0; i<5; i++){
			for(int k=0; k<5; k++){
				cout << tabF[i][k];
		};
		cout << endl;
	};
};

void step(Room*** tab, char road[]){
	int w = 0;
	int k = 0;
	tab[w][k]->setVisit();
	int size = strlen(road);
	for(int i=0; i<size; i++){
		if(road[i] != ' '){
			switch(road[i]){
				case 'n': w-=1; break;
				case 'e': k+=1; break;
				case 's': w+=1; break;
				case 'w': k-=1; break;
			}
			tab[w][k]->setVisit();
		}
	}
}



