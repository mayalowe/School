// Eric Lowe
// schedule.cpp
// Usage Statement:
//
// Explanations

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include "schedule.h"

using namespace std;

Schedule::Schedule(): studentName(NULL), previousCourseCount(0), 
  previousCourses(NULL), quarterCount(0), quarters(NULL) 
{
}  // Schedule()




Schedule::~Schedule()
{
  if(studentName)
    delete[] studentName;
  
  if(previousCourses)
  {
    for(int i = 0; i < previousCourseCount; i++)
      delete[] previousCourses[i];
    
    delete [] previousCourses;
  }

  
  if(quarters)
    delete[] quarters;
} // ~Schedule()


void Schedule::addPreviousCourse()
{
  
  char line[1000];
  cout << "Course name to add: ";
  cin.getline(line, 1000);
  
  if(findCourse(line))
    return;
  
  char **temp = new char*[previousCourseCount + 1];
  
  for(int i = 0; i < previousCourseCount; i++)
    temp[i] = previousCourses[i];
  
  delete [] previousCourses;
  previousCourses = temp;
  temp[previousCourseCount] = new char[strlen(line) + 1];
  strcpy(temp[previousCourseCount++], line);
  
} // addPreviousCourse()


void Schedule::addQuarter(const Catalog &catalog)
{
  char season[80];
  int year;
  cout << "\nAdd Quarter\n";
  getQuarterTime(season, &year);
  
  for(int i = 0; i < quarterCount; i++)
    if(quarters[i] == Quarter(season, year))
    {
        cout << season << ' ' << year << " already exists.\n";
        return;
    } // if found a match
      
  Quarter *temp = new Quarter[quarterCount + 1];
  
  for(int i = 0; i < quarterCount; i++)
    temp[i] = quarters[i];
  
  temp[quarterCount] = Quarter(season, year);
  delete [] quarters;
  quarters = temp;
  quarterCount++;
  
  editExistingQuarter(quarterCount - 1, catalog);
  
} // addQuarter()



void Schedule::edit(const Catalog &catalog)
{
  int choice;
  char name[80];
  
  if(studentName == NULL)
  {
    cout << "Student name: ";
    cin.getline(name, 80);
    studentName = new char[strlen(name) + 1];
    strcpy(studentName, name);
  } // if name is NULL
  
  editPreviousCourses();
  editQuarters(catalog);
  
  do
  {
    cout << "Do you wish to save this schedule (0 = no, 1 = yes): ";
    cin >> choice;
  } while(choice < 0 || choice > 1);
  
  if(choice == 1)
  {
    strcat(name, ".csv");
    ofstream outf(name);
    outf << *this;
  }
} // edit()


void Schedule::editExistingQuarter(int pos, const Catalog &catalog)
{
  
  int choice;
  char courseName[20], courseQuarters;
  
  do
  {
    cout << endl;
    quarters[pos].show();
    
    cout << "\n\nEdit Quarter Menu\n";
    cout << "0. Done\n";
    cout << "1. Add course.\n";
    cout << "2. Remove course.\n";
    cout << "\nYour choice: ";
    cin >> choice;
    cin.ignore(100, '\n');

    if(choice == 1 || choice == 2)
    {
      cout << "Course name: ";
      cin.getline(courseName, 20);
    }

    switch(choice)
    {
      case 0: break;
      case 1: 
        courseQuarters = catalog.getQuarters(courseName);
        cout << courseName << endl;
        if(!quarters[pos].checkQuarter(courseQuarters))
        {
          cout << courseName << "is not offered that quarter.\n";
          break;
        } // if not offered that this quarter.
        
        if(!findCourse(courseName))
          quarters[pos] += courseName;
        break;
        
      case 2: 
        quarters[pos] -= courseName; 
        break;
        
      default: 
        cout << "Choice must be between 0 and 2.\n";
        break;
        
    } // switch
  } while(choice != 0);
} // editExistingQuarter()


void Schedule::editPreviousCourses()
{
  int choice;
  
  do
  {
    cout << "\nPrevious Courses:\n";
    if(previousCourseCount == 0)
      cout << "No previous courses.\n";
    else  // has some previous courses
      for(int i = 0; i < previousCourseCount; i++)
      {
        cout << left << setw(8) << previousCourses[i];
        if(i % 8 == 0 && i != 0)
          cout << endl;
      }  // for each previous course

    cout << "\n\nPrevious Course Menu\n";
    cout << "0. Done\n";
    cout << "1. Add course\n";
    cout << "2. Remove course\n";
    cout << "\nYour choice: ";
    cin >> choice;
    cin.ignore(100, '\n');
    
    switch(choice)
    {
      case 0: 
        break;
        
      case 1: 
        addPreviousCourse(); 
        break;
        
      case 2: 
        removePreviousCourse(); 
        break;
        
      default: 
        cout << "Choice must be between 0 and 2.\n";
        break;
        
    } // switch
  } while(choice != 0);
  
} // editPreviousCourses()



void Schedule::editQuarter(const Catalog &catalog)
{
  char season[80];
  int year;
  cout << "Edit Quarter\n";
  getQuarterTime(season, &year);
  
  for(int i = 0; i < quarterCount; i++)
    if(quarters[i] == Quarter(season, year))
    {
       editExistingQuarter(i, catalog);
       return;
    } // if found a match
  
  cout << season << ' ' << year << " does not exist.\n";
} // editQuarter();


