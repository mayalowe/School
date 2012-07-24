// Author: Sean Davis
#ifndef QUARTER_H
#define	QUARTER_H

#include <iostream>
#include <string>
#include "list.h"
using namespace std;


class Quarter
{
  string season;
  int year;
  List<string> courses;
public:
  Quarter();
  Quarter(const string &seas, int y);
  Quarter(const Quarter &rhs);
  ~Quarter();
  bool checkQuarter(short quarters) const;
  bool findCourse(const string &name) const;
  Quarter& operator= (const Quarter &rhs);
  bool operator== (const Quarter &rhs) const;
  Quarter& operator+= (const string &courseName);
  Quarter& operator-= (const string &courseName);
  bool operator< (const Quarter &rhs) const;
  friend istream& operator>> (istream &is, Quarter &rhs);
  friend ostream& operator<< (ostream &os, const Quarter &rhs);
  
  void printTime() const;
  void show() const;
private:

};

#endif	/* QUARTER_H */

