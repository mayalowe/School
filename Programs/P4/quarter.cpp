// Eric Lowe and Rodolfo Hernandez
// quarter.cpp

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "course.h"
#include "schedule.h"
#include "quarter.h"

using namespace std;

Quarter::Quarter():season(NULL), year(NULL), courses(NULL), count(0)
{
  
} // Quarter::Quarter()
  

Quarter::~Quarter()
{
  if(season)
    delete[] season;
  
  if(year)
    delete[] year;
  
  if(courses) // if Quarter object has courses
  {
    for(int i = 0; i < count; i++) // because it's a double pointer
    { 
      delete[] courses[i];
    } // for(int i = 0; i < count; i++)
    delete[] courses;
  } // if(courses)
} // Quarter::~Quarter()
  

istream &operator>>(istream &in, Quarter &quarter)
{
  return(in);
} // friend istream& operator>>(istream &in, Quarter &quarter)
  

ostream &operator<<(ostream &out, Quarter &quarter)
{
  return(out);
} // friend ostream& operator<<(ostream &out, Quarter &quarter)


Quarter& Quarter::operator+=(Quarter &quarter)
{
  return(*this);
} // Quarter& operator+=(Quarter &quarter)

  
Quarter& Quarter::operator-=(Quarter &quarter)
{
  return(*this);
} // Quarter& operator-=(Quarter &quarter)

  
Quarter& Quarter::operator==(Quarter &quarter)
{
  return(*this);
} // Quarter& operator==(Quarter &quarter)
