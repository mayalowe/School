// Eric Lowe and Rodolfo Hernandez
// main.cpp
// prereqs.out
// main function displays initial menu and searches exp_course_desc
// directory

#include <sys/types.h> 
#include <dirent.h> 
#include <string.h>
#include <iostream>
#include "catalog.h"
#include "schedule.h"


using namespace std;

void readCatalog(Catalog *catalog)
{
  char path[80];
  DIR *dir = opendir("exp_course_desc");
  
  if(dir) 
  { 
    struct dirent *ent; 

    while((ent = readdir(dir)) != NULL) 
    { 
      if (strstr(ent->d_name, ".html"))
      {
        strcpy(path, "exp_course_desc/");
        strcat(path, ent->d_name);
        ifstream inf(path);
        inf >> *catalog;
      }  // if the file ends with an html
    }  // while more files to read 
  }  // if there is a exp_course_desc directory
  else // no exp_course_desc directory found
    printf("Error opening directory\n"); 
} // readCatalog()


int main(void) 
{ 
  Catalog catalog;
  Schedule schedule;
  readCatalog(&catalog);
  int choice;
  
  do
  {
    cout << "\nMenu\n";
    cout << "0. Done.\n";
    cout << "1. Find a course.\n";
    cout << "2. Show all courses.\n";
    cout << "3. Read schedule.\n";
    cout << "4. Edit schedule.\n";
    cout << "\nYour choice: ";
    cin >> choice;
    cin.ignore(100, '\n');
    
    switch(choice)
    {
      case 0: 
        break;
        
      case 1: 
        catalog.find(); 
        break;
        
      case 2: 
        catalog.printAll(); 
        break;
        
      case 3: 
        schedule.read(); 
        break;
        
      case 4: 
        schedule.edit(catalog); 
        break;
        
      default: 
        cout << "Choice must be between 0 and 4.\n";
        break;
    }  // switch
  } while(choice != 0);
  
  return(0); 
}  //main() 
