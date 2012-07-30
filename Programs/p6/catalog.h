// Eric Lowe and Rodolfo Hernandez
// catalog.h
// 

#ifndef catalog_H
#define	catalog_H

#include <string>
#include <fstream>
#include "list.h"
#include "course.h"

using namespace std;

class Catalog
{
  List <Course> courses;
  void printPrerequisites(const string &courseName, string & prereqList);
public:
  Catalog();
  ~Catalog();
  
  void find();
  short getQuarters(const string &courseName) const;
  friend ifstream& operator>> (ifstream &inf, Catalog &rhs);
  void printAll();


};  // class Catalog

#endif	/* catalog_H */

