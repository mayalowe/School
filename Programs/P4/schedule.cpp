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

Schedule::Schedule():stname(NULL), prvcourses(NULL), prvcount(0)
{
  quarters = new Quarter[1];
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

Schedule& Schedule::operator+=(Schedule &schedule)
{
  return(*this);
} // Schedule& Schedule::operator+=(Schedule &lhs, Quarter &rhs)    

Schedule& Schedule::operator-=(Schedule &schedule)
{
  return(*this);
} // Schedule& Schedule::operator-=(Schedule &lhs, Quarter &rhs)     

void Schedule::readFile()
{
  cout << "I'll be reading your schedule files shortly!\n" << endl;
  return;
} // void Schedule::readFile()    

void Schedule::editSchedule()
{
  cout << "I'll be helping you edit your schedule shortly!\n" << endl;
  return;
} // void Schedule::editSchedule()
