// Eric Lowe and Rodolfo Hernandez
// main.cpp
// prereqs.out
// Idea is to have Catalog object create the catalog
// which is then made available to user via menu choices.
// In other words, Catalog is built before the menu is called
// by the Catalog constructor.
#include <iostream>
#include "catalog.h"
#include "course.h"

using namespace std;

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
          myCatalog.findClass(); // calls find function
          break;
          
        case 2:
          myCatalog.showAll(); // Shows all courses
          break;
          
        default: // if anything other than 0,1 or 2
          cout << "Choice must be between 0 and 2.\n";
          break;
        } // switch (choice)
      } // if (choice != 0)
  } while (choice != 0); // do-while

} // int main()