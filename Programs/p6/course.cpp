// Eric Lowe and Rodolfo Hernandez
// course.cpp
// 

#include <fstream>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdlib>
#include "course.h"
#include "prereq.h"
#include "flexprereq.h"
using namespace std;


Course::Course() :  prerequisites(PrereqPtr()), quarters(0)
{
  
}  // Course()


Course::Course(const string &nam) : name(nam), prerequisites(NULL), 
  quarters(0)
{
}  // Course()


Course::Course(const Course &course) : name(course.name),  
  prerequisites(course.prerequisites), quarters(course.quarters)
{
}  // Course copy constructor


Course::~Course()
{
}  // ~Course()


void Course::addPrereqName(const string &prereqName)
{
  PrereqPtr prereqPtr(new Prereq(prereqName));
  
  if(prerequisites.find(prereqPtr) == PrereqPtr())
  {
    prerequisites += PrereqPtr(new Prereq(prereqName));
  }
} // addPrereqName()


bool Course::checkFlexPrereq(const string &line, const string &prereqName, 
  FlexPrereq **flexPrereqPtr)
{
  int pos = line.find("or ");
  
  if(pos < 5 && pos >= 0) // "or" soon
  {
    if(*flexPrereqPtr == NULL)
    {
      *flexPrereqPtr = new FlexPrereq(prereqName);
    }
    else // already started a flexPrereq
    {
      **flexPrereqPtr += prereqName;
    }
    return true;
  } // "or" follows
  else // no or nearby
    if(*flexPrereqPtr != NULL)
    {
      **flexPrereqPtr += prereqName;
      prerequisites += PrereqPtr(*flexPrereqPtr);
      *flexPrereqPtr = NULL;
      return true;
    } // if flexPrereqPtr exists
 
  return false;
}  // checkFlexPrereq()


void Course::correctPrereqName(string &prereqName, const string &previous) const
{
  if(prereqName.find("Math") != string::npos)
    prereqName = "MAT";

  if(prereqName.find("ourse") != string::npos)
    prereqName = "ECS";

  if(prereqName.find("Computer") != string::npos)
    prereqName = "EEC";

  if(prereqName.find("Statistics") != string::npos)
    prereqName = "STA";

  if(prereqName.find("Engineering") != string::npos)
    prereqName = "ENG";

  if(prereqName.find("Science") != string::npos)
    prereqName = "SCI";

  if(prereqName.find("Biology") != string::npos)
    prereqName = "BIS";

  if(prereqName.find("Environmental") != string::npos)
    prereqName = "ECI";

  if(prereqName == "or")
    prereqName = previous;
 }  // correctPrereqName()



int Course::getSize() const
{
  return prerequisites.getSize();
}  // getSize()
   

const string& Course::getName() const
{
  return name;
} // getName()


const string& Course::getPrerequisite(int pos) const
{
  if(pos < prerequisites.getSize())
    return prerequisites[pos]->getName();
  
  cout << "Position exceeds count in getPrerequisite()\n";
  return name;  // to avoid segfault 
}  // getPrerequisite()


short Course::getQuarters() const
{
  return quarters;
} // getQuarters()


ifstream& operator>> (ifstream &inf, Course &rhs)
{
  char line[1000], line2[1000], *ptr, *ptr2;
  
  do
  {
    inf.getline(line, 1000);
  } while(inf && strstr(line, "ECS") == NULL);
  
  while(inf && strstr(line, "</h") == NULL)
  {
    inf.getline(line2, 1000);
    strcat(line, line2);
  }  // while haven't reached </h
  
  ptr = strstr(line, "ECS");
  
  if(!ptr)  // no ECS
    cout << "Bad file\n";
  
  ptr2 = ptr + 5;
  strtok(ptr2, " ");
  rhs.name = ptr;
  rhs.readQuarters();
  if(rhs.name == "ECS 30")
    cout << rhs.name << endl;
  rhs.readPrerequisites(inf);
  return inf;
}  // operator>>


Course& Course::operator= (const Course &rhs)
{
  if(this == &rhs)
    return *this;
  
  name = rhs.name;
  quarters = rhs.quarters;
  prerequisites = rhs.prerequisites;
  return *this;
}  // operator=

bool Course::operator< (const Course &rhs) const
{
  string dept, rhsDept, courseStr;
  int pos, courseNum, rhsCourseNum;
  char courseLetter, rhsCourseLetter;
  pos = name.find(" ");
  dept = name.substr(0, pos);
  courseStr = name.substr(pos);
  courseNum = atoi(courseStr.c_str());
  pos = rhs.name.find(" ");
  rhsDept = rhs.name.substr(0, pos);
  courseStr = rhs.name.substr(pos);
  rhsCourseNum = atoi(courseStr.c_str());
  courseLetter = name[name.size() - 1];
  rhsCourseLetter = rhs.name[rhs.name.size() - 1];
  
  if(dept != rhsDept)
    return dept < rhsDept;
  
  if(courseNum != rhsCourseNum)
    return courseNum < rhsCourseNum;
  
  return courseLetter < rhsCourseLetter;
} // operator<

