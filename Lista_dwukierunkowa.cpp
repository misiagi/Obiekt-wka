// L_dwukier.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

struct wezel{
	wezel *next ,*prev;
	int key;
};

class slownik{
private:
	wezel *head;
	wezel *tail;

public:
	slownik();
	int addNew(int);
};

slownik::slownik(){
	head=new wezel;
	tail=new wezel;
	head->next=NULL;
	head->prev=NULL;
	tail->next=NULL;
	tail->prev=NULL;
};

int slownik::addNew(int v_key){

	if(head->next==NULL)					//PUSTA LISTA
	{
		head->next=new wezel;
		head->next->next=tail;
		head->next->prev=head;
		tail->prev=head->next;
		head->next->key=v_key;
		return 1;
	};
	
	wezel * now = head->next;
	for(;;)							//LISTA ISTNIEJE
	{
		if (now->key>=v_key)		//AKTUALNY KLUCZ WIEKSZY
		{
			if (now->key == v_key)   //KLUCZ ISTNIEJE
			return 0;
				
			now->prev->next=new wezel;				//tworzenie nowego wezła
			now->prev->next->prev=now->prev;		//poprzedni wskazuje na nowy
			now->prev->next->next=now;				//nowy wskazuje na aktualny
			now->prev=now->prev->next;				//aktualny wskazuje na nowy

			now->prev->key=v_key;
			return 1;
		}
		if (now->next == tail)						//AKTUALNY KLUCZ MNIEJSZY
		{
			now->next=new wezel;					//aktualny na nowy
			now->next->prev=now;					//nowy na aktualny
			tail->prev=now->next;					//ogon na nowy
			tail->prev->next=tail;					//nowy na ogon
			now->next->key=v_key;
			return 1;
		}

		now=now->next;								// Przesuwanie po liscie
	}
};

int _tmain(int argc, _TCHAR* argv[])
{

	slownik s1;
	s1.addNew(2);

	getchar();
}

