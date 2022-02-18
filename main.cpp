#include <iostream>
#include <conio.h>//for getch()
#include <iomanip>//for setw()
#include<fstream>//for file write()
#include<ios>//stream size
#include<limits>//numeric limits
#include<windows.h>//for editing display
using namespace std;

//structure of a registered course, a student and a course
struct Reg_course
{
    int reg_courseNo;
    string grade;
};

struct Student
{
	int id;
	string fname;
	string lname;
	int age;
	char sex;
	Reg_course reg_course[50];
    Student *snext;

};

struct Course 
{
    int courseNo;
    int creditHr;
    string courseName;
    Course *cnext;
};