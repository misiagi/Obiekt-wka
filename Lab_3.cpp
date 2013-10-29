// Pliki_samochod.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "string"
#include "time.h"
#include "sstream"
#include <istream>
#include <fstream>
#include "iostream"
#include <ctime>

using namespace std;
int *f_tab();
class Student
{
public:
	Student(){};
	Student(int _nr, string _inicjaly, int *_oceny):nr(_nr), inicjaly(_inicjaly), oceny(_oceny){};
	~Student(){};
	Student(Student&);
	string toString();
	string file_string ();


private:

	int nr;
	string inicjaly;
	int *oceny;
	
};

class Grupa
{

public: 
	Grupa(){};
	~Grupa(){};
	Grupa(string, int, int);
	void Dodaj(Student);
	string toString();
	Grupa(Grupa&);
	void file_read (string);
	void file_write (string);

private:
	string nazwa;
	int nr_gr;
	int l_student;
	Student* studenci;
	int indeks;
};

Grupa::Grupa(string _nazwa, int _nr_gr, int _l_student):nazwa(_nazwa), nr_gr(_nr_gr), l_student(_l_student)
{
	studenci=new Student[l_student];
	indeks=0;

};

void Grupa::file_read (string plik)
{
	ifstream inputFile(plik);
	if (!inputFile.is_open())
		throw std::exception("Brak pliku dane.txt");
	
		/*string lineAsString;
		while (!inputFile.eof())
		{
			inputFile>>lineAsString;
			cout<< lineAsString << endl;
		}*/

	string line;
	inputFile>>line;

	string bufor[3];
	int licz=0;
	
	for(int i=0;i<line.length();i++) if(line[i]!=';') bufor[licz]+=line[i]; else licz++; 

	nazwa=bufor[0];
	istringstream ss(bufor[1]);
	ss>>nr_gr;
	istringstream sss(bufor[2]);
	sss>>l_student;
	delete [] studenci;
	studenci = new Student[l_student];

	

	for(int j=0;j<l_student;j++)
	{	
		string bufor_s[12];
		licz=0;
		string lines="";
		inputFile>>lines;
		for(int i=0;i<lines.length();i++) if(lines[i]!=';') bufor_s[licz]+=lines[i]; else licz++; 
		
				istringstream s_ss(bufor_s[0]);
				int id_1;
				s_ss>>id_1;
				int *tablica_p=new int[10]; 
				for(int r=2;r<12;r++)
				{
					istringstream s_sss(bufor_s[r]);
					s_sss>>tablica_p[r-2];

				}

				Student tmp(id_1,bufor_s[1],tablica_p);
				Dodaj(tmp);
				
	}
	inputFile.close();
}

void Grupa::file_write (string plik)
{
	ofstream outputFile(plik);
	if (!outputFile.is_open())
	throw std::exception("Brak pliku dane.txt");

	outputFile<<nazwa<<";"<<nr_gr<<";"<<l_student<<";"<<endl;
	for(int i=0;i<l_student;i++)
	{
		outputFile<<studenci[i].file_string();
	
	}
	outputFile.close();

}

string Student::file_string ()
{
	
	stringstream ss;
	ss<<nr<<";"<<inicjaly<<";";
	for(int i=0;i<10;i++)
		ss<<oceny[i]<<";";
	ss<<endl;
	return ss.str();
}

void Grupa::Dodaj(Student student)
{
	if (indeks<l_student)
	studenci[indeks++]=student;

}

string Grupa::toString()
{
	stringstream ss;
	ss<<"Nazwa gr: "<<nazwa<<" Numer gr: "<<nr_gr<<endl;
	for(int i=0;i<l_student;i++)
	{
		ss<<studenci[i].toString()<<endl;
	
	}
	ss<<endl;
	return ss.str();
}

int * f_tab()
{
	int *tab=new int[10];
	srand(time(0));
	for(int i=0;i<10;i++)
		{
			tab[i]=(rand()%4)+2;
		}
	return tab;
};

int _tmain(int argc, _TCHAR* argv[])
{

	Student S1(1,"MS",f_tab());
	Student S2(S1);
	Student S3(3,"SS",f_tab());


	Grupa G1("210B",231,3);
	G1.Dodaj(S1);
	G1.Dodaj(S2);
	G1.Dodaj(S3);

	cout << G1.toString();

	Grupa G2(G1);
	cout<<G2.toString(); 

	//G1.file_write("dane.txt");

	Grupa G5("200",200,0);
	G5.file_read("dane.txt");
	cout<<G5.toString();


	getchar();

	return 0;
}

Grupa::Grupa(Grupa& src)
{
	nazwa=src.nazwa;
	nr_gr=src.nr_gr;
	l_student=src.l_student;
	indeks=0;
	studenci=new Student[l_student];

	for(int i=0;i<l_student;i++)
	{
		Student Bufor(src.studenci[i]);
		Dodaj(Bufor);
	}
	indeks=src.indeks;
}

Student::Student(Student& src)
{
	nr=src.nr;
	inicjaly=src.inicjaly;
	oceny=new int[10];

	for(int i=0;i<10;i++)
	{

		oceny[i]=src.oceny[i];

	}

}

string Student::toString()
{
	stringstream ss;
	ss<<"Numer: "<<nr<<" Inicjaly :"<<inicjaly<<" Oceny: ";
	for(int i=0;i<10;i++)
	{
		ss<<oceny[i]<<" ";
		
	}
	ss<<endl;
	return ss.str();
}
