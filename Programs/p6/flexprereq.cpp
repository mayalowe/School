// Eric Lowe and Rodolfo Hernandez
// flexprereq.cpp
//


#include "flexprereq.h"


FlexPrereq::FlexPrereq(const string &n) : Prereq(n), names(string())
{
  
} // FlexPrereq()


FlexPrereq& FlexPrereq::operator+= (const string &n)
{
  names += n;
  return *this;
}  // operator+=


void FlexPrereq::print(ostream &os) const
{
  int i;
  os << '(';
  Prereq::print(os);
  for(i = 0; i < names.getSize() - 1; i++)
    os << ", " << names[i];
  
  os << ", or " << names[i] << ") "; 
    
}
