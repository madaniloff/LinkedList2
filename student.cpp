//Methods and returns for the student class

#include <iostream>
#include <cstring>
#include "student.h"

using namespace std;

//Constructor
Student::Student(char* infname, char* inlname, int inid, float ingpa) {
  fname = infname;
  lname = inlname;
  id = inid;
  gpa = ingpa;
}
//Destructor
Student::~Student() {
  delete fname;
  delete lname;
}
//Return first name
char* Student::getfname() {
  return fname;
}
//Return last name
char* Student::getlname() {
  return lname;
}
//Return id
int Student::getid() {
  return id;
}
//Return GPA
float Student::getgpa() {
  return gpa;
}