/*
bool Course::parse(ifstream &inf)
{
  char line[1000], line2[1000], *ptr, *ptr2;
  
  do
  {
    inf.getline(line, 1000);
  } while(inf && strstr(line, "ECS") == NULL);
  
  while(inf && strstr(line, "</h") == NULL)
  {
    inf.getline(line2, 1000);
    strcat(line, line2);
  }  // while haven't reached </h
  
  ptr = strstr(line, "ECS");
  
  if(!ptr)  // no ECS
    return false;
  
  ptr2 = ptr + 5;
  strtok(ptr2, " ");
  name = ptr;
  readQuarters();
  cout << name << "$" << endl;
  readPrerequisites(inf);
  return true;
}  // parse()
*/

void Course::print() const
{
  cout << name << ": ";
  
  for(int i = 0; i < prerequisites.getSize() - 1; i++)
    cout << prerequisites[i] << ", ";
  
  if(prerequisites.getSize() > 0)
    cout << prerequisites[prerequisites.getSize() - 1];
  
  cout << endl;
} //print()


void Course::printQuarters() const
{
  cout << '(';
  
  if(quarters & 1)
    cout << 'I';
  
  if(quarters & 2)
  {
    if(quarters & 1)
      cout << ", II";
    else
      cout << "II";
  } // if Winter quarter
  
  if(quarters & 4)
  {
    if(quarters & 3)
      cout << ", III";
    else
      cout << "III";
  } // if Spring quarter
  
  cout << ')';
} //printQuarters()




int Course::readPrerequisite(char *ptr, int pos, string &previous, 
  FlexPrereq **flexPrereqPtr)
{
  int pos2;
  string prereqName;
  
  for(pos2 = pos - 1; pos2 && ptr[pos2] == ' '; --pos2);


  if(!isalpha(ptr[pos2]))
    prereqName = "ECS";
  else  // department name precedes number
  {
    ptr[pos2 + 1] = '\0';
    for( ;pos2 && isalpha(ptr[pos2]); --pos2);
    prereqName = &ptr[pos2 + 1];
    correctPrereqName(prereqName, previous);
  } // else previous char was a space
  
  previous = prereqName;
  prereqName += " ";
  for(pos2 = pos + 1; ptr[pos2] && isalnum(ptr[pos2]); pos2++);
  ptr[pos2] = '\0';
  
  if(prereqName.find("of ") != string::npos) // for ECS 192 unit limitation.
    return pos2 + 1;
  
  prereqName += &ptr[pos];
  string lineStr = &ptr[pos2 + 1];
  if(!checkFlexPrereq(lineStr, prereqName, flexPrereqPtr)) 
    addPrereqName(prereqName);
  return pos2 + 1;
}  // readPrerequisite()


void Course:: readPrerequisites(ifstream &inf)
{
  char line[1000], line2[1000], *ptr, *ptr2;
  int pos = 0;
  string previous;
  FlexPrereq *flexPrereqPtr = NULL;
  
  do
  {
    inf.getline(line, 1000);
  } while(inf && strstr(line, "rerequisite") == NULL);
  
  if(strstr(line, "rerequisite") == NULL) // !inf)
    return;
  
  while(inf && strstr(line, "</p>") == NULL)
  {
    inf.getline(line2, 1000);
    strcat(line, line2);
  }  // while haven't reached </p> of prereqs paragraph
  
  ptr = strstr(line, "rerequisite");
  ptr2 = strstr(ptr, "</p>");
  *ptr2 = '\0';  // terminate prerequisite line.  Needed for 92 and 98.
  
  while(ptr[pos])
  {
    while(ptr[pos] && !isdigit(ptr[pos]))
      pos++;

    if(isdigit(ptr[pos]))
      pos = readPrerequisite(ptr, pos, previous, &flexPrereqPtr);
  } // while haven't reached end of line
} // readPrerequisites()


void Course::readQuarters()
{
  char *ptr, *ptr2;
  
  strtok(NULL, ")");
  ptr = strtok(NULL, "<");
  
  if((ptr2 = strstr(ptr, "III")) != NULL)
  {
    quarters = 4;
    *ptr2 = '\0';
  }  // if Spring
  
  if((ptr2 = strstr(ptr, "II")) != NULL)
  {
    quarters += 2;
    *ptr2 = '\0';
  } // if Winter
  
  if(strstr(ptr, "I"))
    quarters += 1;
} // readQuarters()
