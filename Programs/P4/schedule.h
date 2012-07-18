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
    int qcount;
    int prvcount; // count of previous courses
    friend istream& operator>>(istream &in, Schedule &schedule);
    friend ostream& operator<<(ostream &out, Schedule &schedule);
    friend ifstream& operator>>(ifstream &inf, Schedule &schedule);
    friend ifstream& operator<<(ifstream &outf, Schedule &schedule);
    Schedule& operator+=(Schedule &schedule);
    Schedule& operator-=(Schedule &schedule);
    void writeFile();
    void courseMenu();
    void quarterMenu();
    void getPrevious();
    void getQuarters();
    void addQuarter();
    void remQuarter();
    void editQuarter();
    void saveSchedule();
public:
    Schedule();
    ~Schedule();
    void readFile();
    void editSchedule();
};
#endif /* SCHEDULE_H_ */
