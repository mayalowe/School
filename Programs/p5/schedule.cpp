//  Author: Sean Davis

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include "quarter.h"
#include "catalog.h"
#include "list.h"
#include "schedule.h"

using namespace std;

Schedule::Schedule():previousCourses(string()), quarters(Quarter()) 
{
}  // Schedule()




Schedule::~Schedule()
{
  
} // ~Schedule()


void Schedule::addPreviousCourse()
{
  
  string line;
  cout << "Course name to add: ";
  getline(cin, line);
  
  if(findCourse(line))
    return;
  
  previousCourses += line;
} // addPreviousCourse()


void Schedule::addQuarter(const Catalog &catalog)
{
  string season;
  int year;
  cout << "\nAdd Quarter\n";
  getQuarterTime(season, &year);
  Quarter quarter(season, year);
  quarter = quarters.find(Quarter(season, year));

  if(quarters.find(quarter) == quarter)
    cout << season << ' ' << year << " already exists.\n";
  else
  {
    quarters += quarter;
    editExistingQuarter(quarters.getSize() - 1, catalog);
  }
} // addQuarter()



void Schedule::edit(const Catalog &catalog)
{
  int choice;
  string name;
  
  if(studentName == "")
  {
    cout << "Student name: ";
    getline(cin, name);
    studentName = name;
  } // if name is NULL
  
  editPreviousCourses();
  editQuarters(catalog);
  
  do
  {
    cout << "Do you wish to save this schedule (0 = no, 1 = yes): ";
    cin >> choice;
  } while(choice < 0 || choice > 1);
  
  if(choice == 1)
  {
    name += ".csv";
    ofstream outf(name.c_str());
    outf << *this;
  }
} // edit()


void Schedule::editExistingQuarter(int pos, const Catalog &catalog)
{
  
  int choice;
  string courseName;
  short courseQuarters;
  
  do
  {
    cout << endl;
    quarters[pos].show();
    
    cout << "\n\nEdit Quarter Menu\n";
    cout << "0. Done\n";
    cout << "1. Add course.\n";
    cout << "2. Remove course.\n";
    cout << "\nYour choice: ";
    cin >> choice;
    cin.ignore(100, '\n');

    if(choice == 1 || choice == 2)
    {
      cout << "Course name: ";
      getline(cin, courseName);
    }

    switch(choice)
    {
      case 0: break;
      case 1: 
        courseQuarters = catalog.getQuarters(courseName);
        cout << courseName << endl;
        if(!quarters[pos].checkQuarter(courseQuarters))
        {
          cout << courseName << "is not offered that quarter.\n";
          break;
        } // if not offered that this quarter.
        
        if(!findCourse(courseName))
          quarters[pos] += courseName;
        break;
      case 2: quarters[pos] -= courseName; break;
      default: cout << "Choice must be between 0 and 2.\n";
    } // switch
  } while(choice != 0);
} // editExistingQuarter()


void Schedule::editPreviousCourses()
{
  int choice;
  
  do
  {
    cout << "\nPrevious Courses:\n";
    if(previousCourses.getSize() == 0)
      cout << "No previous courses.\n";
    else  // has some previous courses
      for(int i = 0; i < previousCourses.getSize(); i++)
      {
        cout << left << setw(8) << previousCourses[i];
        if(i % 8 == 0 && i != 0)
          cout << endl;
      }  // for each previous course

    cout << "\n\nPrevious Course Menu\n";
    cout << "0. Done\n";
    cout << "1. Add course\n";
    cout << "2. Remove course\n";
    cout << "\nYour choice: ";
    cin >> choice;
    cin.ignore(100, '\n');
    
    switch(choice)
    {
      case 0: break;
      case 1: addPreviousCourse(); break;
      case 2: removePreviousCourse(); break;
      default: cout << "Choice must be between 0 and 2.\n";
    } // switch
  } while(choice != 0);
  
} // editPreviousCourses()



void Schedule::editQuarter(const Catalog &catalog)
{
  string season;
  int year;
  cout << "Edit Quarter\n";
  getQuarterTime(season, &year);
  
  for(int i = 0; i < quarters.getSize(); i++)
    if(quarters[i] == Quarter(season, year))
    {
       editExistingQuarter(i, catalog);
       return;
    } // if found a match
  
  cout << season << ' ' << year << " does not exist.\n";
} // editQuarter();


