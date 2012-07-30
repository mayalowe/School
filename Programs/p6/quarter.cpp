// Eric Lowe and Rodolfo Hernandez
// quarter.cpp
//


#include <cstring>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "list.h"
#include "quarter.h"

using namespace std;


Quarter::Quarter():courses(string())
{
}  // Quarter()


Quarter::Quarter(const string &seas, int y) : season(seas), year(y), 
  courses(string())
{
} // Quarter()


Quarter::Quarter(const Quarter &rhs) : season(rhs.season), year(rhs.year), 
  courses(rhs.courses)
{
  
} // Quarter()

Quarter::~Quarter()
{
} // ~Quarter()

bool Quarter::checkQuarter(short quarters) const
{
  if((season == "Fall") && (quarters & 1) == 0)
    return false;
  
   if((season == "Winter") && (quarters & 2) == 0)
    return false;
  
   if((season == "Spring") && (quarters & 4) == 0)
    return false;
  
  return true;
} // checkQuarter()


 bool Quarter::findCourse(const string &name) const
 {
   return courses.find(name) == name;
 } // findCourse
 
 

Quarter& Quarter::operator= (const Quarter &rhs)
{
  if(this == &rhs)
    return *this;
  
  year = rhs.year;
  season = rhs.season;
  courses = rhs.courses;;
  return *this;
} // operator=


bool Quarter::operator== (const Quarter &rhs) const
{
  return rhs.season == season && year == rhs.year;
}  // operator==


Quarter& Quarter::operator+= (const string &courseName)
{
  courses += courseName;
  return *this;
} // operator+=


Quarter& Quarter::operator-= (const string &courseName)
{
  if(courses.find(courseName) != courseName)
     cout << courseName << " does not exist in " << season << ' ' << year << ".\n";
  else
    courses -= courseName;
  
  return *this;
} // operator-=


bool Quarter::operator< (const Quarter &rhs) const
{
  if(year != rhs.year)
    return year < rhs.year;
  
  return season == "Winter" || rhs.season == "Fall";
} // operator<

istream& operator>> (istream &is, Quarter &rhs)
{
  char line[1000], *ptr;
  is.getline(line, 1000);
  ptr = strtok(line, ",");
  rhs.season = ptr;
  rhs.year = atoi(strtok(NULL, ","));
  int courseCount = atoi(strtok(NULL, ","));
  
  for(int i = 0; i < courseCount; i++)
  {
    ptr = strtok(NULL, ",");
    rhs.courses += string(ptr);
  }  // for each course in the quarter

  return is;
} // operator>>

ostream& operator<< (ostream &os, const Quarter &rhs)
{
  os << rhs.season << ',' << rhs.year << ',' << rhs.courses.getSize() << ',';
  
  for(int i = 0; i < rhs.courses.getSize(); i++)
    os << rhs.courses[i] << ',';
  
  os << endl;
  return os;
} // operator>>


void Quarter::printTime() const
{
  cout << season << ' ' << year << endl;
} // printTime()


void Quarter::show() const
{
  int i;
   
  cout << year << ' ' << left << setw(6) << season <<  ": ";
  
  if (courses.getSize() == 0)
    cout << "No courses.";
  else  // at least one course
  {
    for(i = 0; i < courses.getSize() - 1; i++)
      cout << left << setw(8) << courses[i] << ", ";
   
    cout << left << setw(8) << courses[i];
  }
  
  cout << endl;
} // show()
