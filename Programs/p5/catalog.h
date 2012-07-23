// Eric Lowe
// catalog.h
// Usage Statement:
//
// Explanations

#ifndef CATALOG_H_
#define CATALOG_H_

#include <fstream>
#include <string>
#include "course.h"
using namespace std;

class Catalog
{
  Course *courses;
  int count;
  int size;
  void printPrerequisites(int pos, string prereqList);
  void resize();
public:
  Catalog();
  ~Catalog();
  
  void find();
  char getQuarters(const char *courseName) const;
  friend ifstream& operator>> (ifstream &inf, Catalog &rhs);
  void printAll();


};  // class Catalog


#endif /* CATALOG_H_ */
