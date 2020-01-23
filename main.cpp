//This program creates a student list using linked lists and nodes
//First and last name, id, and gpa are all stored
//Author: Mark Daniloff
//1/8/2020

#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctype.h>
#include <cctype>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <iomanip>
#include "node.h"
#include "student.h"

using namespace std;

//Initialize functions
void addStudent(Node* &head, Node* temp, Node* temp2, Node* current, char* infname, char* inlname, int inid, float ingpa);
void printStudent(Node* &head, Node* next);
void delStudent(Node* &head, Node* current, Node* temp3, Node* temp4, int delid);
void avgStudent(Node* &head, Node* next, float avg, int count);

//Node at the beginning of the linked list
//Node* head = NULL;

int main() {
  //Initialize variables
  Node* head = NULL;
  Node* temp = NULL;
  Node* temp2 = NULL;
  Node* temp3 = NULL;
  Node* temp4 = NULL;
  float avg = 0;
  int count = 0;
  bool on = true;
  while (on == true) {
    char input[10];
    cout << "Enter ADD, PRINT, DELETE, AVERAGE, or QUIT" << endl;
    cin.get(input, 10);
    cin.ignore();
    //ADD
    if (strcmp(input, "ADD")==0) {
      //Ask user to input first and last names, id, and gpa
      char* infname = new char[30];
      char* inlname = new char[30];
      int inid;
      float ingpa;
      cout << "First name: " << endl;
      cin.get(infname, 30);
      cin.ignore();
      cout << "Last name: " << endl;
      cin.get(inlname, 30);
      cin.ignore();
      cout << "ID: " << endl;
      cin >> inid;
      cin.ignore();
      cout << "GPA: " << endl;
      cin >> ingpa;
      cin.ignore();
      //Add all of the fields to addStudent method
      addStudent(head, temp, temp2, head, infname, inlname, inid, ingpa);
      
    }
    //PRINT
    if (strcmp(input, "PRINT")==0) {
      printStudent(head, head);
    }
    //DELETE
    if (strcmp(input, "DELETE")==0) {
      cout << "Enter the ID that you want to delete" << endl;
      int delID;
      cin >> delID;
      cin.ignore();
      delStudent(head, head, temp3, temp4, delID);
      delID = 0;
    }
    //AVERAGE
    if (strcmp(input, "AVERAGE")==0) {
      avgStudent(head, head, avg, count);
      avg = 0;
      count = 0;
    }
    //QUIT
    if (strcmp(input, "QUIT")==0) {
      on = false;
    }
  }
}

//Function to add a student to the linked list
//I used some of the functionalities in Nicholas Fong's code, Period 1
void addStudent(Node* &head, Node* temp, Node* temp2, Node* current, char* infname, char* inlname, int inid, float ingpa) {
  Student* newStudent = new Student(infname, inlname, inid, ingpa);
  //If current (the first index) is empty
  if (current == NULL) {
    //Create a new head
    head = new Node(newStudent);
    //Set the student to the node at the head
    head->setStudent(newStudent);
  }
  //If the node after current is empty
  else if (current->getNext() == NULL && current == head) {
    //If current's ID is greater than the inputted id
    if (current->getStudent()->getid() > inid) {
      //Put the new student before the node
      temp = current;
      head = new Node(newStudent);
      head->setStudent(newStudent);
      head->setNext(temp);
    }
    //If current's ID is less than the inputted id
    if (current->getStudent()->getid() < inid) {
      //Put the new student after the node
      current->setNext(new Node(newStudent));
      current->getNext()->setStudent(newStudent);
    }
  }
  //If the next node isn't null
  else if (current->getNext() != NULL) {
    //If current's id is greater than the inid
    if (current->getStudent()->getid() > inid) {
      //Put newStudent before the node
      temp = current;
      head = new Node(newStudent);
      current->setStudent(newStudent);
      current->setNext(temp);
    }
    //If the current's gpa is smaller than the inid and the next node is larger
    else if (current->getStudent()->getid() < inid && current->getNext()->getStudent()->getid() > inid) {
      //Put newStudent in between the nodes
      Node* tempstudent = new Node(newStudent);
      tempstudent->setStudent(newStudent);
      temp = current->getNext();
      current->setNext(tempstudent);
      tempstudent->setNext(temp);
    }
    //If both the current and the next node's ID is smaller than the inid
    else if (current->getStudent()->getid() < inid && current->getNext()->getStudent()->getid() < inid) {
      //Call the function again and move forward one node
      addStudent(head, temp, temp2, current->getNext(), infname, inlname, inid, ingpa);
    }
  }
  //If current's next is NULL
  else if (current->getNext() == NULL) {
    //If current's id is less than the inid
    if (current->getStudent()->getid() < inid) {
      //Insert inid after it
      current->setNext(new Node(newStudent));
      current->getNext()->setStudent(newStudent);
    }
    //If current's id is more than the inid
    if (current->getStudent()->getid() > inid) {
      //Insert inid before it
      temp = current;
      current = new Node(newStudent);
      current->setStudent(newStudent);
      current->setNext(temp);
    }
  }
}

