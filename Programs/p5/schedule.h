// Eric Lowe
// schedule.h
// Usage Statement:
//
// Explanations

#ifndef SCHEDULE_H_
#define SCHEDULE_H_

#include <iostream>
#include "quarter.h"
#include "catalog.h"
using namespace std;


class Schedule
{
  char *studentName;
  int previousCourseCount;
  char **previousCourses;
  int quarterCount;
  Quarter *quarters;
  void addPreviousCourse();
  void addQuarter(const Catalog &catalog);
  void editExistingQuarter(int pos, const Catalog &catalog);
  void editPreviousCourses();
  void editQuarter(const Catalog &catalog);
  void editQuarters(const Catalog &catalog);
  bool findCourse(const char *name) const;
  void getQuarterTime(char *season, int *year) const;
  void removePreviousCourse();
  void removeQuarter();
public:
  Schedule();
  ~Schedule();
  void edit(const Catalog &catalog);
  friend istream& operator>> (istream &is, Schedule &rhs);
  friend ostream& operator<< (ostream &os, const Schedule &rhs);
  void read();
};



#endif /* SCHEDULE_H_ */
