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
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//    A file that contains the llist class functions and friend functions.
//    These functions are used to construct, destruct, and edit linked lists.
//
//
****************************************************************/

/* includes */
#include "llist.h"

/*****************************************************************
//
//  FUNCTION NAME: default constructor
//
//  DESCRIPTION:   The default constructor that is called when a new
//                 instance of the llist class is made.  It initializes
//                 the class variables and reads the database from the 
//                 "database.txt" file.
//
//  PARAMETERS:    none
//
//  RETURN VALUES: none
//
****************************************************************/

llist::llist()
{

    /* print debug info */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE=======================\n\n";
        cout << "\t  Entered llist default constructor\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\tnone\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* initialize class variables */

    this->start = NULL;
    strcpy(this->filename, "database.txt");

    /* read database from file */

    readfile();
}

/*****************************************************************
//
//  FUNCTION NAME: overloaded constructor
//
//  DESCRIPTION:   This is the overloaded constructor for the llist class.
//                 Whenever a new instance of the class is created with a 
//                 filename parameter, this is called.  It initializes the
//                 class variables, checks the parameter quality, then reads
//                 the database from the file.
//
//  PARAMETERS:    none
//
//  RETURN VALUES: none
//
****************************************************************/

llist::llist(char dataFileName[])
{

    /* print debug info */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE=======================\n\n";
        cout << "\t  Entered llist overloaded constructor\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\tdataFileName[]: " << dataFileName << "\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* initialize class variables */

    this->start = NULL;

    if ( strlen(dataFileName) > 0 && strlen(dataFileName) < FILENAME_LENGTH )
    {
        strcpy(this->filename, dataFileName);
    }
    else
    {
        strcpy(this->filename, "database.txt");
    }

    /* read database from file */

    readfile();
}

/*****************************************************************
//
//  FUNCTION NAME: copy constructor
//
//  DESCRIPTION:   The copy constructor for the llist class.  If an 
//                 instance of this class is initialized to another 
//                 instance, this constructor is called.  It initializes
//                 the class variables, then allocates a copy of the list
//                 in the original object.
//
//  PARAMETERS:    original is a reference to the original object.
//
//  RETURN VALUES: none
//
****************************************************************/

llist::llist(const llist & original)
{
    record* node = original.start;

    /* print debug info */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE=======================\n\n";
        cout << "\t  Entered llist copy constructor\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\tobject reference\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* initialize class variables */

    strcpy(this->filename, original.filename);
    this->start = NULL;

    /* allocate and populate copy of original list */

    while ( node != NULL )
    {
        this->addRecord(node->accountno, node->name, node->address); 
        node = node->next;
    }

}

/*****************************************************************
//
//  FUNCTION NAME: destructor
//
//  DESCRIPTION:   The destructor for the llist class.  When an instance
//                 of the class is removed from memory, this is called.
//                 This function writes the current database to filename,
//                 then unallocates the list.
//
//  PARAMETERS:    none
//
//  RETURN VALUES: none
//
****************************************************************/

llist::~llist()
{

    /* print debug info */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE=======================\n\n";
        cout << "\t  Entered llist destructor\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\tnone\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* write database to file */

    writefile();

    /* unallocate list memory */

    cleanup();
}

/*****************************************************************
//
//  FUNCTION NAME: overloaded operator<<
//
//  DESCRIPTION:   This is the overloaded operator<< for the llist class.
//                 This function allows an object's entire list to be printed
//                 using the operator<<, replacing the printAllRecords function.
//
//  PARAMETERS:    out is a reference to an output stream.
//                 list is a reference to an llist object.
//
//  RETURN VALUES: Returns a reference to an output stream.
//
****************************************************************/

ostream & operator<<(ostream & out, llist & list)
{
    int i;
    int recordCounter = 0;

    record* node = list.start;

    /* print debug info */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE=======================\n\n";
        cout << "\t  Entered llist overloaded operator<<\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\toutput stream\n";
        cout << "\t\tobject reference\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* traverse through list, printing all records */

    while ( node != NULL )
    {
        i = 0;

        /* print accountno and name */
        
        out << "\nAccount Number: \t" << (*node).accountno << '\n';
        out << "Name:\t\t\t" << (*node).name << '\n';
        out << "Address\t\t\t";

        /* print address */

        while ( (*node).address[i] != '\0' )
        {
            out << (*node).address[i];
            if ( (*node).address[i++] == '\n' )
            {
                out << "\t\t\t";
            }
        }
        out << "\n\n";

        /* increment node */

        node = (*node).next;
        recordCounter++;
    }

    /* append record count to output */

    if ( recordCounter == 1 )
    {
        out << "\nThere is 1 record currently in the database.\n\n";
    }
    else
    {
        out << "\nThere are " << recordCounter << " records currently in the database.\n\n";
    }

    return out;
}

