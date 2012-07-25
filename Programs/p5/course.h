// Eric Lowe
// course.h
// Usage Statement:
//
// Explanations

#ifndef COURSE_H_
#define COURSE_H_

#include <fstream>
#include <string>
using namespace std;


class Course
{
  string name;
  string* prerequisites;
  int count;
  short quarters;
  void correctPrereqName(string& prereqName, const string& previous) const;
  void readQuarters();
  int readPrerequisite(char *ptr, int pos, string previous);
  void readPrerequisites(ifstream &inf);
public:
  Course();
  ~Course();
  int getCount() const;
  const string getName() const;
  const string getPrerequisite(int pos) const;
  short getQuarters() const;
  friend ifstream& operator>> (ifstream &inf, Course &rhs);
  Course& operator= (const Course &rhs);
  bool parse(ifstream &inf);
  void print() const;
  void printQuarters() const;
};  // class Course



#endif /* COURSE_H_ */

