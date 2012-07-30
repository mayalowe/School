// Eric Lowe and Rodolfo Hernandez
// course.h
//


#ifndef course_H
#define	course_H

#include <fstream>
#include <string>
#include "list.h"
#include "prereq.h"
#include "flexprereq.h"
#include "prereqptr.h"
using namespace std;


class Course
{
  string name;
  List <PrereqPtr> prerequisites;
  short quarters;
  void addPrereqName(const string &prereqName);
  bool checkFlexPrereq(const string &line, const string &prereqName, 
    FlexPrereq **flexPrereqPtr);
  void correctPrereqName(string &prereqName, const string &previous) const;
  void readQuarters();
  int readPrerequisite(char *ptr, int pos, string &previous,
    FlexPrereq **flexPrereqPtr);
  void readPrerequisites(ifstream &inf);
public:
  Course();
  Course(const string &nam);
  Course(const Course &course);
  ~Course();
  int getSize() const;
  const string& getName() const;
  const string& getPrerequisite(int pos) const;
  short getQuarters() const;
  friend ifstream& operator>> (ifstream &inf, Course &rhs);
  Course& operator= (const Course &rhs);
  bool operator< (const Course &rhs) const;
//  bool parse(ifstream &inf);
  void print() const;
  void printQuarters() const;
};  // class Course

#endif	/* course_H */

