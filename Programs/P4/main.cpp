// Eric Lowe and Rodolfo Hernandez
// main.cpp
// prereqs.out
//
// Idea is to have Catalog object create the catalog
// which is then made available to user via menu choices.
// In other words, Catalog is built before the menu is called
// by the Catalog constructor.
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <sys/types.h>
#include "catalog.h"
#include "course.h"

using namespace std;

void readDir(Catalog &catalog); // Function readDir explores the directory

int main()
{
  int choice; // variable stores users menu choice
  Catalog myCatalog; // declares Catalog object
  
  do 
  {
    myCatalog.printMenu(); // calls menu function from Catalog object
    cin >> choice;
    
    if (choice != 0) 
    {
      switch (choice)
      {
        case 1:
          readDir(myCatalog); // Explore directory and fill Catalog
          myCatalog.findClass(); // calls find function
          break;
          
        case 2:
          readDir(myCatalog); // Explore directory and fill catalog
          myCatalog.showAll(); // Shows all courses
          break;
          
        case 3:
          cout << "Coming soon!\n\n"; // Will be the option to read schedules
          break;
          
        case 4:
          cout << "Coming soon!\n\n"; // Will be the option to edit schedules
          break;
          
        default: // if anything other than 0,1 or 2
          cout << "Choice must be between 0 and 2.\n";
          break;
        } // switch (choice)
      } // if (choice != 0)
  } while (choice != 0); // do-while

} // int main()

// This function is supposed to explore the exp_course_desc directory
// so that overloaded extraction operators can be used to read info
// from files.
void readDir(Catalog &catalog)
{
  char path[50] = "";
    
  DIR *dir = opendir("exp_course_desc"); // declares directory handle
    
  if(dir) // if directory exists
  {
    struct dirent *ent; // declares a struct from header file dirent.h
    while((ent = readdir(dir)) != NULL) // while reading from dir
    {
      if(strstr(ent->d_name, ".html")) // if file is an html file                                                 
      {
        strcpy(path, "exp_course_desc/"); // copy directory to string path
        strcat(path, ent->d_name); // copy filename to end of path
        ifstream inf(path); // open file

        if (!inf)
        {
          cout << "Couldn't open file " << path << "\n" << endl;
          exit(1);
        }
                         
       inf >> catalog; // Fill Catalog using overloaded extraction operator
      } // if(strstr(ent->d_name, ".html"))                                                                                      
    } // while((ent = readdir(dir)) != NULL)                                                                    
  } // if(dir)
  else
  {
    cout << "Error opening directory\n";
    return;
  } // else if directory can't be read
  return;
} // void readDir(Catalog &catalog)
