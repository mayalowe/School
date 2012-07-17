// Eric Lowe and Rodolfo Hernandez
// schedule.cpp

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "catalog.h"
#include "quarter.h"
#include "schedule.h"

using namespace std;

// Complete constructor for Schedule class
Schedule::Schedule():stname(NULL), prvcourses(NULL), prvcount(0)
{
  quarters = new Quarter[1];
} // Schedule::Schedule()

// Schedule class destructor
Schedule::~Schedule()
{
  if(quarters) // if quarter object exists, delete it
    delete[] quarters;
  
  if(stname) // if student name exists, delete it
    delete[] stname;
  
  if(prvcourses) // if Schedule object has previous courses
  {
    for(int i = 0; i < prvcount; i++) // because it's a double pointer
    { 
      delete[] prvcourses[i];
    } // for(int i = 0; i < count; i++)
    delete[] prvcourses;
  } // if(prvcourses)
} // Schedule::~Schedule()
    
// Overloaded input stream extraction operator for Schedule class
istream &operator>>(istream &in, Schedule &schedule)
{
  return(in);
} // friend istream& operator>>(istream &in, Schedule &schedule)
    
// Overloaded output stream insertion operator for Schedule class
ostream &operator<<(ostream &out, Schedule &schedule)
{
  return(out);
} // friend ostream& operator<<(ostream &out, Schedule &schedule)

// Overloaded file stream extraction operator for Schedule class
// Reads from file
ifstream& operator>>(ifstream &inf, Schedule &schedule)
{
  return(inf);
} // friend ifstream& operator>>(ifstream &in, Schedule &schedule)
  
// Overloaded file stream insertion operator for Schedule class
// Writes to file
ifstream& operator<<(ifstream &outf, Schedule &schedule)
{
  return(outf);
} // friend ifstream& operator<<(ifstream &out, Schedule &schedule)
// Overloaded operator to add a Quarter object to Schedule
Schedule& Schedule::operator+=(Schedule &schedule)
{
  return(*this);
} // Schedule& Schedule::operator+=(Schedule &lhs, Quarter &rhs)    

// Overloaded operator to remove a Quarter object from Schedule
Schedule& Schedule::operator-=(Schedule &schedule)
{
  return(*this);
} // Schedule& Schedule::operator-=(Schedule &lhs, Quarter &rhs)     

// Method to read a schedule file if one exists
// Should ask for Student name, should attempt to open corresponding .csv file
// and then should call appropriate overloaded operators
void Schedule::readFile()
{
  char file[50];
  cin.ignore(100, '\n');
  cout << "Student name: ";
  cin.getline(file, 50);
  strcat(file, ".csv");
  //cout << "File is: " << file << endl;
  ifstream inf(file); // try to open file
  
  if(!inf) // if file not found print warning and get out
  {
    cout << file << " not found.\n" << endl;
    return;
  }
  //else
    
  return;
} // void Schedule::readFile()    

// Method to edit a schedule, either empty or existing.  If schedule is empty, should
// ask for student name but should not attempt to open a file by that name!
void Schedule::editSchedule()
{
  char name[50];
  cin.ignore(100, '\n');
  cout << "Student name: ";
  cin.getline(name, 50);
  
  if(!stname) // if student name is null
  {
    stname = new char[strlen(name) + 1]; // dynamically allocate memory for student name
    strcpy(stname, name);
    cout << "Name is " << name << endl; // for testing/debugging
    return;
  }
  return;
} // void Schedule::editSchedule()

// Method to write out a .csv file containing a student's schedule
void Schedule::writeFile()
{
  char file[50];
  
  if(!stname) // if student name is null, get out of here
    return;
  else
    strcpy(file, stname); // copy student name to file string
  // adds file extension to string file
  strcat(file, ".csv");
  
  ifstream outf(file, ios::app); // should open file for appending
  // next line should use overloaded insertion operator
  // outf << schedule;
  return;
} // void Schedule::writeFile()
