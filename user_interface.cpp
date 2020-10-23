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
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//    A file containing the user interface used to access the database
//    in llist.cpp.  The user interface collects user input to access
//    database functions.
//
//
****************************************************************/

/* includes */
#include "user_interface.h"

/*****************************************************************
//
//  FUNCTION NAME: main
//
//  DESCRIPTION:   The main driver for the user interface, it prints the 
//                 opening message, tells the user how many records are in
//                 the database upon start, and how many have been saved upon
//                 exit.
//
//  PARAMETERS:    int argc is the number of arguments.
//                 char *argv[] is an array of the arguent pointers.
//
//  RETURN VALUES: Returns 0
//
****************************************************************/

int main(int argc, char *argv[])
{
    int recordReturn;

    llist list;

    /* print debug info */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE========================\n\n";
        cout << "\t  Entered 'main'\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\targc, argv (unused)\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* print initial instructions */

    cout << "\n===============================================================================\n";
    cout << "\nWelcome to the user interface for project1!\n";
    cout << "This UI offers multiple methods of accessing and updating the database.\n";
    cout << "Each method can be called as many times as needed.\n";
    cout << "\n===============================================================================\n\n";

    /* print database import statement */

    recordReturn = list.size();

    if ( recordReturn < 1 )
    {
        cout << "Database is currently empty.\n";
    }
    else if ( recordReturn == 1 )
    {
        cout << "1 record currently in database.\n";
    }
    else
    {
        cout << recordReturn << " records currently in database.\n";
    }

    /* run program */

    getUserInput(list);

    /* print exit message */

    cout << "\n===============================================================================\n\n";

    recordReturn = list.size();

    if ( recordReturn == 0 )
    {
        cout << "Database empty! No records to be saved to database file.\n";
    }
    else if ( recordReturn == 1 )
    {
        cout << "Tried saving 1 record to database file.\n";
    }
    else
    {
        cout << "Tried saving " << recordReturn << " records to database file.\n";
    }

    cout << "\n===============================================================================\n";

    return 0;
}

/*****************************************************************
//
//  FUNCTION NAME: getUserInput
//
//  DESCRIPTION:   A function that gets the user's input and calls the function that the user chooses.
//                 The user_interface functions are used to gather further input.
//
//  PARAMETERS:    list is a reference to an llist object.
//
//  RETURN VALUES: none
//
****************************************************************/

