// Eric Lowe and Rodolfo Hernandez
// schedule.h

#ifndef SCHEDULE_H_
#define SCHEDULE_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "catalog.h"
#include "quarter.h"

class Schedule {
    char *stname;
    char **prvcourses;
    Quarter *quarters;
};
#endif /* SCHEDULE_H_ */
