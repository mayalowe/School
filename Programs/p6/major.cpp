// Eric Lowe and Rodolfo Hernandez
// major.cpp
//

#include <fstream>
#include <cstring>
#include "major.h"
#include "schedule.h"
#include "quarter.h"
#include "list.h"

using namespace std;


void Major::save()
{
  const char *prep[5] = {"ECS 20", "ECS 30", "ECS 40", "ECS 50", "ECS 60"};
  const char *core[5] = {"ECS 120", "ECS 122A", "ECS 140A", "ECS 150", "ECS 154A"};
  const char *electives2[32] = {"ECS 122B", "ECS 124", "ECS 129", "ECS 130",
    "ECS 132", "ECS 140B",  "ECS 142", "ECS 145",  "ECS 152A",  "ECS 152B",
    "ECS 152C", "ECS 153", "ECS 154B", "ECS 156", "ECS 158", "ECS 160", 
    "ECS 163", "ECS 165A", "ECS 165B", "ECS 170", "ECS 173", "ECS 175",
    "ECS 177", "ECS 178", "ECS 188", "ECS 189", "ECS 192", "ECS 199", 
    "ECS 193A", "ECS 193B", "EEC 180A", "EEC 180B"};
  const char *required[16] = {"STA 131A", "MAT 25", "MAT 108", "MAT 115A", "MAT 115B",
    "MAT 125A", "MAT 125B", "MAT 135A", "MAT 141", "MAT 145", "MAT 147",
    "MAT 148", "MAT 150A", "MAT 150B", "MAT 150C", "MAT 160"};
  
  for(int i = 0; i < 5; i++)
    strcpy(prepatories[i], prep[i]);
  
  for(int i = 0; i < 5; i++)
    strcpy(cores[i], core[i]);
  
  for(int i = 0; i < 32; i++)
    strcpy(electives[i], electives2[i]);
  
  for(int i = 0; i < 16; i++)
    strcpy(requiredElectives[i], required[i]);
  
  ofstream outf("major.dat", ios::binary);
  outf.write((char*) this, sizeof(Major));
  outf.close();
}  // save()





