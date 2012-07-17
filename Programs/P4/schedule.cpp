// Eric Lowe and Rodolfo Hernandez
// schedule.cpp

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "catalog.h"
#include "quarter.h"
#include "schedule.h"

using namespace std;

Schedule::Schedule()
{
    
} // Schedule::Schedule()


Schedule::~Schedule()
{
  if(quarters)
    delete[] quarters;
  
  if(stname)
    delete[] stname;
  
  if(prvcourses) // if Schedule object has previous courses
  {
    for(int i = 0; i < prvcount; i++) // because it's a double pointer
    { 
      delete[] prvcourses[i];
    } // for(int i = 0; i < count; i++)
    delete[] prvcourses;
  } // if(prvcourses)
} // Schedule::~Schedule()
    

istream &operator>>(istream &in, Schedule &schedule)
{
  return(in);
} // friend istream& operator>>(istream &in, Schedule &schedule)
    

ostream &operator<<(ostream &out, Schedule &schedule)
{
  return(out);
} // friend ostream& operator<<(ostream &out, Schedule &schedule)

