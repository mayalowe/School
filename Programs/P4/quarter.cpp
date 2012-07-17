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

// Quarter object complete constructor
Quarter::Quarter():season(NULL), year(NULL), courses(NULL), count(0)
{
  
} // Quarter::Quarter()
  
// Quarter object destructor
Quarter::~Quarter()
{
  if(season) // if Quarter object has seasons, deallocate the memory
    delete[] season;
  
  if(year) // Same as above
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
  
// Overloaded input stream extraction operator for Quarter class
istream &operator>>(istream &in, Quarter &quarter)
{
  return(in);
} // friend istream& operator>>(istream &in, Quarter &quarter)
  
// Overloaded output stream insertion operator for Quarter class
ostream &operator<<(ostream &out, Quarter &quarter)
{
  return(out);
} // friend ostream& operator<<(ostream &out, Quarter &quarter)

// Course object copy constructor
Quarter& Quarter::operator=(const Quarter &rhs)
{
  return(*this);
} // Quarter& Quarter::operator=(const Quarter &rhs)

// Overloaded operator to add a course name to Quarter object
Quarter& Quarter::operator+=(Quarter &quarter)
{
  return(*this);
} // Quarter& operator+=(Quarter &quarter)

// Overloaded operator to remove a course name from Quarter object
Quarter& Quarter::operator-=(Quarter &quarter)
{
  return(*this);
} // Quarter& operator-=(Quarter &quarter)

// Overloaded operator to test if two Quarters have the same season and year  
Quarter& Quarter::operator==(Quarter &quarter)
{
  return(*this);
} // Quarter& operator==(Quarter &quarter)
