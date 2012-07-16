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
#include "schedule.h"

class Quarter {
    char *season;
    char *year;
    char **courses;
};
#endif /* QUARTER_H_ */
