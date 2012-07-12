// Eric Lowe
// catalog.h
// Usage Statement:
//
// Explanations

#ifndef CATALOG_H_
#define CATALOG_H_

#include <dirent.h>
#include "course.h"

class Catalog {
  Course *courses;
  int count;
  int size;
  void moreCourses();
public:
  Catalog();
  ~Catalog();
  void findClass();
  void printMenu();
  void printPrereqs(int pos, char prereqList[]);
  void showAll();
};


#endif /* CATALOG_H_ */
