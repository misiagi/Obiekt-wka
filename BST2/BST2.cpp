// DrzewoBST2.cpp : Defines the entry point for the console application.
//

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
	Node * SearchMax(Node*);
	Node * SearchMin(Node*);
	Node * SearchPop(Node*);
	Node * SearchNas(Node*);
	void Del_p1(Node*);
	void Del_p2(Node*);
	void Del_p3(Node*);
	int Del(int);
};

int Tree::addNew(int v_key){
	Node* now=root;
	bool adder=false;

	if(Search(v_key) == NULL){							//Funckja Search nie znalazła elementu czyli można dodać go do drzewa
		if(root == NULL){														//Tworzenie roota jak nie ma żadnego elementu
			Node *tmp = new Node(v_key);
			root=tmp;
			adder=true;
		}else while (adder==false){									//Pętla kończona returnem
			if(v_key>now->key){							// jesli v_key wiekszy od istniejacego to idziemy w prawo
				if(now->right==NULL){					// jesli dotarlismy na koniec dodajemy wezel
					Node *tmp=new Node(v_key);
					now->right=tmp;
					now->right->father=now;
					adder=true;
				}else now=now->right;					// jak nie dotarlismy na koniec to lecimy dalej :)
			}else										// jak nie w prawo to w 

			if(v_key<now->key){							// lewo
				if(now->left==NULL){					//jesli dotarlismy na koniec dodajemy wezel
					Node *tmp=new Node(v_key);
					now->left=tmp;
					now->left->father=now;
					adder=true;
				}else now=now->left;					//jak nie to lecim dalej :)
			};
		}

	} if (adder)	return 1; else return 0;						// gdy dodano to 1 gdy nie to 0
	

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
	if (root->left!=NULL) {Disp(root->left);};
	cout<<root->key<<" ";
	if(root->right!=NULL) {Disp(root->right);};
};

void Tree::Sort(int ilosc){

	srand ((unsigned) time(NULL));
	int liczba=rand()%30000;
	int liczba_p=rand()%1000;
	liczba=liczba*liczba_p;

	while (ilosc!=0){
		if (!(Search(liczba)))
		{
			addNew(liczba);
			ilosc--;
		}else {liczba=rand()%30000; liczba_p=rand()%10000; liczba=liczba*liczba_p;};
	};
};

Node* Tree::SearchMax(Node * wezel){
	Node* max=wezel;
	while (wezel->right!=NULL){
		wezel=wezel->right;
	};
	return wezel;
	
};

Node* Tree::SearchMin(Node * wezel){
	Node* min=wezel;
	while (wezel->left!=NULL){
		wezel=wezel->left;
	};
	return wezel;
	
};

Node* Tree::SearchPop(Node* wezel){

	if(wezel->left) return SearchMax(wezel->left);

	Node * now=wezel;

	while (wezel && (wezel->right != now)){
		now=wezel;
		wezel=wezel->father;
	} return wezel;
};

Node* Tree::SearchNas(Node* wezel){

	if(wezel->right) return SearchMin(wezel->right);

	Node * now=wezel;

	while(wezel && (wezel->left != now)){
		now=wezel;
		wezel=wezel->father;
	} return wezel;
};

void Tree::Del_p1(Node* wezel){

		// Gdy nie ma potomków
			if(wezel==wezel->father->left) wezel->father->left=NULL;
			if(wezel==wezel->father->right) wezel->father->right=NULL;
			delete wezel;
		
};

void Tree::Del_p2(Node * wezel){

	if ((wezel->left==NULL) && (wezel->right!=NULL)){
			if(wezel==wezel->father->right){
				wezel->father->right=wezel->right;
				wezel->right->father=wezel->father;
				
			} else
			if (wezel==wezel->father->left){
				wezel->father->left=wezel->right;
				wezel->right->father=wezel->father;
				
			}
		} else
		if ((wezel->left!=NULL) && (wezel->right==NULL)){
			if(wezel==wezel->father->right){
				wezel->father->right=wezel->left;
				wezel->left->father=wezel->father;
			
			}else
			if(wezel==wezel->father->left){
				wezel->father->left=wezel->left;
				wezel->left->father=wezel->father;
				
			}
		}
		delete wezel;

}

void Tree::Del_p3(Node * wezel){

	Node* zamiennik;
	int los=rand()%2;
	los=0;
	if (los) zamiennik=SearchPop(wezel); else zamiennik=SearchNas(wezel);

	/*Node * tmp=zamiennik;
	
	if((tmp->left==NULL) && (tmp->right==NULL)) Del_p1(tmp); else Del_p2(tmp);
	if(wezel->father->left==wezel) wezel->father->left=zamiennik; else wezel->father->right=zamiennik;
	zamiennik->father=wezel->father;
	if(wezel->left!=zamiennik) {zamiennik->left=wezel->left; zamiennik->left->father=zamiennik;} else zamiennik->left=NULL;
	if(wezel->right!=zamiennik) {zamiennik->right=wezel->right; zamiennik->right->father=zamiennik;} else zamiennik->right=NULL; 
	
	//Del_p1(tmp);
	delete wezel;*/
	
	wezel->key=zamiennik->key;
	if((zamiennik->left==NULL) && (zamiennik->right==NULL)) Del_p1(zamiennik); else Del_p2(zamiennik);
	

};

int Tree::Del(int v_key){
	if (Search(v_key)){						// Sprawdzanie czy obiekt istnieje
		Node* wezel=Search(v_key);				//wezel to ten usuwany

		if ((wezel->left==NULL) && (wezel->right==NULL)) Del_p1(wezel); else 														//Usuwanie liścia
		if (((wezel->left==NULL) && (wezel->right!=NULL)) || ((wezel->left!=NULL) && (wezel->right==NULL))) Del_p2(wezel); else Del_p3(wezel);															//Dwóch potomków


		return 1;
	}return 0;								// nie istnieje obiekt 
};



int _tmain(int argc, _TCHAR* argv[])
{
	Tree t1;
	cout<<t1.addNew(10);
	cout<<t1.addNew(6);
	cout<<t1.addNew(1);
	cout<<t1.addNew(7);
	cout<<t1.addNew(13);
	cout<<t1.addNew(12);
	cout<<t1.addNew(7);
	cout<<t1.addNew(18);
	cout<<"            "<<t1.Search(9)<<"              ";
	//t1.Sort(100000);
	//cout<<"Koniec losowania";
	cout<<t1.addNew(24)<<endl;
	cout<<t1.Search(24)<<endl;
	//t1.Disp(t1.root);
	//cout<<t1.SearchMax(t1.root)->key<<endl;

//	cout<<t1.Search(1)->key<<endl;
	//t1.Disp(t1.root);
	//cout<<t1.SearchMin(t1.root)->key<<endl;;
	//cout<<t1.SearchPop(t1.Search(18))->key<<endl;;
	//cout<<t1.SearchNas(t1.Search(13))->key<<endl;;
	//t1.Del_p2(t1.Search(18));
	cout<<t1.Del(6)<<endl;
	//cout<<t1.Search(7)->key<<endl;
	//cout<<t1.Search(7)->right<<endl;
	t1.Disp(t1.root);

	getchar();
	return 0;
}
