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
Schedule::Schedule():stname(NULL), prvcourses(NULL), qcount(0), prvcount(0)
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
  outf << schedule.stname << "," << schedule.prvcount << "," << schedule.qcount << "\n";
  if(schedule.prvcount > 0)
  {
    for(int i = 0; i < schedule.prvcount; i++)
    {
      outf << schedule.prvcourses[i] << ",";
    } // for(int i = 0; i < schedule.prvcount; i++)
  } // if(schedule.prvcount > 0)
  outf << "\n";
  
  if(schedule.qcount > 0)
  {
    for(int j = 0; j < schedule.qcount; j++)
    {
      outf << schedule.quarters[j] << "\n";
    } // for(int j = 0; j < qcount; j++)
  } // if(schedule.qcount > 0)
  
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
  }
  
  quarterMenu(); // calls menu method
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
  
  ifstream outf(file, ios::out); // should open file for appending
  // next line should use overloaded insertion operator
  outf << schedule;
  return;
} // void Schedule::writeFile()

// Method to print out the previous course menu
void Schedule::courseMenu()
{
  int choice;
  
  // Before this do-while loop should call Schedule method to list previous courses
  do
  {
    cout << "Previous Course Menu\n";
    cout << "0. Done\n1. Add course\n2. Remove course\n" << endl;
    cout << "Your choice: ";
    cin >> choice;
    
    if(choice != 0)
    {
      switch(choice)
      {
        case 1:
          cout << "Will allow you to add course soon\n";
          break;
          
        case 2:
          cout << "Will allow you to remove course soon\n";
          break;
          
        default:
          cout << "Choice must be between 0 and 2.\n" << endl;
          break;
      } // switch(choice)
    } // if(choice != 0)
  }while(choice != 0);
  
  return;
} // void Schedule::courseMenu()


// Method to print out the quarter menu
void Schedule::quarterMenu()
{
  int choice;
  
  getPrevious(); // call method to list previous courses
  courseMenu(); // call method to print previous course menu with options
  getQuarters();
  do // this will loop at least once, and will continue to loop if choice != 0
  {
    cout << "\n\nQuarter Menu\n";
    cout << "0. Done\n1. Add quarter\n2. Remove quarter\n3. Edit quarter\n" << endl;
    cout << "Your choice: ";
    cin >> choice;
        
    if(choice != 0)
    {
      switch(choice)
      {
        case 1:
          addQuarter();
          break;
              
        case 2:
          remQuarter();
          break;
          
        case 3:
          editQuarter();
          break;
              
        default:
          cout << "Choice must be between 0 and 2.\n" << endl;
          break;
      } // switch(choice)
    } // if(choice != 0)  
  }while(choice != 0);
  saveSchedule();
  return;
} // void Schedule::quarterMenu()


// Method to print out the previous courses taken by a student, if known
// and will print no previous courses if no previous courses exist
void Schedule::getPrevious()
{
  cout << "\nPrevious Courses: \n";
  
  if(prvcount == 0) // if no previous courses
  {
    cout << "No previous courses.\n\n" << endl;
    return;
  } // if(prvcount == 0)
  else // previous courses exist
  {
    for(int i = 0; i < prvcount; i++) // because previous courses is a double pointer
    {
      cout << prvcourses[i] << " ";
    } // for(int i = 0; i < prvcount; i++)
    cout << "\n" << endl;
  } // else
  return;
} // void Schedule::getPrevious()

// Method to print info for all quarters in a schedule
// Relies on quarter class overloaded operators
void Schedule::getQuarters()
{
  cout << "Quarters\n";
  
  if(qcount == 0)
    return;
  
  else
  {
    for(int i = 0; i < qcount; i++)
    {
      cout << quarters[i] << "\n";
    } // for(int i = 0; i < qcount; i++)
  } // else
  return;
} // void Schedule::getQuarters()

//
void Schedule::addQuarter()
{
  int season;
  char year[10];
  if(qcount > 0)
  {
    qcount++;
    quarters += qcount;
  } // if(qcount > 0)
    
  cout << "\nAdd Quarter\n";
  cout << "Quarter season (1 = Fall, 2 = Winter, 3 = Spring): ";
  cin >> season;
  cin.ignore();
  cout << "Year: ";
  cin.getline(year, 10);
  
  editQuarter();
  return;
} // void Schedule::addQuarter()
 
//
void Schedule::remQuarter()
{
  
  return;
} // void Schedule::remQuarter()
 
//
void Schedule::editQuarter()
{
  int choice;
  cout << "\n\nEdit Quarter Menu\n";
  cout << "0. Done\n1. Add course.\n2. Remove course.\n\n";
  cout << "Your choice: ";
  cin >> choice;
  cout << "Will let you edit soon\n";
  return; 
} // void editQuarter()

void Schedule::saveSchedule()
{
  int save;
  
  do
  {
    cout << "Do you wish to save this schedule (0 = no, 1 = yes): ";
    cin >> save;
    if(save != 0)
    {
      switch(save)
      {
        case 1:
          writeFile();
          break;
          
        default:
          break;
      } // switch(save)
    } // if(save != 0)
  }while(save != 0);
  
  return;
} // void Schedule::saveSchedule()
