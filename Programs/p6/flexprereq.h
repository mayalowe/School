// Eric Lowe and Rodolfo Hernandez
// flexprereq.h
//

#ifndef FLEXPREREQ_H
#define	FLEXPREREQ_H
#include <string>
#include "list.h"
#include"prereq.h"

class FlexPrereq : public Prereq
{
  List <string> names;
public:
  FlexPrereq(const string &name);
  FlexPrereq& operator+= (const string &name);
  void print(ostream&) const;
};

#endif	/* FLEXPREREQ_H */

