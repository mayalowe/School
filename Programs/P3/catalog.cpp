// Eric Lowe and Rodolfo Hernandez
// catalog.cpp

#include <iostream>
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
  courses = new Course[ size ]; // declares array of Course objects of size = size (10)
  DIR *dir = opendir("../../exp_course_desc");
  
  if(dir) // if directory exists
  {
    struct dirent *ent;
    while((ent = readdir(dir)) != NULL) // while reading from dir
    {
      if(ent->d_name[0] != '.') // if file isn't a hidden file                                                  
      {
        if (count == size - 1) // if number of files read equal to Course array size
          moreCourses(); // grow Course array
       
        openFile(ent->d_name);
        count++; // increment count
      } // if(ent->d_name)                                                                                      
    } // while((ent = readdir(dir)) != NULL)                                                                    
  } // if(dir)
  else
  {
    cout << "Error opening directory\n";
    return;
  } // else if directory can't be read
  
} // Catalog::Catalog()

// Catalog object destructor
Catalog::~Catalog()
{
  if (courses)
    delete[] courses;
} // Catalog::~Catalog()

// This function finds a specific class in Catalog and 
// displays its name and prereqs
void Catalog::findClass()
{
  int i, t = 0;
  char name[25];
  cin.ignore();
  cout << "Course name to find: ";
  cin.getline(name, 25); 
  
  for (i = 0; i < count; i++)
  {
    if (strcmp(name, courses[i].getName()) == 0) 
    {
      cout << courses[i].getName() << ": \n" << endl;
      t = 1;
      break;
    } // if (strcmp(name, courses[i].getName()) != 0)
  } // for (i = 0; i < count; i++)
  if (t == 0) 
  {
    cout << name << " not found.\n" << endl;
  } // if (t == 0);
  return;
} // void Catalog::findClass()

// This function dynamically grows Course array
void Catalog::moreCourses()
{
  Course *temp = new Course[ size * 2 ]; // Dynamically allocate temp Course array
  
  for (int i = 0; i < size - 1; i++) 
  {
    temp[i] = courses[i];
  } // for (int i = 0; i < size - 1; i++)
  delete[] courses;
  courses = temp;
  size *= 2; // double size
  return;
} // void Catalog::moreCourses()

// This function opens files for parsing
void Catalog::openFile(const char *file)
{
  char path[50] = "../../exp_course_desc/";
  strcat(path, file);
  ifstream inf(path);
  if (!inf) 
  {
    cout << "Couldn't open file!\n" << endl;
    exit(1);
  } // if (!inf)
  
  courses[count].parseFile(inf); // open file for parsing
  return;
} // void Catalog::openFile(const char *file)

// This function prints the menu called in main()
void Catalog::printMenu()
{
  cout << "Menu\n" << "0. Done.\n" << "1. Find a course.\n" << "2. Show all courses.\n\n";
  cout << "Your choice: ";
  return;
} // void Catalog::printMenu()

// This function is called from main()
// Shows all courses with their prereqs
void Catalog::showAll()
{
  int i;
  for (i = 0; i < count; i++) 
  {
    courses[i].printFile();
  } // for (i = 0; i < count; i++)
  
  return;
} // void Catalog::showAll()




