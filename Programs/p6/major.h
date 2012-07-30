// Eric Lowe and Rodolfo Hernandez
// major.h
//

#ifndef MAJOR_H
#define	MAJOR_H

class Major
{
  const static int NUM_PREPS = 5;
  const static int NUM_CORES = 5;
  const static int NUM_ELECTIVES = 32;
  const static int NUM_REQUIRED_ELECTIVES = 16;
  char prepatories[NUM_PREPS][9] ;
  char cores[NUM_CORES][9];
  char electives[NUM_ELECTIVES][9];
  char requiredElectives[NUM_REQUIRED_ELECTIVES][9];
public:
  void save();
};

#endif	/* MAJOR_H */

