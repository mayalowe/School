// Author: Sean Davis
#ifndef SCHEDULE_H
#define	SCHEDULE_H

#include <iostream>
#include <string>
#include "quarter.h"
#include "catalog.h"
#include "list.h"
using namespace std;


class Schedule
{
  string studentName;
  List <string> previousCourses;
  List <Quarter> quarters;
  void addPreviousCourse();
  void addQuarter(const Catalog &catalog);
  void editExistingQuarter(int pos, const Catalog &catalog);
  void editPreviousCourses();
  void editQuarter(const Catalog &catalog);
  void editQuarters(const Catalog &catalog);
  bool findCourse(const string &name) const;
  void getQuarterTime(string &season, int *year) const;
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

#endif	/* SCHEDULE_H */

