// Eric Lowe
// course.cpp
// Usage Statement:
//
// Explanations

#include <fstream>
#include <cstring>
#include <iostream>
#include "course.h"
using namespace std;


Course::Course() : prerequisites(NULL), count(0), quarters(0)
{
  
}  // Course()



Course::~Course()
{ 
  if(prerequisites)
    delete [] prerequisites;
}  // ~Course()



void Course::correctPrereqName(string &prereqName, const string &previous) const
{
  if(prereqName.find("Math"))
    prereqName = "MAT";

  if(prereqName.find("ourse"))
    prereqName = "ECS";

  if(prereqName.find("Computer"))
    prereqName = "EEC";

  if(prereqName.find("Statistics"))
    prereqName = "STA";

  if(prereqName.find("Engineering"))
    prereqName = "ENG";

  if(prereqName.find("Science"))
    prereqName = "SCI";

  if(prereqName.find("Biology"))
    prereqName = "BIS";

  if(prereqName.find("Environmental"))
    prereqName = "ECI";

  if(prereqName.find("or") == 0)
    prereqName = previous;
} // correctPrereqName()


int Course::getCount() const
{
  return(count);
}  // getCount()
   

const string Course::getName() const
{
  return(name);
} // getName()


const string Course::getPrerequisite(int pos) const
{
  if(pos < count)
    return(prerequisites[pos]);
  
  cout << "Position exceeds count in getPrerequisite()\n";
  return(name.c_str());  // to avoid segfault 
}  // getPrerequisite()


short Course::getQuarters() const
{
  return(quarters);
} // getQuarters()


Course& Course::operator= (const Course &rhs)
{
  if(this == &rhs)
    return(*this);
  
  if(prerequisites)
    delete [] prerequisites;
  
  name = rhs.name;
  quarters = rhs.quarters;
  count = rhs.count;
  prerequisites = new string[rhs.count];
  
  for(int i = 0; i < count; i++)
  {
    prerequisites[i] = rhs.prerequisites[i];
  } // for each prerequisite

  return(*this);
}  // operator=


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
  rhs.readPrerequisites(inf);
  return(inf);
}  // operator>>


void Course::print() const
{
  cout << name << ": ";
  
  for(int i = 0; i < count - 1; i++)
    cout << prerequisites[i] << ", ";
  
  if(count > 0)
    cout << prerequisites[count - 1];
  
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
  
} //print()


int Course::readPrerequisite(char *ptr, int pos, string previous)
{
  int i, pos2;
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
  
  if((prereqName == "of ") == 0) // for ECS 192 unit limitation.
    return(pos2 + 1);
  
  prereqName += &ptr[pos];

  for(i = 0; i < count; i++)
    if((prereqName == prerequisites[i]) == 0)
      break;

  if(i == count)
  {
    string *temp = new string[count + 1];

    for(i = 0; i < count; i++)
      temp[i] = prerequisites[i];

    delete [] prerequisites;
    prerequisites = temp;
    
    prerequisites[count++] = prereqName;
  }  // if prereqName not in prerequisites
  
  return(pos2 + 1);
}  // readPrerequisite()


void Course:: readPrerequisites(ifstream &inf)
{
  string line, line2, previous = "";
  char *ptr, *ptr2;
  int pos = 0;
  
  do
  {
    getline(inf, line);
  } while(inf && line.find("rerequisite") == string::npos);
  
  if(line.find("rerequisite") == string::npos) // !inf)
    return;
  
  while(inf && line.find("</p>") == string::npos)
  {
    getline(inf, line2);
    line += line2;
  }  // while haven't reached </p> of prereqs paragraph
  
  ptr = strstr(line.c_str(), "rerequisite");
  ptr2 = strstr(ptr, "</p>");
  *ptr2 = '\0';  // terminate prerequisite line.  Needed for 92 and 98.
  
  while(ptr[pos])
  {
    while(ptr[pos] && !isdigit(ptr[pos]))
      pos++;

    if(isdigit(ptr[pos]))
      pos = readPrerequisite(ptr, pos, previous);
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



