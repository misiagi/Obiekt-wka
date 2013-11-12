// Lab_2_lis.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class wezel{
public:
	wezel(int v_key):key(v_key){next=NULL; prev=NULL;};
	wezel *next, *prev;
	int key;
};

class Lista{
public:
	Lista(){head=NULL; tail=NULL;};
	wezel *head, *tail;
	int addNew(int);
	void Disp();
	wezel * Search(int);
	int Del(int);
	void Los(int);
};

int Lista::addNew(int v_key){
	if(Search(v_key)==NULL){
		if (head == NULL)					//PUSTA LISTA
		{
			wezel* tmp = new wezel(v_key);
			head=tmp;
			tail=head;
		}else 
		{
			if(head->key>v_key){			// Key wstawianego mniejszy od istniejacego
				wezel * tmp=new wezel(v_key);
				head->prev=tmp;
				tmp->next=head;
				head=tmp;
			}else
			{
				if(tail->key<v_key){		//Key wiekszy 
					wezel * tmp=new wezel(v_key);
					tail->next=tmp;
					tmp->prev=tail;
					tail=tmp;
				}else
				{
					wezel * now=head;
					wezel * tmp=new wezel(v_key);

					while (!(now->key<v_key && now->next->key>v_key)){		
						now=now->next;
					};

					tmp->prev=now;
					tmp->next=now->next;
					now->next=tmp;
					now->next->prev=tmp;

				};
			};
		};
	}else return 0;
	return 1;

};

void Lista::Disp(){

	wezel * now=tail;

	while(now != NULL){
		cout<<now->key<<" "<<now->prev << " ";
		now=now->prev;
	};

};

wezel * Lista::Search(int v_key){
	wezel * now=head;


	while (now!=NULL){
		if(now->key == v_key) return now;
		now=now->next;
	};

	return NULL;
};

int Lista::Del(int v_key){

	wezel *now=Search(v_key);
	if(now!=NULL) {
		if(now==tail) {
			tail=now->prev;
			tail->next=NULL;
		}else if(now==head){
			head=now->next;
			head->prev=NULL;
		}else {

			wezel * prawy=now->next, * lewy=now->prev;
			prawy->prev=lewy;
			lewy->next=prawy;
	

		};
		delete now;
	}else return 0;
	return 1;
};

void Lista::Los(int licz){

};

int _tmain(int argc, _TCHAR* argv[])
{

	Lista s1;

	s1.addNew(3);
	s1.addNew(4);
	s1.addNew(2);
	s1.addNew(5);
	s1.addNew(1);

	wezel * w1=s1.Search(3);
	//cout<<w1->key<<endl;
	s1.Disp();

	s1.Del(2);
	//s1.Del(5);
	cout << endl << s1.head->key << " " << s1.tail->key << " " << endl;
	s1.Disp();

	getchar();



	return 0;

}