/*****************************************************************
//
//  FUNCTION NAME: overloaded operator=
//
//  DESCRIPTION:   The overloaded assignment operator for the llist class.
//                 This is called whenever one llist object is assigned to
//                 another llist object.  This copies the variables from the
//                 source object to the destination object, allocating memory
//                 for a copy of the source list within the destination object.
//
//  PARAMETERS:    original is a reference to an llist object.
//
//  RETURN VALUES: Returns a reference to an llist object.
//
****************************************************************/

llist & llist::operator=(const llist & original)
{
    record* node = original.start;

    /* print debug info */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE=======================\n\n";
        cout << "\t  Entered llist overloaded operator=\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\tobject reference\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* initialize class variables */

    strcpy(this->filename, original.filename);
    this->start = NULL;

    /* allocate and populate copy of original list */

    while ( node != NULL )
    {
        this->addRecord(node->accountno, node->name, node->address); 
        node = node->next;
    }

    return *this;
}

/*****************************************************************
//
//  FUNCTION NAME: addRecord
//
//  DESCRIPTION:   A database function that, given an account number, name, and address,
//                 creates a new node that's populated with the parameter information
//                 and links it to the end of the database.  It updates the start
//                 pointer for the database if you add to an empty linked list.
//
//  PARAMETERS:    int accountNo is the user-entered account number.
//                 char name[] is the user-entered name.
//                 char address[] is the user-entered address.
//
//  RETURN VALUES: Returns 0 if record added.
//                 Returns -1 if record wasn't added.
//
****************************************************************/

int llist::addRecord(int accountNo, char name[], char address[])
{
    int returnValue;

    record *newNode;
    record *tempNode;

    /* print debug information for function call */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE=======================\n\n";
        cout << "\t  Entered 'addRecord' function\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\taccountNo: " << accountNo << '\n';
        cout << "\t\tname: " << name << '\n';
        cout << "\t\taddress: " << address << "\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* Create a new node */

    returnValue = -1;
    newNode = new record;

    if (newNode != NULL )
    {
        returnValue = 0;

        (*newNode).accountno = accountNo;
        strcpy((*newNode).name, name);
        strcpy((*newNode).address, address);
        (*newNode).next = NULL;

        /* Update start pointer if list is empty */

        if ( this->start == NULL )
        {
            this->start = newNode;
        }

        /* Update linked list if not empty */

        else
        {
            tempNode = this->start;

            while ( (*tempNode).next != NULL )
            {
                tempNode = (*tempNode).next;
            }

            (*tempNode).next = newNode;
        }
    }

    return returnValue;
}

/*****************************************************************
//
//  FUNCTION NAME: printRecord
//
//  DESCRIPTION:   A database function that iterates through the linked list and
//                 prints all records with a given account number.
//
//  PARAMETERS:    int accountNo is the user-entered account number to print.
//
//  RETURN VALUES: Returns -1 if database is empty.
//                 Otherwise, returns the amount of records read (0 or positive int).
//
****************************************************************/

int llist::printRecord(int accountNo)
{
    int i;
    int returnValue;

    record *node;

    cout << "\n===============================================================================\n\n";

    /* print debug information for function call */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE========================\n\n";
        cout << "\t  Entered 'printRecord' function\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\taccountNo: " << accountNo << "\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* Initialize variables */

    returnValue = 0;
    node = this->start;

    /* check if database is empty */

    if ( this->start == NULL )
    {
        returnValue = -1;
    }

    /* iterate through the databse */

    while ( node != NULL )
    {

        /* print all records with matching account numbers */

        if ( (*node).accountno == accountNo )
        {
            i = 0;

            cout << "\nAccount Number: \t" << (*node).accountno << '\n';
            cout << "Name:\t\t\t" << (*node).name << '\n';
            cout << "Address:\t\t";

            while ( (*node).address[i] != '\0' )
            {
                cout << (*node).address[i];
                if ( (*node).address[i++] == '\n' )
                {
                    cout << "\t\t\t";
                }
            }

            cout << "\n\n";

            returnValue++;
        }

        node = (*node).next;
    }

    return returnValue;
}