void Schedule::editQuarters(const Catalog &catalog)
{
  int choice;
  
  do
  {
    cout << "Quarters\n";
  
    for(int i = 0; i < quarters.getSize(); i++)
    quarters[i].show();
     
    cout << "\n\nQuarter Menu\n";
    cout << "0. Done\n";
    cout << "1. Add quarter\n";
    cout << "2. Remove quarter\n";
    cout << "3. Edit quarter\n";
    cout << "\nYour choice: ";
    cin >> choice;
    cin.ignore(100, '\n');
    
    switch(choice)
    {
      case 0: break;
      case 1: addQuarter(catalog); break;
      case 2: removeQuarter(); break;
      case 3: editQuarter(catalog); break;
      default: cout << "Choice must be between 0 and 3.\n";
    } // switch
  } while(choice != 0);
} // editQuarters()




bool Schedule::findCourse(const string & name) const
{
  if(previousCourses.find(name) == name)
  {
    cout << name << " already is a previous course.\n";
     return true;
  } // if course already in previousCourses

  for(int i = 0; i < quarters.getSize(); i++)
    if(quarters[i].findCourse(name))
    {
      cout << name << " is already in ";
      quarters[i].printTime();
      return true;
    }
  
  return false;
} // findCourse()


void Schedule::getQuarterTime(string &season, int *year) const
{
  int seasonNum;
  
  do
  {
    cout << "Quarter season (1 = Fall, 2 = Winter, 3 = Spring): ";
    cin >> seasonNum;
    
    switch(seasonNum)
    {
      case 1: season = "Fall"; break;
      case 2: season = "Winter"; break;
      case 3: season = "Spring"; break;
      default: cout << "Season must be between 1 and 3.\n";
    } // switch
  } while(seasonNum < 1 || seasonNum > 3);
  
  cout << "Year: ";
  cin >> *year;
  cin.ignore(100, '\n');
} // getQuarterTime()

istream& operator>> (istream &is, Schedule &rhs)
{
  char line[1000], *ptr;
  is.getline(line, 1000);
  
  ptr = strtok(line, ",");
  rhs.studentName = ptr;
  int previousCourseCount = atoi(strtok(NULL, ","));
  int quarterCount = atoi(strtok(NULL, ","));
  is.getline(line, 1000);
  ptr = strtok(line, ",");
  
  for(int i = 0; i < previousCourseCount; i++)
  {
    rhs.previousCourses += ptr;
    ptr = strtok(NULL, ",");
  } // while more previous courses;
  
  Quarter quarter;
  
  for(int i = 0; i < quarterCount; i++)
  {
    is >> quarter;
    rhs.quarters += quarter;
  }  // for each quarter
  
  return is;
} // operator>>


ostream& operator<< (ostream &os, const Schedule &rhs)
{
  os << rhs.studentName << ',' 
    << rhs.previousCourses.getSize() << ',' << rhs.quarters.getSize() << endl;
  
  for(int i = 0; i < rhs.previousCourses.getSize(); i++)
    os << rhs.previousCourses[i] << ',';
  
  os << endl;

  
  for(int i = 0; i < rhs.quarters.getSize(); i++)
    os << rhs.quarters[i];
  
  return os;
} // operator<<


void Schedule::read()
{
  string name;
  cout << "Student name: ";
  getline(cin, name);
  name += ".csv";
  ifstream inf(name.c_str());
  if(!inf)
  {
    cout << name << " not found.\n";
    return;
  }
  
  inf >> *this;
  
  cout << "\nPrevious Courses:\n";
  if(previousCourses.getSize() == 0)
    cout << "No previous courses.\n";
  else  // has some previous courses
    for(int i = 0; i < previousCourses.getSize(); i++)
    {
      cout << left << setw(8) << previousCourses[i];
    
      if(i % 8 == 0 && i != 0)
        cout << endl;
    }  // for each previous course
  
  cout << "\nQuarters:\n";
  for(int i = 0; i < quarters.getSize(); i++)
    quarters[i].show();
}  // read()


void Schedule::removePreviousCourse()
{
  string line;
  cout << "Course name to remove: ";
  getline(cin, line);
  
  if(previousCourses.find(line) == line)
    previousCourses -= line;
  else  // course not found  
    cout << line << " is not a previous course.\n";
} // removePreviousCourse()


void Schedule::removeQuarter()
{
  string season;
  int year;
  cout << "Remove Quarter\n";
  getQuarterTime(season, &year);
  Quarter quarter(season, year);
  
  if(quarters.find(quarter) == quarter)
    quarters -= quarter;
  else // quarter not found
    cout << season << ' ' << year << " does not exist.\n";
} // removeQuarter()

