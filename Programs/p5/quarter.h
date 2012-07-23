// Eric Lowe
// quarter.h
// Usage Statement:
//
// Explanations

#ifndef QUARTER_H_
#define QUARTER_H_

#include <iostream>
using namespace std;


class Quarter
{
  char *season;
  int year;
  int courseCount;
  char **courses;
public:
  Quarter();
  Quarter(const char *seas, int y);
  ~Quarter();
  bool checkQuarter(char quarters) const;
  bool findCourse(const char* name) const;
  Quarter& operator= (const Quarter &rhs);
  bool operator== (const Quarter &rhs) const;
  Quarter& operator+= (const char *courseName);
  Quarter& operator-= (const char *courseName);
  friend istream& operator>> (istream &is, Quarter &rhs);
  friend ostream& operator<< (ostream &os, const Quarter &rhs);
  void printTime() const;
  void show() const;
private:

};



#endif /* QUARTER_H_ */
