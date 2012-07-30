// Eric Lowe and Rodolfo Hernandez
// prereq.cpp
//

#include <string>
#include "prereq.h"
using namespace std;


Prereq::Prereq(const string &n) : name(n)
{
} // Prereq()


Prereq::~Prereq()
{
} // ~Prereq()


const string& Prereq::getName() const
{
  return name;
}  // getName()


bool Prereq::operator< (const Prereq &rhs) const
{
  return name < rhs.name;
} // operator<




void Prereq::print(ostream& os) const
{
  os << name;
}  // print()


