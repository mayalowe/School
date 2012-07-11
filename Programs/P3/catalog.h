// Eric Lowe and Rodolfo Hernandez
// catalog.h

#ifndef p3_catalog_h
#define p3_catalog_h

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
  void openFile(const char *file);
  void printMenu();
  void showAll();
};

#endif
