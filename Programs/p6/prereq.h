// Eric Lowe and Rodolfo Hernandez
// prereq.h
//

#ifndef PREREQ_H
#define	PREREQ_H

#include <string>
#include <iostream>
using namespace std;

class Prereq
{
protected:
  string name;
public:
  Prereq(const string &n = "");
  virtual ~Prereq();
  const string& getName() const;
  bool operator< (const Prereq &rhs) const;
  virtual void print(ostream& os) const;
};


#endif	/* PREREQ_H */

