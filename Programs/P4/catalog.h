// Eric Lowe and Rodolfo Hernandez
// catalog.h


#ifndef CATALOG_H_
#define CATALOG_H_

#include <dirent.h>
#include "course.h"

class Catalog {
  Course *courses;
  int count;
  int size;
  friend ifstream &operator>>(ifstream &inf, Catalog &rhs);
  void moreCourses();
public:
  Catalog();
  ~Catalog();
  Catalog& operator=(const Catalog &rhs);
  void findClass();
  void printMenu();
  void printPrereqs(int pos, char prereqList[]);
  void showAll();
};


#endif /* CATALOG_H_ */