void getUserInput(llist & list)
{
    int recordReturn;
    int userInput;
    int accountNo;

    char name[NAME_LENGTH];
    char address[ADDRESS_LENGTH];

    /* print debug info */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE========================\n\n";
        cout << "\t  Entered 'getUserInput' function\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\tobject reference\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* run until user quits */

    userInput = 0;

    while ( userInput != 7 )
    {
        writeMenu();

        /* get user input */

        if ( !(cin >> userInput) )
        {
            cin.clear();
            userInput = 0;
        }

        clearLine();

        /* process user input */

        switch ( userInput )
        {

            /* addRecord case */

            case 1:

                // collect record data
                accountNo = getAccountNo();
                getName(name, NAME_LENGTH);
                getAddress(address, ADDRESS_LENGTH);

                // add record
                recordReturn = list.addRecord(accountNo, name, address);

                // print return statement
                if ( recordReturn == 0 )
                {
                    cout << "\n===============================================================================\n\n";
                    cout << "Record successfully added!\n";
                }
                else
                {
                    cout << "Record could not be added! Not enough memory!\n";
                }

                break;

            /* printRecord case */

            case 2:

                // check list size
                if ( list.size()  == 0 )
                {
                    cout << "\n===============================================================================\n\n";
                    cout << "Database is empty!\n";
                }
                // print record
                else
                {
                    accountNo = getAccountNo();

                    recordReturn = list.printRecord(accountNo);

                    if ( recordReturn == 0 )
                    {
                        cout << "\nThere are no records with account number " << accountNo;
                        cout << " in the database.\n\n";
                    }
                    else if ( recordReturn == 1 )
                    {
                        cout << "\nThere is 1 record with account number " << accountNo;
                        cout << " in the database.\n\n";
                    }
                    else if ( recordReturn > 1 )
                    {
                        cout << "\nThere are " << recordReturn << " records with account number ";
                        cout << accountNo << " in the database.\n\n";
                    }
                }

                break;

            /* printAllRecords case */

            case 3:

                // print all records
                cout << "\n===============================================================================\n\n";

                if ( list.size() == 0 )
                {
                    cout << "Database is empty!\n";
                }
                else {
                    cout << list;
                }

                break;

            /* modifyRecord case */

            case 4:

                // check list size
                if ( list.size() == 0 )
                {
                    cout << "\n===============================================================================\n\n";
                    cout << "Database is empty!\n";
                }
                // modify record
                else
                {
                    accountNo = getAccountNo();
                    getAddress(address, ADDRESS_LENGTH);

                    recordReturn = list.modifyRecord(accountNo, address);

                    cout << "\n===============================================================================\n\n";

                    if ( recordReturn == 0 )
                    {
                        cout << "\nThere are no records with account number " << accountNo;
                        cout << " in the database.\n\n";
                    }
                    else if ( recordReturn == 1 )
                    {
                        cout << "\n1 record with account number " << accountNo  << " got modified.\n\n";
                    }
                    else if ( recordReturn > 1 )
                    {
                        cout << '\n' << recordReturn << " records with account number ";
                        cout << accountNo << " got modified.\n\n";
                    }
                }

                break;

            /* deleteRecord case */

            case 5:

                // check list size
                if ( list.size() == 0 )
                {
                    cout << "\n===============================================================================\n\n";
                    cout << "Database is empty!\n";
                }
                // delete record(s)
                else
                {
                    accountNo = getAccountNo();

                    recordReturn = list.deleteRecord(accountNo);

                    cout << "\n===============================================================================\n\n";

                    if ( recordReturn == 0 )
                    {
                        cout << "\nThere are no records with account number " << accountNo << " in the database.\n\n";
                    }
                    else if ( recordReturn == 1 )
                    {
                        cout << "\n1 record with account number " << accountNo << " got deleted.\n\n";
                    }
                    else if ( recordReturn > 1 )
                    {
                        cout << '\n' << recordReturn << " records with account number ";
                        cout << accountNo << " got deleted.\n\n";
                    }
                }

                break;

            /* reverse list case */

            case 6:

                cout << "\n===============================================================================\n\n";

                recordReturn = list.size();

                // check list size
                if ( recordReturn == 0 )
                {
                    cout << "Database is empty!\n";
                }
                else if ( recordReturn == 1 )
                {
                    cout << "Only 1 record in database, cannot reverse!\n";
                }
                else
                {
                    list.reverse();
                    cout << "Database reversed!\n";
                }

                break;

            /* quit program case */

            case 7:
                break;

            /* invalid input case */

            default:
                cout << "\n===============================================================================\n\n";
                cout << "\nInvalid input!\n\n";
        }
    }
}

/*****************************************************************
//
//  FUNCTION NAME: writeMenu
//
//  DESCRIPTION:   A function that writes the UI menu to the screen.
//
//  PARAMETERS:    none
//
//  RETURN VALUES: none
//
****************************************************************/

void writeMenu()
{
    cout << "\n===============================================================================\n\n";

    /* print debug info */

    #ifdef DEBUGMODE

        cout << "\n\t==DEBUG MODE========================\n\n";
        cout << "\t  Entered 'writeMenu' function\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\tnone\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* print the menu */

    cout << "There are 7 implemented choices, as described below.\n";
    cout << "Please input the number corresponding with your choice.\n\n";
    cout << "1: Add new record to database\n";
    cout << "2: Print record for individual account\n";
    cout << "3: Print all records in database\n";
    cout << "4: Modify address of an account\n";
    cout << "5: Delete an account's record\n";
    cout << "6: Reverse the order of the list\n";
    cout << "7: Quit\n\nInput: ";

}

/*****************************************************************
//
//  FUNCTION NAME: getAccountNo
//
//  DESCRIPTION:   Gets an account number from the user.
//
//  PARAMETERS:    none
//
//  RETURN VALUES: Returns the account number (int).
//
****************************************************************/

int getAccountNo()
{
    bool gotNumber;

    int accountNo;

    cout << "\n===============================================================================\n";

    /* print debug info */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE========================\n\n";
        cout << "\t  Entered 'getAccountNo' function\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\tnone\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* print instructions */

    cout << "\nPlease enter account number\n";
    cout << "  (account numbers are positive integers)\n\n";
    cout << "Number: ";

    /* get account number */

    gotNumber = false;
    accountNo = -1;

    while ( !gotNumber )
    {

        /* get user input */

        if ( !(cin >> accountNo) )
        {
            cin.clear();
            accountNo = 0;
        }

        clearLine();

        /* check input quality */

        if ( accountNo < 1 )
        {
            cout << "\nInvalid account number! Please try again\n\nNumber: ";
        }
        else
        {
            gotNumber = true;
        }

    }

    return accountNo;
}

