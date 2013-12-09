#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <math.h>

using namespace std;

class Node{ //Węzeł
public:
        Node(int v_key):key(v_key){left=NULL; right=NULL; father=NULL; };
        ~Node(){};
        
        
        Node *left, *right, *father;
        int key;
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
        int Del(int);
                void RotR(Node*);
                void RotL(Node*);
                void getRoad(Node*);
                void setList(void);
                int getPar(int);
                void DSW();
};

int Tree::addNew(int v_key){
        Node* now=root;
        bool adder=false;

        if(Search(v_key) == NULL){ //Funckja Search nie znalazła elementu czyli można dodać go do drzewa
                if(root == NULL){ //Tworzenie roota jak nie ma żadnego elementu
                        Node *tmp = new Node(v_key);
                        root=tmp;
                        adder=true;
                }else while (adder==false){ //Pętla kończona returnem
                        if(v_key>now->key){ // jesli v_key wiekszy od istniejacego to idziemy w prawo
                                if(now->right==NULL){ // jesli dotarlismy na koniec dodajemy wezel
                                        Node *tmp=new Node(v_key);
                                        now->right=tmp;
                                        now->right->father=now;
                                        adder=true;
                                }else now=now->right; // jak nie dotarlismy na koniec to lecimy dalej :)
                        }else // jak nie w prawo to w

                        if(v_key<now->key){ // lewo
                                if(now->left==NULL){ //jesli dotarlismy na koniec dodajemy wezel
                                        Node *tmp=new Node(v_key);
                                        now->left=tmp;
                                        now->left->father=now;
                                        adder=true;
                                }else now=now->left; //jak nie to lecim dalej :)
                        };
                }
                                n+=1;
        } if (adder) return 1; else return 0; // gdy dodano to 1 gdy nie to 0
        

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

void Tree::RotR(Node* wezel){
        
        if(wezel->father != NULL){
                Node* father=wezel->father;
                Node* gfather=father->father;

                if(father->left==wezel){
                        if(gfather!=NULL){
                                if(gfather->right==father)gfather->right=wezel;//1
                                if(gfather->left==father)gfather->left=wezel;//1
                        wezel->father=gfather;                                //2
                        }else{ root=wezel; root->father=NULL;}
                        
                        Node* tmp=wezel->right;                        // bufor na prawe dziecko wezla

                        wezel->right=father;                        //3
                        father->father=wezel;                        //4
                        if(wezel->left==NULL)father->left=NULL;


                        if (tmp!=NULL){
                        father->left=tmp;                                //5
                        tmp->father=father;                                //6
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
                                if(gfather->left==father)gfather->left=wezel;//1                                //1
                        wezel->father=gfather;                                //2
                        }else{ root=wezel; root->father=NULL;}
                        
                        Node* tmp=wezel->left;                        // bufor na prawe dziecko wezla

                        wezel->left=father;                        //3
                        father->father=wezel;                        //4
                        if(wezel->right==NULL)father->right=NULL;

                        if (tmp!=NULL){
                        father->right=tmp;                                //5
                        tmp->father=father;                                //6
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
        int         m=getPar(n);
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


int _tmain(int argc, _TCHAR* argv[])
{
        Tree t1;
        cout<<t1.addNew(120);
        cout<<t1.addNew(30);
        cout<<t1.addNew(160);
        cout<<t1.addNew(100);
        cout<<t1.addNew(130);
        cout<<t1.addNew(50);
        cout<<t1.addNew(110);
        cout<<t1.addNew(150);
        cout<<t1.addNew(140);
		//cout<<t1.addNew(180);
		//cout<<t1.addNew(20);
                
                //t1.DispPre(root);
				cout<<endl;
                t1.DispIn(t1.root);
                cout<<endl;

                //t1.Sort(100000);
                t1.DSW();
                t1.DispIn(t1.root);
		

        getchar();
        return 0;
}
