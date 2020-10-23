/*****************************************************************
//
//  NAME:        Robert Lemon
//
//  HOMEWORK:    project2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 18, 2020
//
//  FILE:        llist.h
//
//  DESCRIPTION:
//    A header file for the llist class.  It defines the class,
//    as well as the imported headers and macros.
//
//
****************************************************************/

/* includes */
#include "record.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

/* defines */
#define NAME_LENGTH 25
#define ADDRESS_LENGTH 80
#define FILENAME_LENGTH 16

/* classes*/
class llist
{
private:
    record *    start;
    char        filename[FILENAME_LENGTH];
    int         readfile();
    int         writefile();
    record *    reverse(record * );
    void        cleanup();

public:
    llist();
    llist(char[]);
    llist(const llist &);
    ~llist();
    int addRecord(int, char [ ],char [ ]);
    int printRecord(int);
    int modifyRecord(int, char [ ]);
    int deleteRecord(int);
    void reverse();
    int size();  // utility method to return the size of the list
    friend ostream & operator<<(ostream &, llist &);
    llist & operator=(const llist &);
};

