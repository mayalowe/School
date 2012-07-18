// Eric Lowe and Rodolfo Hernandez
// catalog.cpp

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <dirent.h>
#include <sys/types.h>
#include <cstdlib>
#include "catalog.h"
#include "course.h"

using namespace std;

// Catalog object constructor
// Opens directory for reading, declares Course object array
Catalog::Catalog():count(0), size(10)
{
  courses = new Course[10]; // declares array of Course objects of size = size (10) 
} // Catalog::Catalog()

// Catalog object destructor
Catalog::~Catalog()
{
  if (courses)
    delete[] courses;
} // Catalog::~Catalog()

// Catalog class overloaded extraction operator
ifstream &operator>>(ifstream &inf, Catalog &rhs)
{
  if (rhs.count == rhs.size) // if number of files read equal to Course array size
    rhs.moreCourses(); // grow Course array
  
  if(rhs.courses[rhs.count].parseFile(inf))
    rhs.count++; // increment count
  
  return(inf);
} // istream &operator>>(istream &inf, Catalog &rhs)

// Function to find a specific class in the Catalog Object
void Catalog::findClass()
{
  int i;
  char name[80], prereqList[1000] = "";
  cin.ignore(100, '\n');
  cout << "Course name to find: ";
  cin.getline(name, 80);
  
  for(i = 0; i < count; i++)
  {
    if(strcmp(name, courses[i].getName()) == 0)
      break;
  } // for(i = 0; i < count; i++)
  
  if(i == count)
    cout << name << " not found.\n\n";
  else
  {
    cout << name << " ";
    courses[i].printQuarters();
    cout << ": ";
    printPrereqs(i, prereqList);
    cout << prereqList << endl << endl;
  } // else
} // void Catalog::findClass()

// Function to dynamically grow the array of course objects 
void Catalog::moreCourses()
{
  Course *temp = new Course[size * 2];
  
  for(int i = 0; i < size; i++)
  {
    temp[i] = courses[i];
  } // for(int i = 0; i < size; i++)
  
  delete[] courses;
  courses = temp;
  size *= 2;
  return;
} // void Catalog::moreCourses()


void Catalog::printMenu()
{
  cout << "\nMenu\n" << "0. Done.\n" << "1. Find a course.\n" << "2. Show all courses.\n";
  cout << "3. Read schedule.\n" << "4. Edit schedule.\n";
  cout << "Your choice: ";
  return;
} // void Catalog::printMenu()

void Catalog::printPrereqs(int pos, char prereqList[])
{
  int i, j;
  
  for(i = 0; i < courses[pos].getCount(); i++)
  {
    const char *name = courses[pos].getPrereq(i);
    
    if(strstr(prereqList, name) == NULL)
    {
      if(strlen(prereqList) > 0)
        strcat(prereqList, ", ");
      
      strcat(prereqList, name);
      
      for(j = 0; j < count; j++)
      {
        if(strcmp(name, courses[j].getName()) == 0)
          break;
      } // for(j = 0; j < count; j++)
      
      if(j < count)
        printPrereqs(j, prereqList);
    } // if(strstr(prereqList, name) == NULL)
  } // for(i = 0; i < courses[pos].getCount(); i++)
} // void Catalog::printPrereqs(int pos, char prereqList[])


void Catalog::showAll()
{
  int i;
  for (i = 0; i < count; i++) 
  {
    courses[i].printFile();
  } // for (i = 0; i < count; i++)
  
  return;
} // void Catalog::showAll()
