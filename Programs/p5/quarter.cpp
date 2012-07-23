// Eric Lowe
// quarter.cpp
// Usage Statement:
//
// Explanations

#include <cstring>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "quarter.h"

using namespace std;


Quarter::Quarter(): season(NULL), year(NULL), courseCount(0), courses(NULL)
{
}  // Quarter()


Quarter::Quarter(const char *seas, int y) : year(y), courseCount(0), courses(NULL)
{
  season = new char[strlen(seas) + 1];
  strcpy(season, seas);
} // Quarter()


Quarter::~Quarter()
{
  if(season)
    delete [] season;
  
  if(courses)
  {
    for(int i = 0; i < courseCount; i++)
      delete [] courses[i];
    
    delete [] courses;
  } // if courses;
  
} // ~Quarter()

bool Quarter::checkQuarter(char quarters) const
{
  if(strcmp(season, "Fall") == 0 && (quarters & 1) == 0)
    return(false);
  
   if(strcmp(season, "Winter") == 0 && (quarters & 2) == 0)
    return(false);
  
   if(strcmp(season, "Spring") == 0 && (quarters & 4) == 0)
    return(false);
  
  return(true);
} // checkQuarter()


 bool Quarter::findCourse(const char* name) const
 {
   for(int i = 0; i < courseCount; i++)
     if(strcmp(name, courses[i]) == 0)
       return(true);
   
   return(false);
 } // findCourse
 
 

Quarter& Quarter::operator= (const Quarter &rhs)
{
  if(this == &rhs)
    return(*this);
  
  year = rhs.year;
  
  if(season)
    delete [] season;
  
  if(courses)
  {
    for(int i = 0; i < courseCount; i++)
      delete [] courses[i];
    
    delete [] courses;
  } // if courses;
  
  if(rhs.season)
  {
    season = new char[strlen(rhs.season) + 1];
    strcpy(season, rhs.season);
  } // if rhs.season
  else
    season = NULL;
  
  courseCount = rhs.courseCount;
  
  if(rhs.courses)
  {
    courses = new char* [courseCount];
    
    for(int i = 0; i < courseCount; i++)
    {
      courses[i] = new char[strlen(rhs.courses[i]) + 1];
      strcpy(courses[i], rhs.courses[i]);
    }  // for each course
  }  // if rhs.courses

  return(*this);
} // operator=


bool Quarter::operator== (const Quarter &rhs) const
{
  if(season == NULL)
    return(rhs.season == NULL && year == rhs.year);
  
  return(rhs.season != NULL && strcmp(season, rhs.season) == 0 
    && year == rhs.year);
}


Quarter& Quarter::operator+= (const char *courseName)
{
  char **temp = new char*[courseCount + 1];
  
  for(int i = 0; i < courseCount; i++)
    temp[i] = courses[i];
  
  delete [] courses;
  courses = temp;
  courses[courseCount] = new char[strlen(courseName) + 1];
  strcpy(courses[courseCount++], courseName);
  return(*this);
} // operator+=


Quarter& Quarter::operator-= (const char *courseName)
{
  for(int i = 0; i < courseCount; i++)
  {
    if(strcmp(courses[i], courseName) == 0)
    {
      delete [] courses[i];
      
      for(int j = i; j < courseCount - 1; j++)
        courses[j] = courses[j + 1];
      
      courseCount--;
      return(*this);
    }
  } // for each course name
  
  cout << courseName << " does not exist in " << season << ' ' << year << ".\n";
  return(*this);
} // operator-=


istream& operator>> (istream &is, Quarter &rhs)
{
  char line[1000], *ptr;
  is.getline(line, 1000);
  ptr = strtok(line, ",");
  rhs.season = new char[strlen(ptr) + 1];
  strcpy(rhs.season, ptr);
  rhs.year = atoi(strtok(NULL, ","));
  rhs.courseCount = atoi(strtok(NULL, ","));
  rhs.courses = new char*[rhs.courseCount];
  
  for(int i = 0; i < rhs.courseCount; i++)
  {
    ptr = strtok(NULL, ",");
    rhs.courses[i] = new char[strlen(ptr) + 1];
    strcpy(rhs.courses[i], ptr);
  } // for each course
  return(is);
} // operator>>

ostream& operator<< (ostream &os, const Quarter &rhs)
{
  os << rhs.season << ',' << rhs.year << ',' << rhs.courseCount << ',';
  
  for(int i = 0; i < rhs.courseCount; i++)
    os << rhs.courses[i] << ',';
  
  os << endl;
  return(os);
} // operator>>


void Quarter::printTime() const
{
  cout << season << ' ' << year << endl;
} // printTime()


void Quarter::show() const
{
  int i;
   
  cout << year << ' ' << left << setw(6) << season <<  ": ";
  
  if (courseCount == 0)
    cout << "No courses.";
  else  // at least one course
  {
    for(i = 0; i < courseCount - 1; i++)
      cout << left << setw(8) << courses[i] << ", ";
   
    cout << left << setw(8) << courses[i];
  }
  
  cout << endl;
} // show()



