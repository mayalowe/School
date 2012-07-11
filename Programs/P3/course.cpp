// Eric Lowe and Rodolfo Hernandez
// course.cpp
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include "course.h"

using namespace std;

// Course object constructor
Course::Course():name(NULL), count(0), p(0), quarters(0)
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
    return *this; // return current object
  
  if(name)
    delete[] name;
  
  if(rhs.name == NULL)
    name = NULL;
  else {
    name = new char[strlen(rhs.name) + 1];
    strcpy(name, rhs.name);
  } // else
  
  if(prereqs)
    delete[] prereqs;
  
  if(rhs.prereqs == NULL)
    prereqs = NULL;

  count = rhs.count;
  return *this;
} // Course& Course::operator=(const Course &rhs)

void Course::addPrereq(char *reqname)
{
  char **temp = new char*[count + 1];
  for(int i = 0; i < count; i++)
  { 
    temp[i] = prereqs[i];
  } // for(int i = 0; i < count; i++)
  
  delete[] prereqs;
  prereqs = temp;
  prereqs[count++] = new char[strlen(reqname) + 1];
  
  return;
}

// Function to return course name
const char * Course::getName() const
{
  return name;
} // const char * Courses::getName() const

// Function to return course prereqs
const char * Course::getPrereqs(int pos) const
{
  return prereqs[pos];
} // const char * Course::getPrereqs(int pos) const

// Function to parse files
void Course::parseFile(ifstream &inf)
{
  char line[1000], *ptr, *ptr2;
  char temp[25] = ""; // char array to hold name
  
  // Looks for course name
  do {
    inf.getline(line, 1000); 
  } while (!inf.eof() && strstr(line, "ECS") == NULL); // 
  
  // Gets full Course name from line
  ptr = strstr(line, "ECS");
  ptr2 = strtok(ptr, " ");
  strcat(temp, ptr2);
  strcat(temp, " ");
  ptr += 4;
  ptr2 = strtok(NULL, " ");
  strcat(temp, ptr2);
  name = new char[strlen(temp) + 1];
  strcpy(name, temp);
  
  readQuarters(line);
  // Call to read course prereqs
  readPrereqs(inf);
  return;
} // void Course::parseFile(ifstream &inf)

// Function to print out Course info
void Course::printFile() const
{
  int n;
  
  // print out course name
  cout << getName() << ": \n";
  
  // if course has prereqs, print prereqs sequentially
  if (count > 0)
  {
    for (n = 0; n < count; n++) 
    {
     cout << "Prereqs (temporary) " << getPrereqs(n) << "\n";
    } // for (n = 0; n < count; n++)
  } // if (count > 0)
  
  return;
} // void Course::printFile() const

// Function to print course quarters
void Course::printQuarters() const
{
  return;
} // void Course::printQuarters() const

// Function to parse Prereqs from line after finding line
void Course::readPrereq(char *line, int pos)
{
  int pos2;
  char reqname[100];

  while (!isdigit(line[p]) && (p < ((int)strlen(line))))
  {
     p++;
  } // while (!isalnum(line[pos] && line[pos]))
      
  if(!line[pos])
    return;
  
  for(pos2 = (p - 1); line[pos2] == ' '; pos2--)
  {
    if(line[pos2] == ' ')
      line[pos2] = '\0';
  } // for(pos2 = pos-1; line[pos2] == ' '; pos2--)
  
  for(pos2 = (p - 1);isalpha(pos2); pos2--)
  {
    strcpy(reqname, &line[pos2]);
  } // for(pos2=pos-1;isalpha(pos2); pos2--)
  
  for(pos2 = p; isalnum(line[pos2]); pos2++)
  {
    strcat(reqname, " ");
    strcat(reqname,&line[p]);
    p = pos2;
  } // for(pos2 = pos; isalnum(line[pos2]); pos2++)
  addPrereq(reqname);
  
  return;
} // int Course::readPrereq( char *line, int pos)

// Function to find prereq line in HTML file
void Course::readPrereqs(ifstream &inf)
{
  char line[1000], line2[1000], *ptr;
  
  // While not  EOF or on prereq line
  do {
    inf.getline(line, 1000);
  } while (!inf.eof() && strstr(line, "requisite") == NULL);  
  
  ptr = strstr(line, "requisite");
  if (!ptr) {
    return;
  } // if (!ptr)
  
  while (strstr(line, "</p>") == NULL)
  {
    inf.getline(line2, 1000);
    strcat(line, line2);
  } // while (strstr(line, "</p>") == NULL)
  
  // Call function to parse prereq line as long as line needs parsing
  
  //while(p < ((int)strlen(line)))
  //{
    //readPrereq(line, p);
  //} // while(pos < strlen(line))
   
  return;
} // void Course::readPrereqs(ifstream &inf)

// Function to read Quarters
void Course::readQuarters(char *line)
{
  
  return;
} // void Course::readQuarters(char *line)





