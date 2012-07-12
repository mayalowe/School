// Eric Lowe
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
  char path[150];
  courses = new Course[10]; // declares array of Course objects of size = size (10)
  DIR *dir = opendir("/Users/Eric/Desktop/ecs40/exp_course_desc");
  
  if(dir) // if directory exists
  {
    struct dirent *ent;
    while((ent = readdir(dir)) != NULL) // while reading from dir
    {
      if(strstr(ent->d_name, ".html")) // if file isn't a hidden file                                                  
      {
        if (count == size) // if number of files read equal to Course array size
          moreCourses(); // grow Course array
       
        strcpy(path, "/Users/Eric/Desktop/ecs40/exp_course_desc/");
        strcpy(path, ent->d_name);
        ifstream inf(path);

	if (!inf)
	{
	  cout << "Couldn't open file " << path << "\n" << endl;
	  exit(1);
	}
        if(courses[count].parseFile(inf))
          count++; // increment count
      } // if(strstr(ent->d_name, ".html"))                                                                                      
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
  cout << "Menu\n" << "0. Done.\n" << "1. Find a course.\n" << "2. Show all courses.\n\n";
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