/*****************************************************************
//
//  FUNCTION NAME: modifyRecord
//
//  DESCRIPTION:   A database function that iterates through the database and updates the
//                 address of all records that match a user-specified account number.
//
//  PARAMETERES:   int accountNo is the user-specified account number.
//                 char address[] is the user-specified new address.
//
//  RETURN VALUES: Returns -1 if the database is empty.
//                 Otherwise, returns the number of records modified (0 or a positive int).
//
****************************************************************/

int llist::modifyRecord(int accountNo, char address[])
{
    int returnValue;

    record *node;

    /* print debug information for function call */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE========================\n\n";
        cout << "\t  Entered 'modifyRecord' function\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\taccountNo: " << accountNo << "\n";
        cout << "\t\taddress: " << address << "\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* initialize variables */

    returnValue = 0;
    node = this->start;

    if ( this->start == NULL )
    {
        returnValue = -1;
    }

    /* iterate through the database */

    while ( node != NULL )
    {

        /* modify all records with matching account numbers */

        if ( (*node).accountno == accountNo )
        {
            strcpy((*node).address, address);
            returnValue++;
        }

        node = (*node).next;
    }

    return returnValue;
}

/*****************************************************************
//
//  FUNCTION NAME: deleteRecord
//
//  DESCRIPTION:   A database function that iterates through the entire database and
//                 deletes all records with a user-specified account number.
//
//  PARAMETERS:    int accountNo is the user-specified account number.
//
//  RETURN VALUES: Returns -1 if database is empty.
//                 Otherwise, returns the amount of records deleted (0 or positive int).
//
****************************************************************/

int llist::deleteRecord(int accountNo)
{
    int returnValue;

    record *previousNode;
    record *currentNode;
    record *nextNode;

    /* print debug information for function call */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE========================\n\n";
        cout << "\t  Entered 'deleteRecord' function\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\taccountNo: " << accountNo << "\n";
        cout << "\t====================================\n\n";
    #endif

    /* initialize all variables */

    returnValue = -1;
    previousNode = NULL;
    currentNode = this->start;

    if ( this->start != NULL )
    {
        returnValue = 0;
        nextNode = (*currentNode).next;
    }

    /* iterate through entire database */

    while ( currentNode != NULL )
    {

        /* delete record if the account number matches parameter */

        if ( accountNo == (*currentNode).accountno )
        {
            returnValue++;
            delete currentNode;

            /* if head got deleted */

            if ( this->start == currentNode )
            {
                this->start = nextNode;
            }

            /* if tail got deleted */

            else if ( nextNode == NULL )
            {
                (*previousNode).next = NULL;
            }

            /* if middle got deleted */

            else
            {
                (*previousNode).next = nextNode;
            }
        }

        else
        {
            previousNode = currentNode;
        }

        currentNode = nextNode;

        if ( currentNode != NULL )
        {
            nextNode = (*currentNode).next;
        }

    }

    return returnValue;
}

/*****************************************************************
//
//  FUNCTION NAME: readfile
//
//  DESCRIPTION:   A database function that is run upon successful startup of the
//                 program.  It scans a text file, adding records stored on it to the
//                 database.
//
//  PARAMETERS:    none
//
//  RETURN VALUES: Returns -1 if no file found.
//                 Otherwise, returns the amount of records scanned and added (0 or positive int).
//
****************************************************************/

int llist::readfile()
{
    bool continueReading;

    int i;
    int accountno;
    int lineNumber;
    int returnValue;

    char ch;
    char address[ADDRESS_LENGTH];
    char name[NAME_LENGTH];

    /* print debug information for function call */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE========================\n\n";
        cout << "\t  Entered 'readfile' function\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\tnone\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* initialize variables */

    continueReading = true;
    lineNumber = 0;
    returnValue = 0;

    ifstream file;
    file.open(filename);

    if (!file)
    {
        returnValue = -1;;
        this->start = NULL;
    }

    while (continueReading && returnValue > -1)
    {

        /* process next line in file */

        switch (lineNumber)
        {

            /* get account number */

            case 0:

                if ( !(file >> accountno) )
                {
                    cin.clear();
                    continueReading = false;
                }
                else
                {
                    do // clear line
                    {
                        file.get(ch);
                    }
                    while ( ch != '\n' );
                }
                break;

            /* get name */

            case 1:

                i = 0;
                file.get(ch);

                while (ch != '\n' && i < NAME_LENGTH - 1)
                {
                    if ( ch != '\t' ) // ignore tabs in names
                    {
                        name[i++] = ch;
                    }
                    file.get(ch);
                }

                name[i] = '\0';

                while (ch != '\n') // clear line
                {
                    file.get(ch);
                }

                break;

            /* get address */

            case 2:

                i = 0;
                file.get(ch);

                while (ch != '!' && i < ADDRESS_LENGTH - 1)
                {
                    address[i++] = ch;
                    file.get(ch);
                }

                address[i] = '\0';

                while ( ch != '\n' ) // clear line
                {
                    file.get(ch);
                }

                break;

            default:;
        }

        /* increment numcust */

        if (lineNumber == 2)
        {
            addRecord(accountno, name, address);
            returnValue++;
        }

        /* increment line being processed */

        lineNumber = (lineNumber + 1) % 3;

    }

    /* close file */

    if (returnValue != -1)
    {
        file.close();
    }

    return returnValue;
}

