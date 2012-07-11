// Eric Lowe and Rodolfo Hernandez
// course.h
#ifndef p3_course_h
#define p3_course_h

#include <iostream>
#include <fstream>

using namespace std;

class Course {
    char *name;
    char **prereqs;
    int count;
    int p;
    char quarters;
    void addPrereq(char *reqname);
    void readPrereq(char *line, int pos);
    void readPrereqs(ifstream &inf);
    void readQuarters(char *line);
public:
    Course();
    ~Course();
    Course& operator=(const Course &rhs);
    const char * getName() const;
    const char * getPrereqs(int pos) const;
    void parseFile(ifstream &inf);
    void printFile() const;
    void printQuarters() const;
};

#endif
