// Eric Lowe and Rodolfo Hernandez
// course.cpp

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include "course.h"

using namespace std;

// Course object constructor
Course::Course():name(NULL), prereqs(NULL), count(0), quarters(0)
{
  
} // Course::Course()

// Course object destructor
Course::~Course()
{
  if(name) // if Course object has a name
    delete[] name;
  
  if(prereqs) // if Course object has prereqs
  {
    for(int i = 0; i < count; i++) // because it's a double pointer
    { 
      delete[] prereqs[i];
    } // for(int i = 0; i < count; i++)
    delete[] prereqs;
  } // if(prereqs)
} // Course::~Course()

// Course object copy operator
Course& Course::operator=(const Course &rhs)
{
  if(this == &rhs) // if identical
    return (*this); // return current object
  
  if(prereqs) // if Course object has prereqs
    {
      for(int i = 0; i < count; i++) // because it's a double pointer
      { 
        delete[] prereqs[i];
      } // for(int i = 0; i < count; i++)
      delete[] prereqs;
    } // if(prereqs)
  
  if(name)
    delete[] name;
  
  name = new char[strlen(rhs.name) + 1];
  strcpy(name, rhs.name);
  quarters = rhs.quarters;
  count = rhs.count;
  prereqs = new char*[rhs.count];
  
  for(int i = 0; i < count; i++)
  {
    prereqs[i] = new char[strlen(rhs.prereqs[i]) + 1];
    strcpy(prereqs[i], rhs.prereqs[i]);
  } // for(int i = 0; i < count; i++)
  
  return (*this);
} // Course& Course::operator=(const Course &rhs)

istream &operator>>(ifstream &inf, Course &rhs)
{
  return(inf);
} // istream &operator>>(istream &inf, Course &rhs)

int Course::getCount() const
{
  return (count);
} // int Course::getCount() const;


const char * Course::getName() const
{
  return (name);
} // const char * Course::getName() const;


const char * Course::getPrereq(int pos) const
{
  if(pos < count)
    return (prereqs[pos]);
  
  return (name);
} // const char * Course::getPrereq(int pos) const;


bool Course::parseFile(ifstream &inf)
{
  char line[1000], line2[1000], *ptr, *ptr2;
  // this looks for line with course name
  do
  {
    inf.getline(line, 1000);
  }while(inf && strstr(line, "ECS") == NULL);
  // this makes sure the entire line is grabbed
  while(inf && strstr(line, "</h") == NULL)
  {
    inf.getline(line2, 1000);
    strcat(line, line2);
  } // while(inf && strstr(line, "</h") == NULL)
  
  ptr = strstr(line, "ECS");
  
  if(!ptr)
    return (false);
  
  ptr2 = ptr + 5;
  strtok(ptr2, " ");
  name = new char [strlen(ptr) + 1];
  strcpy(name, ptr);
  readQuarters(); // gets quarters course is available
  readPrereqs(inf); // looks for prereq line
  return (true);
} // bool Course::parseFile(ifstream &inf);


void Course::printFile() const
{
  cout << name << ": ";
  
  for(int i = 0; i < count - 1; i++)
    cout << prereqs[i] << ", ";
  
  if(count > 0)
    cout << prereqs[count - 1];
  
  cout << endl;
  return;
} // void Course::printFile() const;


void Course::printQuarters() const
{
  cout << '(';
  // if offered in Fall
  if(quarters & 1)
    cout << 'I';
  // if offered in Winter
  if(quarters & 2)
  {
    if(quarters & 1)
      cout << ", II";
    else
      cout << "II";
  } // if(quarters & 2)
  // if offered in Spring
  if(quarters & 4)
  {
    if(quarters & 3)
      cout << ", III";
    else
      cout << "III";
  } // if (quarters & 4)
  
  cout << ')';
  return;
} // void Course::printQuarters() const;

void Course::addPrereqName(const char *prereqName)
{
  int i;
  
  for(i = 0; i < count; i++)
  {
    if(strcmp(prereqName, prereqs[i]) == 0)
      break;
  } // for(i = 0; i < count; i++)
  
  if(i == count)
  {
    char **temp = new char*[count + 1];
    
    for(i = 0; i < count; i++)
      temp[i] = prereqs[i];
    
    delete[] prereqs;
    prereqs = temp;
    prereqs[count] = new char[strlen(prereqName) + 1];
    strcpy(prereqs[count++], prereqName);
  } // if(i == count)
  
  return;
} // void Course::addPrereq(const char *prereqName);

int Course::readPrereq(char *line, int pos, char previous[])
{
  int pos2;
  char prereqName[30];
  
  for(pos2 = pos - 1; pos2 && line[pos2] == ' '; --pos2);
  
  if(!isalpha(line[pos2]))
    strcpy(prereqName, "ECS");
  else
  {
    line[pos2 + 1] = '\0';
    for(; pos2 && isalpha(line[pos2]); --pos2);
    strcpy(prereqName, &line[pos2 + 1]);
    //correctPrereqName(prereqName, previous);
  } // else
  
  strcpy(previous, prereqName);
  strcat(prereqName, " ");
  for(pos2 = pos + 1; line[pos2] && isalnum(line[pos2]); pos2++);
  line[pos2] = '\0';
  
  if(strcmp(prereqName, "of ") == 0)
    return (pos2 + 1);
  
  strcat(prereqName, &line[pos]);
  addPrereqName(prereqName);
  
  return (pos2 + 1);
} // int Course::readPrereq(char *line, int pos, char previous[]);


void Course::readPrereqs(ifstream &inf)
{
  char line[1000], line2[1000], *ptr, *ptr2, previous[20] = "";
  int pos = 0;
  
  do
  {
    inf.getline(line, 1000);
  } while(inf && strstr(line, "requisite") == NULL);
  
  if(strstr(line, "requisite") == NULL)
    return;
  
  while(inf && strstr(line, "</p") == NULL)
  {
    inf.getline(line2, 1000);
    strcat(line, line2);
  } // while(inf && strstr(line, "</p>") == NULL)
  
  ptr = strstr(line, "requisite");
  ptr2 = strstr(ptr, "</p>");
  *ptr2 = '\0';
  
  while(ptr[pos])
  {
    while(ptr[pos] && !isdigit(ptr[pos]))
      pos++;
    
    if(isdigit(ptr[pos]))
      pos = readPrereq(ptr, pos, previous);
  } // while(ptr[pos])
  return;
} // void Course::readPrereqs(ifstream &inf);

void Course::readQuarters()
{
  char *ptr, *ptr2;
  
  strtok(NULL, ")");
  ptr = strtok(NULL, "<");
  
  if((ptr2 = strstr(ptr, "III")) != NULL)
  {
    quarters = 4;
    *ptr2 = '\0';
  } // if((ptr2 = strstr(ptr, "III")) != NULL)
  
  if((ptr2 = strstr(ptr, "II")) != NULL)
  {
    quarters += 2;
    *ptr2 = '\0';
  } // if((ptr2 = strstr(ptr, "II")) != NULL)
  
  if(strstr(ptr, "I"))
    quarters += 1;
  return;
} // void Course::readQuarters();
