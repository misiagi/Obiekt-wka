#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <math.h>

using namespace std;

class Node{ //Węzeł
public:
        Node(int v_key):key(v_key){left=NULL; right=NULL; father=NULL; bf=0; };
        ~Node(){};
        
        
        Node *left, *right, *father;
        int key, bf;
};

class Tree{
public:
        Tree(){root=NULL; n=0;};
        ~Tree(){};
        Node *root;
                int n;

        int addNew(int);
        Node* Search(int);
        void Sort(int);
        void DispIn(Node*);
        void DispPre(Node*);
        Node * SearchMax(Node*);
        Node * SearchMin(Node*);
        Node * SearchPop(Node*);
        Node * SearchNas(Node*);
        void Del_p1(Node*);
        void Del_p2(Node*);
        void Del_p3(Node*);
		Node * Del_AVL(int);
        int Del(int);
        void RotR(Node*);
        void RotL(Node*);
		Node * RR(Node* );
		Node * LL(Node* );
		Node * RL(Node* );
		void LR(Node* );
        void getRoad(Node*);
        void setList(void);
        int getPar(int);
        void DSW();
};

int Tree::addNew(int v_key){

	if(root == NULL ){
		Node* n = new Node(v_key);
		root = n;
	}else {
		Node * tmp = root;
		Node * tmp_p = NULL;

		while(tmp) {
			if(tmp->key == v_key) return 0;
			tmp_p=tmp;
			if(v_key < tmp->key) tmp=tmp->left; else tmp=tmp->right;
		}
		Node *n = new Node(v_key);
		n->father=tmp_p;
		if(v_key < tmp_p->key) tmp_p->left=n; else tmp_p->right=n;

		if(tmp_p->bf){
			tmp_p->bf=0;
			return 1;
		}

		if(tmp_p->left == n) tmp_p->bf=1; else tmp_p->bf=-1;

		Node * tmp_p_f=tmp_p->father;
		tmp=tmp_p;

		while (tmp_p_f && !tmp_p_f->bf) {
			if(tmp_p_f->left == tmp) tmp_p_f->bf=1; else tmp_p_f->bf=-1;
			tmp=tmp_p_f;
			tmp_p_f=tmp_p_f->father;
		}

		if(tmp_p_f == NULL) return 1;

		if(tmp_p_f->bf == 1){
			if(tmp_p_f->right == tmp){
				tmp_p_f->bf=0;
				return 1;
			}
			if(tmp->bf == 1) LL(tmp_p_f); else LR(tmp_p_f);
			return 1;
		}else {
			if(tmp_p_f->left == tmp) {
				tmp_p_f->bf=0;
				return 1;
			}
			if(tmp->bf == -1) RR(tmp_p_f); else RL(tmp_p_f);
			return 1;
		}

	}
	n+=1;
};

Node* Tree::Search(int v_key){
        

        Node* now=root;
        if(root!=NULL){ //Lista pusta
                while(v_key!=now->key){ //Dopuki klucze nie są równe
                        if(v_key>now->key && now->right!=NULL){
                                now=now->right; //Idziemy w prawo
                        }else if(v_key<now->key && now->left!=NULL){
                                now=now->left; //Idziemy w lewo
                        }else return NULL; //Nie ma elementu
                }
                return now; //Znaleziony element
        }else return NULL;
        
};

void Tree::DispIn(Node* root){

        if(root){
        if (root->left!=NULL) {DispIn(root->left);};
        cout<<endl;
        cout<<root->key<<" ";
        if(root->left!=NULL)cout<<"Lewy: "<<root->left->key<<" ";
        if(root->right!=NULL)cout<<"Prawy: "<<root->right->key<<" ";
		cout<<"BF: "<<root->bf;
        //if(root->father!=NULL)cout<<"Tata: "<<root->father->key<<" ";
       if(root->right!=NULL) {DispIn(root->right);}; 
                cout<<endl;
        }
};

void Tree::DispPre(Node* root){

        if(root){
                cout<<root->key<<" ";
        if (root->left!=NULL) {DispPre(root->left);};
        if(root->right!=NULL) {DispPre(root->right);};
        }
};

