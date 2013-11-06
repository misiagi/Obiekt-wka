// ConsoleApplication4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

class Matrix{
public:
	Matrix(int, int);
	~Matrix(){};
	void showMatrix();
	void changeCell();
	string getCell();


private:
	double ** matrix;
	int w;
	int k;

};

Matrix::Matrix(int _w, int _k){
	w=_w;
	k=_k;

	matrix = new double*[w];
	for (int i = 0; i < w; i++) {
	matrix[i] = new double[k];
	};

	for (int i = 0; i < w; i++) {
		for (int r = 0; r < k; r++) {
			matrix[i][r]=0;
		};
	};
};

void Matrix::showMatrix(){
	for (int i = 0; i < w; i++) {
		for (int r = 0; r < k; r++) {
			cout<< matrix[i][r];
		};
		cout<<endl;
	};
};

void Matrix::changeCell(){
	
	int _w,_k,value;
	cout<<"Podaj kolumne aby zmienić: ";
	cin>>_w;
	cout<<"Podaj wiersz aby zmienić: ";
	cin>>_k;
	cout<<"Podaj wartosc: ";
	cin>>value;


	matrix[_w-1][_k-1]=value;

};

string Matrix::getCell(){
	
	int _w,_k,value;
	stringstream ss;


	cout<<"Podaj kolumne: ";
	cin>>_w;
	cout<<"Podaj wiersz: ";
	cin>>_k;

	ss<<matrix[_w-1][_k-1];
	return(ss.str());
};


int _tmain(int argc, _TCHAR* argv[])
{
	int _w=3,_k=3;
	Matrix m1(_w,_k);
	m1.showMatrix();

	cout<< endl;

	m1.changeCell();
	m1.showMatrix();
	cout<<endl;
	cout<<m1.getCell();


	getchar();
	getchar();
}

