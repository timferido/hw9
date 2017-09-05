/****************************************************************************

                                                        Adam Kabbara, cs12xbr
														Tim Ferido, csxaf
                                                        CSE 12, SS2 
                                                        08-31-2017
                                Assignment Nine

File Name:      Driver.c
Description:    This file contains fuctions for a UCSDStudent. It is used to 
				store and display information about the student.
*****************************************************************************/
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <getopt.h>
#include "Driver.h"
#include "SymTab.h"

using namespace std;

#ifdef NULL
#undef NULL
#define NULL 0
#endif

ostream & operator << (ostream & stream, const UCSDStudent & stu) {
        return stream << "name:  " << stu.name
                << " with studentnum:  " << stu.studentnum;
}

int main (int argc, char * const * argv) {

        char buffer[BUFSIZ];
        char command;
        long number;
        char option;
        
        SymTab<UCSDStudent>::Set_Debug_Off ();

        while ((option = getopt (argc, argv, "x")) != EOF) {

        switch (option) {
                case 'x': SymTab<UCSDStudent>::Set_Debug_On ();
                        break;
                }       
        }
        
        SymTab<UCSDStudent> ST("Driver.datafile");
        ST.Write (cout << "Initial Symbol Table:\n" );

        while (cin) {
                command = NULL;         // reset command each time in loop
                cout << "Please enter a command ((i)nsert, "
                        << "(l)ookup, (r)emove, (w)rite):  ";
                cin >> command;

                switch (command) {

                case 'i': {
                        cout << "Please enter UCSD student name to insert:  ";
                        cin >> buffer;  // formatted input

                        cout << "Please enter UCSD student number:  ";
                        cin >> number;

                        UCSDStudent stu (buffer, number);

                        // create student and place in symbol table
                        ST.Insert (stu);
                        break;
                }
                case 'l': { 
                        unsigned long found;    // whether found or not

                        cout << "Please enter UCSD student name to lookup:  ";
                        cin >> buffer;  // formatted input

                        UCSDStudent stu (buffer, 0);
                        found = ST.Lookup (stu);
                        
                        if (found)
                                cout << "Student found!!!\n" << stu << "\n";
                        else
                                cout << "student " << buffer << " not there!\n";
                        break;
                        }
                case 'r': { 
                        unsigned long removed;

                        cout << "Please enter UCSD student name to remove:  ";
                        cin >> buffer;  // formatted input

                        UCSDStudent stu (buffer, 0);
                        removed = ST.Remove(stu);

                        if (removed)
                                cout << "Student removed!!!\n" << stu << "\n";
                        else
                                cout << "student " << buffer << " not there!\n";
                        break;
                }
                case 'w':
                        ST.Write (cout << "The Symbol Table contains:\n");
                }
        }
	

        ST.Write (cout << "\nFinal Symbol Table:\n");

		//Displays information about the Tree
		if (ST.GetOperation() != 0) {
			cout << "\nCost of operations: ";
			cout << ST.GetCost();
			cout << " tree accesses";

			cout << "\nNumber of operations: ";
			cout << ST.GetOperation();

			cout << "\nAverage cost: ";
			cout << (((float)(ST.GetCost()))/(ST.GetOperation()));
			cout << " tree accesses/operation\n";
		}
		//No information was found
		else
	        cout << "\nNo cost information available.\n";

}
