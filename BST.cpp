#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;

class Node{		//Węzeł
public:
	Node(int v_key):key(v_key){left=NULL; right=NULL; father=NULL; };
	~Node(){};
	
	
	Node *left, *right, *father;
	int key;
};

class Tree{
public:
	Tree(){root=NULL;};
	~Tree(){};
	Node *root;

	int addNew(int);
	Node* Search(int);
	void Sort(int);
	void Disp(Node*);
};

int Tree::addNew(int v_key){
	Node* now=root;

	if(Search(v_key) == NULL){							//Funckja Search nie znalazła elementu czyli można dodać go do drzewa
		if(root == NULL){														//Tworzenie roota jak nie ma żadnego elementu
			Node *tmp = new Node(v_key);
			root=tmp;
		}else for(;;){									//Pętla kończona returnem
			if(v_key>now->key){							// jesli v_key wiekszy od istniejacego to idziemy w prawo
				if(now->right==NULL){					// jesli dotarlismy na koniec dodajemy wezel
					Node *tmp=new Node(v_key);
					now->right=tmp;
					now->right->father=now;
					return 1;
				}else now=now->right;					// jak nie dotarlismy na koniec to lecimy dalej :)
			}else										// jak nie w prawo to w 

			if(v_key<now->key){							// lewo
				if(now->left==NULL){					//jesli dotarlismy na koniec dodajemy wezel
					Node *tmp=new Node(v_key);
					now->left=tmp;
					now->left->father=now;
					return 1;
				}else now=now->left;					//jak nie to lecim dalej :)
			};
		}	

	}else return 0;										//jak juz jest ten klucz to nie dodajemy
	return 1;																// Zwaraca 1 bo dodano roota
};

Node* Tree::Search(int v_key){
	

	Node* now=root;
	if(root!=NULL){																//Lista pusta
		while(v_key!=now->key){													//Dopuki klucze nie są równe
			if(v_key>now->key && now->right!=NULL){								
				now=now->right;													//Idziemy w prawo 
			}else if(v_key<now->key && now->left!=NULL){
				now=now->left;													//Idziemy w lewo
			}else return NULL;													//Nie ma elementu
		}
		return now;																//Znaleziony element		
	}else return NULL;
	
};

void Tree::Disp(Node* root){
	if(root)																//jesli istnieje korzeń
	{
		Disp(root->left);													// ogarniamy lewego potomka
		cout<<root->key<<" ";												// wypisujemy na ekran kluczyk
		Disp(root->right);													// i ogarniamy prawą mańkę
	};
};

void Tree::Sort(int ilosc){

	srand ((unsigned) time(NULL));
	int liczba=rand()%30000;
	while (ilosc!=0){
		if (!(Search(liczba)))
		{
			addNew(liczba);
			ilosc--;
		}else liczba=rand()%30000;
	};
};

int _tmain(int argc, _TCHAR* argv[])
{
	Tree t1;
	cout<<t1.addNew(10);
	cout<<t1.addNew(6);
	cout<<t1.addNew(1);
	cout<<t1.addNew(7);
	cout<<t1.addNew(13);
	cout<<t1.addNew(7);
	cout<<t1.addNew(18);
	t1.Sort(100);
	cout<<"Koniec losowania";
	cout<<t1.addNew(24);
	t1.Disp(t1.root);

	getchar();
	return 0;
}