/*****************************************************************
//
//  FUNCTION NAME: writefile
//
//  DESCRIPTION:   A database function that is run upon successful completion of the
//                 program.  It writes the current database to a text file to save it.
//
//  PARAMETERS:    none
//
//  RETURN VALUES: Returns -1 if file cannot be open or made.
//                 Otherwise, returns number of records written to file (0 or positive int).
//
****************************************************************/

int llist::writefile()
{
    int returnValue;

    record *node;

    /* print debug information for function call */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE========================\n\n";
        cout << "\t  Entered 'writefile' function\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\tnone\n\n";
        cout << "\t====================================\n\n";
    #endif

    returnValue = 0;

    /* write to file */

    ofstream file;
    file.open(filename);

    if (!file)
    {
        returnValue = -1;
    }
    else
    {
        node = this->start;

        while ( node != NULL )
        {
            file << (*node).accountno << '\n';
            file << (*node).name << '\n';
            file << (*node).address << "!\n";
            node = (*node).next;
            returnValue++;
        }

        file.close();
    }

    return returnValue;
}

/*****************************************************************
//
//  FUNCTION NAME: cleanup
//
//  DESCRIPTION:   A database function that is called after writefile saves the
//                 database.  It frees all space allocated for the records, cleaning
//                 up after the program. It reassigns linked list head to NULL.
//
//  PARAMETERS:    none
//
//  RETURN VALUES: none
//
****************************************************************/

void llist::cleanup()
{
    record * currentNode;
    record * nextNode;

    /* print debug information for function call */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE========================\n\n";
        cout << "\t  Entered 'cleanup' function\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\tnone\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* unallocate all allocated heap space */

    currentNode = this->start;

    while ( currentNode != NULL )
    {
        nextNode = (*currentNode).next;

        delete currentNode;

        currentNode = nextNode;
    }

    this->start = NULL;
}

/*****************************************************************
//
//  FUNCTION NAME: reverse
//
//  DESCRIPTION:   A public reverse class that calls the private recursive
//                 reverse function to reverse the order of the list.
//
//  PARAMETERS:    none
//
//  RETURN VALUES: none
//
****************************************************************/

void llist::reverse()
{

    /* print debug information for function call */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE========================\n\n";
        cout << "\t  Entered public reverse function\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\tnone\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* call private reverse function */

    start = this->reverse(start);
}

/*****************************************************************
//
//  FUNCTION NAME: overloaded reverse
//
//  DESCRIPTION:   A private overloaded function that recursively reverses
//                 the order of the list.
//
//  PARAMETERS:    node is a record pointer.
//
//  RETURN VALUES: Returns a record pointer.
//
****************************************************************/

record* llist::reverse(record* node)
{
    record *returnValue;
    record *newNode;

    /* print debug information for function call */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE========================\n\n";
        cout << "\t  Entered private reverse function\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\trecord pointer\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* base case of empty list */

    if ( node == NULL )
    {
        returnValue = NULL;
    }

    /* base case of node.next is null */

    else if ( node->next == NULL )
    {
        returnValue = node;
    }

    /* recursion */

    else
    {
        // recursive function call
        newNode = reverse(node->next);

        // update references
        node->next->next = node;
        node->next = NULL;

        returnValue = newNode;
    }

    return returnValue;
}

/*****************************************************************
//
//  FUNCTION NAME: size
//
//  DESCRIPTION:   A public utility function that returns the size of
//                 the linked list.
//
//  PARAMETERS:    none
//
//  RETURN VALUES: Returns an int representing the amount of records in list.
//
****************************************************************/

int llist::size()
{
    int size = 0;

    record* node = start;

    /* print debug information for function call */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE========================\n\n";
        cout << "\t  Entered llist size function\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\tnone\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* iterate through list, counting records */

    while ( node != NULL )
    {
        size++;
        node = node->next;
    }

    return size;
}

