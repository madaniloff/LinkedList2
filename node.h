//raymond baartmans
//linked lists one
//node.h

#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>
#include "student.h"

using namespace std;

class Node{
 public:
  Node(Student*);//construct
  ~Node();//destruct
  void setStudent(Student*);//set the student
  Student* getStudent();//returns student pointer
  void setNext(Node* newNext);//sets the name
  Node* getNext();//get the next node in linked list
 private:
  Student* student;//Student node holds
  Node* next;//next node in linked list
};

#endif