/*****************************************************************
//
//  FUNCTION NAME: getName
//
//  DESCRIPTION:   Gets the account name from the user.
//
//  PARAMETERS:    char *name is the name string.
//                 int size is the max size of the string.
//
//  RETURN VALUES: none
//
****************************************************************/

void getName(char * name, int size)
{
    int length;
    char ch;

    cout << "\n===============================================================================\n";

    /* print debug info */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE========================\n\n";
        cout << "\t  Entered 'getName' function\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t  name pointer\n";
        cout << "\t\tsize: " << size << "\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* print instructions */

    cout << "\nPlease enter desired account name\n";
    cout << "  (Names have a maximum length of " << size - 1 << " characters)\n";
    cout << "  (To submit name, press 'Enter')\n\n";
    cout << "Name: ";

    /* get name */

    length = 0;
    cin.get(ch);

    while ( ch != '\n' && length < size - 1 )
    {
        if ( ch != '\t' ) // ignore tabs in names
        {
            name[length++] = ch;
        }
        cin.get(ch);
    }

    name[length++] = '\0';

    /* check length of input */

    if ( length == size && ch != '\n' )
    {
        clearLine();

        cout << "\nWARNING: Maximum name length reached! Received name:\n\"" << name << "\"\n";
        cout << "\nWould you like to re-enter the name? (y/n): ";

        do
        {
            cin.get(ch);
        }
        while (ch != 'y' && ch != 'n');

        clearLine();

        /* get name if user wants to retype it */

        if ( ch == 'y' )
        {
            getName(name, size);
        }

    }
}

/*****************************************************************
//
//  FUNCTION NAME: getAddress
//
//  DESCRIPTION:   Gets the account address from the user.
//
//  PARAMETERS:    char *address is the address string.
//                 int size is the max size of the string.
//
//  RETURN VALUES: none
//
****************************************************************/

void getAddress(char * address, int size)
{
    int length;

    char ch;

    cout << "\n===============================================================================\n";

    /* print debug info */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE========================\n\n";
        cout << "\t  Entered 'getAddress' function\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\taddress pointer\n";
        cout << "\t\tsize: " << size << "\n\n";
        cout << "\t====================================\n\n";
    #endif

    /* print instructions */

    cout << "\nPlease enter desired account address\n";
    cout << "  (Addresses have a maximum of " << size - 1 << " characters)\n";
    cout << "  (To indicate the end of the address, type a '!' then hit ENTER)\n\n";
    cout << "Address: ";

    /* get address */

    length = 0;
    cin.get(ch);

    while ( ch != '!' && length < size - 1 )
    {
        address[length++] = ch;

        if ( ch == '\n' )
        {
            cout << "         ";
        }

        cin.get(ch);
    }

    address[length++] = '\0';

    /* check length of input */

    if ( length ==  size && ch != '!')
    {
        clearLine();

        cout << "\nWARNING: Maximum address length reached! Received address:\n\"" << address << "\"\n";
        cout << "\nWould you like to re-enter the address? (y/n): ";

        do
        {
            cin.get(ch);
        }
        while (ch != 'y' && ch != 'n');

        clearLine();

        /* get address if user wants to retype it */

        if ( ch == 'y' )
        {
            getAddress(address, size);
        }
    }
}

/*****************************************************************
//
//  FUNCTION NAME: clearLine
//
//  DESCRIPTION:   A utility function that clears input until a newline
//                 character is detected.  It removes newline from buffer.
//
//  PARAMETERS:    none
//
//  RETURN VALUES: none
//
****************************************************************/

void clearLine()
{
    char ch;

    /* print debug info */

    #ifdef DEBUGMODE
        cout << "\n\t==DEBUG MODE========================\n\n";
        cout << "\t  Entered 'clearLine' function\n\n";
        cout << "\t  Parameters:\n";
        cout << "\t\tnone\n\n";
        cout << "\t====================================\n\n";
    #endif

    do // clear line
    {
        cin.get(ch);
    }
    while ( ch != '\n' );

}
