#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <cstring>

//Initializes methods and variables for the student class

using namespace std;

class Student {
public:
  Student(char*, char*, int, float);
  ~Student();
  char* getfname();
  char* getlname();
  int getid();
  float getgpa();
 private:
  char* fname;
  char* lname;
  int id;
  float gpa;
};


#endif
