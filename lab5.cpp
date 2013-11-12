// Lab5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <ostream>
#include <istream>
#include <fstream>

using namespace std;

class Matrix{
public:
        Matrix(int, int);
        ~Matrix(){};
        void showMatrix();
        void changeCell(int, int, int);
        string getCell(int, int);
		string getLine(int);
		string getColumn(int);
		string getMatrix();
		void addValue(int);
		void makeTrans();
		void Save(string);
		Matrix(string);


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

void Matrix::changeCell(int _w, int _k, int value){
        
        matrix[_w-1][_k-1]=value;

};

string Matrix::getCell(int _w, int _k){
        
        stringstream ss;

        ss<<matrix[_w-1][_k-1];
        return(ss.str());
};

string Matrix::getLine(int _w){

	stringstream ss;
	
	for(int i=0;i<k;i++){

		ss<<matrix[_w-1][i];
	};
	return(ss.str());
};

string Matrix::getColumn(int _k){
	stringstream ss;
	
	for(int i=0;i<w;i++){
		ss<<matrix[i][_k-1];
	};
	return(ss.str());
};

string Matrix::getMatrix(){
	
	stringstream ss;

	for(int i=0;i<w;i++){
		ss<<getLine(i+1)<<endl;
	};
	return(ss.str());
};

void Matrix::addValue(int value){

	for (int i = 0; i < w; i++) {
                for (int r = 0; r < k; r++) {
                        matrix[i][r]+=value;
                };
        };
};

void Matrix::makeTrans(){

	int buf=w;
	w=k;
	k=buf;
	

		double **trans = new double*[w];
        for (int i = 0; i < w; i++) {
        trans[i] = new double[k];
        };

		for(int i=0;i<w;i++){
			for(int r=0;r<k;r++){
				trans[i][r]=matrix[r][i];
			};
		};
		 delete[] matrix;

		 matrix=trans;

};

void Matrix::Save(string file){

	ofstream outputFile(file);
	if (!outputFile.is_open())
	throw std::exception("Brak pliku");

	outputFile<<w<<";"<<k<<";"<<endl;
	for(int r=0;r<w;r++){
	for(int i=0;i<k;i++){outputFile<<matrix[r][i]<<";";}
	outputFile<<endl;
	};

	outputFile.close();

};

Matrix::Matrix(string file){

	ifstream inputFile(file);
	if (!inputFile.is_open())
	throw std::exception("Brak pliku dane.txt");

	string line="";
	inputFile>>line;

	string bufor[2];						// bufor do odczytu rozmiarów
	int licz=0;
	for(int i=0;i<line.length();i++){ if(line[i]!=';') bufor[licz]+=line[i]; else licz++;}

	istringstream ss_w(bufor[0]);
	ss_w>>w;
	istringstream ss_k(bufor[1]);
	ss_k>>k;

	//istringstream ss_v;

							// bufor do przechowywyania wiersza

	
	 matrix = new double*[w];
        for (int i = 0; i < w; i++) {
        matrix[i] = new double[k];
        };


	licz=0;
	for(int i=0;i<w;i++){
		line="";
		inputFile>>line;
		licz=0;
		string *bufor_v=new string[k];


		for(int r=0;r<line.length();r++){ if(line[r]!=';')bufor_v[licz]+=line[r]; else licz++;}

		for(int l=0;l<k;l++){
			
			istringstream ss(bufor_v[l]);
			ss>>matrix[i][l];
			};
		};
	

	inputFile.close();
};



int _tmain(int argc, _TCHAR* argv[])
{
     
	Matrix m1("macierz.txt");		//wczytanie macierzy 4x3
	m1.showMatrix();
	cout<<endl;
	cout<<endl;

	m1.changeCell(2,2,3);			// zmiana wartosci macierzy
	m1.changeCell(4,1,8);

	m1.showMatrix();
	cout<<endl;
	cout<<endl;

	m1.Save("macierz1.txt");	//zapis macierzy do pliku

	Matrix m2("macierz1.txt");	// nowa macierz z pliku
	m2.showMatrix();
	cout<<endl;
	cout<<endl;

	m2.makeTrans();				// macierz transponowana
	m2.showMatrix();
	cout<<endl;
	cout<<endl;

	m2.Save("macierz2.txt");	// zapis macierzy do pliku

	Matrix m3("macierz2.txt");	// noqa macierz z pliku
	m3.showMatrix();
	cout<<endl;
	cout<<endl;

	m3.addValue(1);				//dodanie wartosci do elementow macierzy
	m3.showMatrix();
	cout<<endl;
	cout<<endl;

	m3.Save("macierz3.txt");	//zapis macierzy do pliku

        getchar();
        getchar();
}
