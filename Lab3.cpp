// PoLab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <time.h>
#include <sstream>
#include <istream>
#include <fstream>
#include <ctime>

using namespace std;

class Student{
private:
	string initials;
	int nr_gr;
	int marks[10];

public:
	Student(){};
	Student(string, int, int*);
	Student(string);
	~Student(){};
	Student(Student&);
	string toString();

};

class Group{
private:
	string name_gr;
	int l_student;
	Student *studenci;
	int indeks;

public:
	Group(){indeks=0;};
	Group(string, int);
	void add(Student);
	string toString();
	void file_write(string);;
	void file_read(string);
	Group(Group&);

};


int *tab();
bool open=1;


int _tmain(int argc, _TCHAR* argv[])
{
	srand ((unsigned int)time(NULL));
	Student s1("Yogi",210,tab());
	Student s2("Tama",210,tab());
	Student s3("Biszkopt",211,tab());
	Student s4("Piotrek",211,tab());
	Student s5("Kazi",211,tab());

	Group g1("Grupa1",5);
	g1.add(s1);
	g1.add(s2);
	g1.add(s3);
	g1.add(s4);
	g1.add(s5);

	//cout<<g1.toString();

	Group g2;

	//g2.file_read("dane.txt");

	//g1.file_write("dane.txt");

	//cout<<g2.toString();

	g2.file_read("dane.txt");
	cout<<g2.toString();
	getchar();
}

//###################################################################################################################################

void Group::add(Student n_student){
	if(indeks<l_student) studenci[indeks++]=n_student;
	else cout<< "Za duzo studentow w grupie";
};

Group::Group(string _name_gr, int _l_student){
	name_gr=_name_gr;
	l_student=_l_student;
	studenci=new Student[l_student];
	indeks=0;

};

string Group::toString(){
	stringstream ss_group;
	ss_group<<name_gr<<";"<<l_student<<";"<<endl;
	for(int i=0;i<indeks;i++)
	{
		ss_group<<studenci[i].toString();
	};
	return(ss_group.str());
};

void Group::file_read(string file){
	ifstream inputFile(file);
	if(!inputFile.is_open())
		throw std::exception("Brak pliku!");

	string line;
	inputFile>>line;
	string bufor[2];
	int licz=0;

	for(int i=0;i<line.length();i++) {if (line[i]!=';') bufor[licz]+=line[i]; else licz++;}
	name_gr=bufor[0];
	istringstream s_l_student(bufor[1]);
	s_l_student>>l_student;

	//delete [] studenci;
	studenci = new Student[l_student];


	for(int j=0;j<l_student;j++)
	{


		string line="";
		inputFile>>line;

		
			Student* tmp=new Student (line);
			add(*tmp);
	};
	inputFile.close();
};


void Group::file_write(string file){

	ofstream outputFile(file);
	if (!outputFile.is_open())
		throw std::exception("Brak pliku!");

	outputFile<<name_gr<<";"<<l_student<<";"<<endl;
	for(int i=0;i<indeks;i++)
	{
		outputFile<<studenci[i].toString();
	};
	outputFile.close();
};

Group::Group(Group& src){
	
	name_gr=src.name_gr;
	l_student=src.l_student;
	indeks=0;
	studenci=new Student[l_student];

	for(int i=0;i<l_student;i++)
	{
		Student Bufor(src.studenci[i]);
		add(Bufor);
	};
	indeks=src.indeks;
};


//#######################################################################################################################################3

Student::Student(string line){

	string bufor_s[12];
	int licz=0;
	for(int i=0;i<line.length();i++) if (line[i]!=';') bufor_s[licz]+=line[i]; else licz++;
	initials=bufor_s[0];
	istringstream _nr_gr(bufor_s[1]);
	_nr_gr>>nr_gr;

		for(int k=2;k<12;k++)
		{
			istringstream _marks(bufor_s[k]);
			_marks>>marks[k-2];
		};

};

Student::Student(string _initials, int _nr_gr, int *tab){
	initials=_initials;
	nr_gr=_nr_gr;
	for(int i=0;i<10;i++){
		marks[i]=tab[i];
	};

}

Student::Student(Student& src){
	initials=src.initials;
	nr_gr=src.nr_gr;
	for(int i=0;i<10;i++)
	{
		marks[i]=src.marks[i];
	};
}

string Student::toString(){

	stringstream ss_student;
	ss_student<<initials<<";"<<nr_gr<<";";
	for(int i=0;i<10;i++)
	{
		ss_student<<marks[i]<<";";
	};
	ss_student<<endl;
	return(ss_student.str());
}

//#######################################################################################################################################333

int* tab(){
	int *tab=new int[10];
	for(int i=0;i<10;i++)
	{
		tab[i]=rand()%4+2;
	};
	return(tab);
}

