// Author: Sean Davis

#include <iostream>

#include <cstring>
#include "list.h"
#include "catalog.h"

using namespace std;


Catalog::Catalog() : courses(Course())
{
 
  
} // Catalog()




Catalog::~Catalog()
{
} // ~Catalog()




void Catalog::find()
{
  string name;
  string prereqList;
  cout << "Course name to find: ";
  getline(cin, name);
  
  const Course &course = courses.find(Course(name));
  
  if(course.getName() == "")
    cout << name << " not found.\n";
  else // name is in courses
  {
    cout << name << " ";
    course.printQuarters();
    cout << ": ";
    printPrerequisites(name, prereqList);
    cout << prereqList << endl;
  }  // else found course
} // find()
 

short Catalog::getQuarters(const string &courseName) const
{
  const Course course = courses.find(Course(courseName));
  return course.getQuarters();
} // getQuarters()


ifstream& operator>> (ifstream &inf, Catalog &rhs)
{
  Course course;
  inf >> course;
  rhs.courses += course;
  return inf;
} // operator>>

void Catalog::printPrerequisites(const string &courseName, string &prereqList)
{
  Course course = courses.find(Course(courseName));
  
  if(course.getName() == courseName)
  {
    for(int i = 0; i < course.getSize(); i++)
    {
      string name = course.getPrerequisite(i);

      if(prereqList.find(name) == string::npos)
      {
        if(prereqList.size() > 0)
          prereqList += ", ";

         prereqList += name;
         printPrerequisites(name, prereqList);
      } // if new prereq
    }  // for each prerequisite of this course
  } // if course found
} // printPrerequisites()



void Catalog::printAll()
{
  for(int i = 0; i < courses.getSize(); i++)
    courses[i].print();
} // printAll()