void Tree::Sort(int ilosc){

        srand ((unsigned) time(NULL));
        int liczba=rand();
        int liczba_p=rand();
        liczba=liczba*liczba_p;

        while (ilosc!=0){
                if (!(Search(liczba)))
                {
                        addNew(liczba);
                        ilosc--;
                }else {liczba=rand(); liczba_p=rand(); liczba=liczba*liczba_p;};
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
        
        wezel->key=zamiennik->key;
        if((zamiennik->left==NULL) && (zamiennik->right==NULL)) Del_p1(zamiennik); else Del_p2(zamiennik);
        

};

int Tree::Del(int v_key){
        if (Search(v_key)){ // Sprawdzanie czy obiekt istnieje
                Node* wezel=Search(v_key); //wezel to ten usuwany

                if ((wezel->left==NULL) && (wezel->right==NULL)) Del_p1(wezel); else //Usuwanie liścia
                if (((wezel->left==NULL) && (wezel->right!=NULL)) || ((wezel->left!=NULL) && (wezel->right==NULL))) Del_p2(wezel); else Del_p3(wezel); //Dwóch potomków

                                n-=1;
                return 1;
        }return 0; // nie istnieje obiekt
};

Node *  Tree::Del_AVL(int v_key){

	Node * node = Search(v_key), *prev, * tmp, *tmp_2;	// wezel usuwany
	bool nest;

	if(node->left && node->right) {					// wezel posiada dwoje dzieci
		Node * prev=Del_AVL(SearchPop(node)->key);	// usuwamy rekurencyjnie poprzednik i dodajemy go w miejsce usuwanego wezla
		nest=false;
	}else {
		if(node->left){
			prev = node->left; node->left = NULL;
		}else {
			prev = node->right; node->right = NULL;
		}
		node->bf = 0;
		nest = true;
	}

	if(prev){
		prev->father=node->father;
		if(prev->left = node->left) prev->left->father=prev;   //jesli node->left istnieje to prev->left=node->left i staje sie ojcem
		if(prev->right = node->right) prev->right->father=prev;
		prev->bf = node->bf;
	}

	if(node->father){
		if(node->father->left == node ) node->father->left = prev; else node->father->right = prev;
	}else root = prev;

	if(nest)
	{
		tmp=prev;
		prev=node->father;
		while(prev)
		{
			if(!(prev->bf)){
				//PRZYPADEK 1 ----------------------- bf = 0 wiec nic nam to nie zmienia

				//prev->bf= (prev->left == tmp) ? -1 : 1;
				if(prev->left == tmp) prev->bf=-1; else prev->bf=1;
				break;
			}else {
				if(((prev->bf == 1) && (prev->left == tmp)) || ((prev->bf == -1) && prev->right == tmp)){

					//PRZYPADEK 2 -------------------------- skrócilismy ciezsze poddrzewo
					prev->bf=0;
					tmp=prev;					//obecny wezeł
					prev=prev->father;			//rodzic wezła prev
				}else{
					if(prev->left == tmp) tmp_2=prev->right; else tmp_2=prev->left;
					if(!(tmp_2->bf)){
						//PRZYPADEK 3----------------------------------- skrócone zpostalo lzejsze poddrzewo
						//A--------------------------------------------

						if(prev->bf == 1) LL(prev); else RR(prev);
						break;
					}else if(prev->bf == tmp_2->bf){

						//B--------------------------------------------
						//skróciliśmy ciezsze poddrzewo ale kontynujuemy bo całe drzewo zmniejszyło wysokosc

						if(prev->bf == 1) LL(prev); else RR(prev);
						tmp=tmp_2; prev=tmp_2->father;
					}else {
						//C------------------------------------------

						if(prev->bf == 1) LR(prev); else RL(prev);
						tmp=prev->father;
						prev=tmp->father;

					}
				}
			}
		}
	}

	return node;
};

void Tree::RotR(Node* wezel){
        
        if(wezel->father != NULL){
                Node* father=wezel->father;
                Node* gfather=father->father;

                if(father->left==wezel){
                        if(gfather!=NULL){
                                if(gfather->right==father)gfather->right=wezel;//1
                                if(gfather->left==father)gfather->left=wezel;//1
                        wezel->father=gfather; //2
                        }else{ root=wezel; root->father=NULL;}
                        
                        Node* tmp=wezel->right; // bufor na prawe dziecko wezla

                        wezel->right=father; //3
                        father->father=wezel; //4
                        if(wezel->left==NULL)father->left=NULL;


                        if (tmp!=NULL){
                        father->left=tmp; //5
                        tmp->father=father; //6
                        } else father->left=NULL;

                }
                
        }
};

void Tree::RotL(Node* wezel){
        
        if(wezel->father != NULL){
                Node* father=wezel->father;
                Node* gfather=father->father;

                if(father->right==wezel){
                        if(gfather!=NULL){
                        if(gfather->right==father)gfather->right=wezel;//1
                                if(gfather->left==father)gfather->left=wezel;//1 //1
                        wezel->father=gfather; //2
                        }else{ root=wezel; root->father=NULL;}
                        
                        Node* tmp=wezel->left; // bufor na prawe dziecko wezla

                        wezel->left=father; //3
                        father->father=wezel; //4
                        if(wezel->right==NULL)father->right=NULL;

                        if (tmp!=NULL){
                        father->right=tmp; //5
                        tmp->father=father; //6
                        } else father->right=NULL;

                }
                
        }
};

void Tree::getRoad(Node* wezel){

        /*while(wezel!=NULL){
cout<<wezel->key<<" \\";
wezel=wezel->father;
};*/
        cout<<"Key: "<<wezel->key<<" ";
        if(wezel->left!=NULL)cout<<"Lewy: "<<wezel->left->key<<" ";
        if(wezel->right!=NULL)cout<<"Prawy: "<<wezel->right->key<<" ";
        if(wezel->father!=NULL)cout<<"Tata: "<<wezel->father->key<<" ";
        cout<<endl;
};

void Tree::setList(void){
        
        Node* tmp=root;
        while (tmp!=NULL){
                if (tmp->left!=NULL){
                        RotR(tmp->left);
                        tmp=tmp->father;
                        //cout<<"Rotacja "<<tmp->key<<" ";
                        //getchar();
                } else tmp=tmp->right;
        }
};

int Tree::getPar(int n){
        int m;
                m=pow(2.0,(int)(log((double)n)/log(2.0)))-1;
        return(m);
};

void Tree::DSW(){

        if(root!=NULL){

                setList();
        int m=getPar(n);
                Node* tmp = root->right;
                for( int i=0; i<n-m; i++){
                        if(tmp->right){
                                RotL(tmp);
                                tmp=tmp->right->right;
                        }
                }

                while (m>1){
                        m=m/2;
                        tmp = root->right;
                        for(int i=0;i<m; i++){
                                RotL(tmp);

                                tmp=tmp->right->right;

                        }
                }
                cout<<"Drzewo wyważone :)"<<endl;
        }
        
};

Node * Tree::RR(Node* A){

	Node* B = A->right;
	Node* P = A->father;
	A->right = B->left;
	if(A->right) A->right->father=A;
	B->left=A;
	B->father=P;
	A->father=B;
	if(P){
		if(P->left == A) P->left=B; else P->right=B;
	}else root=B; 

	if(B->bf == -1){
		A->bf=B->bf=0;
	}else {A->bf=-1; B->bf=1;}

	return B;
};

Node * Tree::LL(Node* A){

	Node* B = A->left;
	Node* P = A->father;
	A->left = B->right;
	if(A->left) A->left->father=A;
	B->right=A;
	B->father=P;
	A->father=B;
	if(P){
		if(P->left == A) P->left=B; else P->right=B;
	}else root=B; 

	if(B->bf == 1){
		A->bf=B->bf=0;
	}else {A->bf=1; B->bf=-1;}

	return B;
};

Node * Tree::RL(Node* A){

	Node* B=A->right;
	Node* C=B->left;
	Node* P=A->father;

	B->left=C->right;
	if(B->left) B->left->father=B;
	A->right=C->left;
	if(A->right) A->right->father=A;
	C->left=A;
	C->right=B;
	A->father=B->father=C;
	C->father=P;
	if(P){
		if(P->left == A) P->left=C; else P->right=C;
	}else root=C;

	if(C->bf == -1) A->bf=1; else A->bf=0;
	if(C->bf == 1) B->bf=-1; else B->bf=0;
	C->bf=0;

	return C;
};

void Tree::LR(Node* node){

	Node* L = node->left;
	Node* LR = L->right;
	Node* parent = node->father;

	L->right=LR->left;
	if(L->right != NULL) L->right->left=L;
	node->left=LR->right;
	if(node->left != NULL) node->left->father=node;
	LR->right=node;
	LR->left=L;
	node->father=LR;
	L->father=LR;
	LR->father=parent;
	if(parent){
		if(parent->left == node) parent->left=LR; else parent->right=LR;
	}else root=LR;

	if(LR->bf == 1) node->bf=-1; else node->bf=0;
	if(LR->bf == -1) L->bf=1; else L->bf=0;
	LR->bf=0;

};


int _tmain(int argc, _TCHAR* argv[])
{
        Tree t1;
        cout<<t1.addNew(7);
        cout<<t1.addNew(4);
        cout<<t1.addNew(15);
        cout<<t1.addNew(1);
        cout<<t1.addNew(6);
        cout<<t1.addNew(30);
        cout<<t1.addNew(8);
        cout<<t1.addNew(12);
        //cout<<t1.addNew(9);
		t1.Del_AVL(30);
		//t1.Del_AVL(3);
		//t1.Del_AVL(9);
                //cout<<t1.addNew(180);
                //cout<<t1.addNew(20);
                
                //t1.DispPre(root);
                                cout<<endl;
                t1.DispIn(t1.root);
                cout<<endl;


              //  t1.Sort(100);
               // t1.DSW();
				cout<<"Działa";
                //t1.DispIn(t1.root);
                

        getchar();
        return 0;
}
