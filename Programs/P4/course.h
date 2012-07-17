// Eric Lowe and Rodolfo Hernandez
// course.h

#ifndef COURSE_H_
#define COURSE_H_

#include <iostream>
#include <fstream>

using namespace std;

class Course {
    char *name;
    char **prereqs;
    int count;
    char quarters;
    friend ifstream& operator>>(ifstream &inf, Course &rhs);
    void addPrereqName(const char *prereqName);
    int readPrereq(char *line, int pos, char previous[]);
    void readPrereqs(ifstream &inf);
    void readQuarters();
  public:
    Course();
    ~Course();
    Course& operator=(const Course &rhs);
    int getCount() const;
    const char * getName() const;
    const char * getPrereq(int pos) const;
    bool parseFile(ifstream &inf);
    void printFile() const;
    void printQuarters() const;
};
#endif /* COURSE_H_ */
