/*------------------------------------------------------------------------------
							Tim Ferido
							CSE12, Summer Academy
							Aug 30, 2017
							cs12xaf
				Assignment HW8
File Name	Driver.h
Description	this declares the UCSD student object which will be used to test
		our program.
------------------------------------------------------------------------------*/
#ifndef DRIVER_H
#define DRIVER_H

#include <string.h>
#include <iostream>
#include <cstdlib>
using namespace std;

/*------------------------------------------------------------------------------
Class Name	UCSDStudent
Description	The purpose of this class is to test our program. The members 
		defined here are a overloaded const char * operator, a == 
		overloaded operator, and a < overloaded operator
------------------------------------------------------------------------------*/
class UCSDStudent {
        friend ostream & operator << (ostream &, const UCSDStudent &);
        char name[20];
	long studentnum;
public:
	/*----------------------------------------------------------------------
	Function Name		UCSDStudent
	Description		This is a constructor for UCSDStudent. It 
				initializes the private member data fields
	----------------------------------------------------------------------*/
	UCSDStudent (char * nm, long val = 0) : studentnum (val) {
		strcpy (name, nm);
	}
	/*----------------------------------------------------------------------
	Function Name		operator const char * 
	Description		This method is used to return the name member 
				data field of the object called from
	----------------------------------------------------------------------*/
	operator const char * (void) const {
		return name;
	}
	/*----------------------------------------------------------------------
	Function Name		operator ==
	Description		this is an overloaded operator that is used to 
				compare the name data fields of the object 
				called from and the object passed in
	----------------------------------------------------------------------*/
	long operator == (const UCSDStudent & variable) const {
		return ! strcmp (name, variable.name);
	}
	/*----------------------------------------------------------------------
	Function Name		operator <
	Description		this function is an overloaded operator that is 
				used to compare the name data fields of the
				object called from and the object passed in and
				return true if the calling object is less than
				the one passed in.
	----------------------------------------------------------------------*/
	long operator < (const UCSDStudent & variable) const {
		return (strcmp (name, variable.name) < 0) ? 1 : 0;
	}
};

#endif
