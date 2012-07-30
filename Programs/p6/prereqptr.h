// Eric Lowe and Rodolfo Hernandez
// prereqptr.h
//

#ifndef PREREQPTR_H
#define	PREREQPTR_H

#include "prereq.h"

class PrereqPtr
{
  Prereq *prereqPtr;
public:
  PrereqPtr(Prereq *ptr = NULL);
  bool operator< (const PrereqPtr &rhs) const;
  bool operator== (const PrereqPtr &rhs) const;
  const Prereq* operator-> () const;
  friend ostream& operator<< (ostream &os, const PrereqPtr &rhs);
};  // class PrereqPtr

#endif	/* PREREQPTR_H */

