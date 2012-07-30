// Eric Lowe and Rodolfo Hernandez
// prereqptr.cpp
//

#include "prereq.h"
#include "prereqptr.h"



PrereqPtr::PrereqPtr(Prereq *ptr) : prereqPtr(ptr)
{
} // PrereqPtr()


bool PrereqPtr::operator< (const PrereqPtr &rhs) const
{
  if(prereqPtr == NULL || rhs.prereqPtr == NULL)
    return false;
  
  return *prereqPtr < *rhs.prereqPtr;
}


bool PrereqPtr::operator== (const PrereqPtr &rhs) const
{
  if(prereqPtr == NULL)
    return rhs.prereqPtr == NULL;
  
  if(rhs.prereqPtr == NULL)
    return false;
  
  return prereqPtr->getName() == rhs.prereqPtr->getName();
}  // operator==


ostream& operator<< (ostream &os, const PrereqPtr &rhs)
{
  rhs.prereqPtr->print(os);
  return os;
} // operator<<


const Prereq* PrereqPtr::operator-> () const
{
  return prereqPtr;
}  // operator->
