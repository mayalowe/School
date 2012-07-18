// Eric Lowe and Rodolfo Hernandez
// quarter.h

#ifndef QUARTER_H_
#define QUARTER_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "course.h"

class Quarter {
  char *season;
  char *year;
  char **courses;
  int count; // int variable to count number of courses in quarter
public:
  Quarter();
  ~Quarter();
  friend istream& operator>>(istream &in, Quarter &quarter);
  friend ostream& operator<<(ostream &out, Quarter &quarter);
  Quarter& operator=(const Quarter &rhs);
  Quarter& operator+=(Quarter &quarter);
  Quarter& operator-=(Quarter &quarter);
  Quarter& operator==(Quarter &quarter);
  
};
#endif /* QUARTER_H_ */
