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
    Quarter *quarters;
    char *stname;
    char **prvcourses;
    int prvcount; // count of previous courses
    
public:
    Schedule();
    ~Schedule();
    friend istream& operator>>(istream &in, Schedule &schedule);
    friend ostream& operator<<(ostream &out, Schedule &schedule);
    Schedule& operator+=(Schedule &schedule);
    Schedule& operator-=(Schedule &schedule);
    void readFile();
    void editSchedule();
};
#endif /* SCHEDULE_H_ */
