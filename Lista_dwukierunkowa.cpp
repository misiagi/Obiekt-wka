// L_dwukier.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>

using namespace std;

struct wezel{
	wezel *next ,*prev;
	int key;
};

class Lista{
private:
	wezel *head;
	wezel *tail;

public:
	Lista();
	int addNew(int);
	void addLos(int);
	int Search(int);
	int Del(int);
	void Display();
};

Lista::Lista(){
	head=new wezel;
	tail=new wezel;
	head->next=NULL;
	head->prev=NULL;
	tail->next=NULL;
	tail->prev=NULL;
};

int Lista::addNew(int v_key){

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

void Lista::addLos(int ilosc){
	
	time_t t;
	srand((unsigned)time(&t));
	int v_key;

	for(;;){
		if(ilosc==0) return;
		else
		{
			v_key=(rand()%(10+ilosc));
				if(addNew(v_key)==1) ilosc--;
		};
	};
};

int Lista::Search(int v_key){
	if (head->next == tail)
		{cout<<"Lista jest pusta"; return 0;} //PUSTA LISTA
	wezel * now=head->next;
	for(;;){
		if(now->key == v_key) return 1;			// ZNALEZIONO KLUCZ
		if(now->key > v_key)  return 0;			// LISTA POSORTOWANA WIEC JUZ NIE BEDZIE
		if(now->next == tail)  return 0;			// KONIEC LISTY

		now=now->next;
	};
};

int Lista::Del(int v_key){

	if (head->next == tail)
		{cout<<"Lista jest pusta"; return 0;} //PUSTA LISTA
	wezel * now=head->next;
	for(;;){
		if(now->key == v_key)
		{
			now->prev->next=now->next;		// poprzedni na nastepny
			now->next->prev=now->prev;		// nastepny na poprzedni
			delete now;
			return 1;
		};
		if(now->key > v_key) return 0;		// Brak elementu
		if(now->next == tail) return 0;		// KONIEC LISTY

		now=now->next;
	};
};

void Lista::Display(){

	if(head->next == tail)
	{
		cout<<"Lista jest pusta";	return;
	};
	wezel * now=head->next;

	for(;;){
		cout<<now->key<<" ";
		if(now->next == tail) {cout<<endl; return;}
		now=now->next;
	};
};

int _tmain(int argc, _TCHAR* argv[])
{
	Lista s1;
	s1.addLos(5);
	s1.Display();
	s1.addNew(2);
	s1.Display();
	s1.Del(2);
	s1.Display();
	s1.Del(2);
	s1.Display();
	s1.addLos(3);
	s1.Display();

	getchar();
}