//Function to print out the contents of the linked list
void printStudent(Node* &head, Node* next) {
  //If the next node is the head
  if (next == head) {
    cout << "Students:" << endl;
    cout << "--------------------" << endl;
  }
  //If the next node in the linked list isn't empty
  if (next != NULL) {
    cout << "First name: " << next->getStudent()->getfname() << endl;
    cout << "Last name: " << next->getStudent()->getlname() << endl;
    cout << "ID: " << next->getStudent()->getid() << endl;
    cout << "GPA: " << std::fixed << std::setprecision(2) << next->getStudent()->getgpa() << endl;
    cout << "--------------------" << endl;
    //Use recursion to print out the next item in the linked list
    printStudent(head, next->getNext());
  }
}

//Function to delete a gpa from a linked list
//I also used some of Nicholas Fong's methods here
void delStudent(Node* &head, Node* current, Node* temp3, Node* temp4, int delid) {
  //If the next item in the linked list is empty
  if (head == NULL) {
    cout << "There are no ID's to delete!" << endl;
  }
  //If there is only one node in the list
  else if (current->getNext() == NULL) {
    //If delID matches the id of the head
    if (current->getStudent()->getid() == delid) {
      head = NULL;
      temp3 = current;
      delete temp3;
      cout << delid << " has been deleted!" << endl;
    }
    else {
      cout << "No ID match!" << endl;
    }
  }
  //If current is the second to last item
  else if (current->getNext() != NULL && current->getNext()->getNext() == NULL) {
    //If the next item after current equals delid
    if (current->getNext()->getStudent()->getid() == delid) {
      //Delete it
      temp3 = NULL;
      current->setNext(temp3);
      temp4 = current->getNext();
      delete temp3;
      cout << delid << " has been deleted!" << endl;
    }
    //If current's id equals delid
    else if (current->getStudent()->getid() == delid) {
      //Delete it 
      temp3 = NULL;
      temp4 = current->getNext();
      head = temp4;
      current->setNext(temp3);
      temp3 = current;
      delete temp3;
      cout << delid << " has been deleted!" << endl;
    }
    else {
      cout << "No ID match!" << endl;
    }
  }
  //If there are more than 3 nodes in the list
  else if ((current->getStudent()->getid() != delid) &&( current->getNext()->getNext() != NULL)) {
    //If the current's id matches delid
    if (current->getStudent()->getid() == delid) {
      //Sets head equal to current's next
      temp3 = current->getNext();
      head = temp3;
      temp4 = current;
      delete temp4;
    }
    //If current's next matches the delid
    else if (current->getNext()->getStudent()->getid() == delid) {
      temp3 = current->getNext()->getNext();
      temp4 = current->getNext();
      delete temp4;
      current->setNext(temp3);
    }
    //If neither current nor currents next match delid
    else if ((current->getStudent()->getid() != delid) && (current->getNext()->getStudent()->getid() != delid)) {
      //Use recursion and utilize the next node
      delStudent(head, head->getNext(), temp3, temp4, delid);
    }
    }
}

//Function to average gpa's of all students
void avgStudent(Node* &head, Node* next, float avg, int count) {
  //If the next node is the head
  if (next == head) {
    cout << "Average GPA:" << endl;
  }
  //if the next node in the linked list isn't empty
  if (next != NULL) {
    count++;
    //cout << next->getStudent()->getgpa() << endl;
    avg += next->getStudent()->getgpa();
    //Use recursion to get the averages from the other nodes
    avgStudent(head, next->getNext(), avg, count);
  }
  //If the next item is empty calculate the average and print it out
  if (next == NULL) {
    cout << std::fixed << std::setprecision(2) << avg/count << endl;
  }
}