void Schedule::editQuarters(const Catalog &catalog)
{
  int choice;
  
  do
  {
    cout << "Quarters\n";
  
    for(int i = 0; i < quarterCount; i++)
    quarters[i].show();
     
    cout << "\n\nQuarter Menu\n";
    cout << "0. Done\n";
    cout << "1. Add quarter\n";
    cout << "2. Remove quarter\n";
    cout << "3. Edit quarter\n";
    cout << "\nYour choice: ";
    cin >> choice;
    cin.ignore(100, '\n');
    
    switch(choice)
    {
      case 0: 
        break;
        
      case 1: 
        addQuarter(catalog); 
        break;
        
      case 2: 
        removeQuarter(); 
        break;
        
      case 3: 
        editQuarter(catalog); 
        break;
        
      default: 
        cout << "Choice must be between 0 and 3.\n";
        break;
        
    } // switch
  } while(choice != 0);
} // editQuarters()




bool Schedule::findCourse(const char *name) const
{
  
  for(int i = 0; i < previousCourseCount; i++)
    if(strcmp(previousCourses[i], name) == 0)
    {
      cout << name << " already is a previous course.\n";
      return(true);
    } // if course already in previousCourses

  for(int i = 0; i < quarterCount; i++)
    if(quarters[i].findCourse(name))
    {
      cout << name << " is already in ";
      quarters[i].printTime();
      return(true);
    }
  
  return(false);
} // findCourse()


void Schedule::getQuarterTime(char *season, int *year) const
{
  int seasonNum;
  
  do
  {
    cout << "Quarter season (1 = Fall, 2 = Winter, 3 = Spring): ";
    cin >> seasonNum;
    
    switch(seasonNum)
    {
      case 1: 
        strcpy(season, "Fall"); 
        break;
        
      case 2: 
        strcpy(season, "Winter"); 
        break;
        
      case 3: 
        strcpy(season, "Spring"); 
        break;
      default: 
        cout << "Season must be between 1 and 3.\n";
        break;
        
    } // switch
  } while(seasonNum < 1 || seasonNum > 3);
  
  cout << "Year: ";
  cin >> *year;
  cin.ignore(100, '\n');
} // getQuarterTime()

istream& operator>> (istream &is, Schedule &rhs)
{
  char line[1000], *ptr;
  is.getline(line, 1000);
  
  ptr = strtok(line, ",");
  rhs.studentName = new char[strlen(ptr) + 1];
  strcpy(rhs.studentName, ptr);
  rhs.previousCourseCount = atoi(strtok(NULL, ","));
  rhs.previousCourses = new char*[rhs.previousCourseCount];
  rhs.quarterCount = atoi(strtok(NULL, ","));
  rhs.quarters = new Quarter[rhs.quarterCount];
  is.getline(line, 1000);
  ptr = strtok(line, ",");
  
  for(int i = 0; i < rhs.previousCourseCount; i++)
  {
    rhs.previousCourses[i] = new char[strlen(ptr) + 1];
    strcpy(rhs.previousCourses[i], ptr);
    ptr = strtok(NULL, ",");
  } // while more previous courses;
  
  for(int i = 0; i < rhs.quarterCount; i++)
    is >> rhs.quarters[i];
  
  return(is);
} // operator>>


ostream& operator<< (ostream &os, const Schedule &rhs)
{
  os << rhs.studentName << ',' 
    << rhs.previousCourseCount << ',' << rhs.quarterCount << endl;
  
  for(int i = 0; i < rhs.previousCourseCount; i++)
    os << rhs.previousCourses[i] << ',';
  
  os << endl;

  
  for(int i = 0; i < rhs.quarterCount; i++)
    os << rhs.quarters[i];
  
  return(os);
} // operator<<


void Schedule::read()
{
  char name[80];
  cout << "Student name: ";
  cin.getline(name, 80);
  strcat(name, ".csv");
  ifstream inf(name);
  if(!inf)
  {
    cout << name << " not found.\n";
    return;
  }
  
  inf >> *this;
  
  cout << "\nPrevious Courses:\n";
  if(previousCourseCount == 0)
    cout << "No previous courses.\n";
  else  // has some previous courses
    for(int i = 0; i < previousCourseCount; i++)
    {
      cout << left << setw(8) << previousCourses[i];
    
      if(i % 8 == 0 && i != 0)
        cout << endl;
    }  // for each previous course
  
  cout << "\nQuarters:\n";
  for(int i = 0; i < quarterCount; i++)
    quarters[i].show();
}  // read()


void Schedule::removePreviousCourse()
{
  char line[1000];
  cout << "Course name to remove: ";
  cin.getline(line, 1000);
  
  for(int i = 0; i < previousCourseCount; i++)
    if(strcmp(previousCourses[i], line) == 0)
    {
      for(int j = i; j < previousCourseCount - 1; j++)
        previousCourses[j] = previousCourses[j + 1];
      
      previousCourseCount--;
      return;
    } // if course already in previousCourses
  
  cout << line << " is not a previous course.\n";
} // removePreviousCourse()


void Schedule::removeQuarter()
{
  char season[80];
  int year;
  cout << "Remove Quarter\n";
  getQuarterTime(season, &year);
  
  for(int i = 0; i < quarterCount; i++)
    if(quarters[i] == Quarter(season, year))
    {
      for(int j = i; j < quarterCount - 1; j++)
        quarters[j] = quarters[j + 1];
       
      quarterCount--;
      return;
    } // if found a match
  
  cout << season << ' ' << year << " does not exist.\n";
} // removeQuarter()



