// Eric Lowe
// catalog.cpp
// Usage Statement:
//
// Explanations

#include <iostream>
#include <string>
#include <cstring>
#include "catalog.h"

using namespace std;


Catalog::Catalog() : count(0), size(10)
{
 
  courses = new Course[10];
  
} // Catalog()




Catalog::~Catalog()
{
  delete [] courses;
} // ~Catalog()




void Catalog::find()
{
  int i;
  char name[80], prereqList[1000] = "";
  cout << "Course name to find: ";
  cin.getline(name, 80);
  
  for(i = 0; i < count; i++)
    if((name == courses[i].getName()) == 0)
      break;
  
  if(i == count)
    cout << name << " not found.\n";
  else // name is in courses
  {
    cout << name << " ";
    courses[i].printQuarters();
    cout << ": ";
    printPrerequisites(i, prereqList);
    cout << prereqList << endl;
  }  // else found course
} // find()
 

char Catalog::getQuarters(const char *courseName) const
{
  for(int i = 0; i < count; i++)
    if((courseName == courses[i].getName()) == 0)
      return(courses[i].getQuarters());
  
  return(7);
} // getQuarters()


ifstream& operator>> (ifstream &inf, Catalog &rhs)
{
  if(rhs.count == rhs.size)
    rhs.resize();

  inf >> rhs.courses[rhs.count++];
  
  return(inf);
} // operator>>

void Catalog::printPrerequisites(int pos, string prereqList)
{
  int j;
  
  for(int i = 0; i < courses[pos].getCount(); i++)
  {
    const string name = courses[pos].getPrerequisite(i);
    
    if(prereqList.find(name) == string::npos)
    {
      if(prereqList.length() > 0)
        prereqList =+ ", ";
      
      prereqList += name;
    
      for(j = 0; j < count; j++)
        if((name == courses[j].getName()) == 0)
          break;
  
      if(j < count)
        printPrerequisites(j, prereqList);
    } // if new prereq
  }  // for each prerequisite of this course
} // printPrerequisites()


void Catalog:: resize()
{
  Course *temp = new Course[size * 2];
  
  for(int i = 0; i < size; i++)
    temp[i] = courses[i];
  
  delete [] courses;
  courses = temp;
  size *= 2;
} // resize()



 
void Catalog::printAll()
{
  for(int i = 0; i < count; i++)
    courses[i].print();
} // printAll()



