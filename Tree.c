/****************************************************************************

                                                        Adam Kabbara, cs12xbr
														Tim Ferido, cs12xaf
                                                        CSE 12, SS2 
                                                        09-06-2017
                                Assignment Nine

File Name:      Tree.c
Description:    This file contains the implementations for a binary tree.
				It includes functionality for persistent data.
				Debug option is also included.
****************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "Tree.h"

// debug messages
static const char ALLOCATE[] = " - Allocating]\n";
static const char COST_READ[] = "[Cost Increment (Disk Access): Reading ";
static const char COST_WRITE[] = "[Cost Increment (Disk Access): Writing ";
static const char DEALLOCATE[] = " - Deallocating]\n";
static const char TREE[] = "[Tree ";

template <class Whatever>
int Tree<Whatever>::debug_on = 0;

template <class Whatever>
long Tree<Whatever>::cost = 0;

template <class Whatever>
long Tree<Whatever>::operation = 0;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define THRESHOLD 2

template <class Whatever>
ostream & operator << (ostream &, const TNode<Whatever> &);

template <class Whatever>
struct  TNode {
// friends:

// data fields:
	Whatever data;
	long height;
	long balance;
	offset left;
	offset right;
	offset this_position;	// current position

// function fields:
	TNode () : height (0), balance (0), left (0), right (0), 
		this_position (0) {}

	// to declare the working TNode in Tree's Remove
	TNode (Whatever & element) : data (element), height (0), balance (0),
		left (0), right (0), this_position (0) {}
	
	TNode (Whatever &, fstream *, long &);	// to add new node to disk
	TNode (const offset &, fstream *);	// to read node from disk
	
	unsigned long Insert (Whatever &, fstream *, long &, offset &);
	// optional recursive Lookup declaration would go here
	void Read (const offset &, fstream *);	// read node from disk
	unsigned long Remove (TNode<Whatever> &, fstream *, long &, offset &,
		long fromSHB = FALSE);
	void ReplaceAndRemoveMin (TNode<Whatever> &, fstream *, offset &);
	void SetHeightAndBalance (fstream *, offset &);
	void Write (fstream *) const;		// update node to disk

	ostream & Write_AllTNodes (ostream &, fstream *) const;
};

/*----------------------------------------------------------------------
Function Name:         Tree<Whatever> :: Set_Debug_Off
Purpose:               Set Debugger off.
Description:           The function sets the debugger messeges off.
Input:                 No input value.
Result:                No return value. Debug messages don't show
----------------------------------------------------------------------*/
template <class Whatever>
void Tree<Whatever> :: Set_Debug_Off () {

	debug_on = false; //Debuger turned off
}

/*----------------------------------------------------------------------
Function Name:         Tree<Whatever> :: Set_Debug_On
Purpose:               Set Debugger on.
Description:           The function sets the debugger messeges on.
Input:                 No input value.
Result:                No return value. Debug messages show.
----------------------------------------------------------------------*/
template <class Whatever>
void Tree<Whatever> :: Set_Debug_On() {

	debug_on = true; //Debuger turned on
}

/*----------------------------------------------------------------------
Function Name:         Insert
Purpose:               Insert an element into the binary tree.
Description:           The function exists Insert an element into the binary 
					   tree. Inserts at the root TNode if Tree is empty, 
					   otherwise delegates to TNode's Insert.
Input:                 element: expected to be the data stored in the TNode.
					   They must be of the same type as the rest of the object
					   present in the tree.
Result:                Returns true or false indicating success of insertion
----------------------------------------------------------------------*/
template <class Whatever>
unsigned long Tree<Whatever> :: Insert (Whatever & element) {

	//Check if first insert TODO: might be 16
	if (!occupancy) {

		//Debug messages
		if (debug_on) {
			
			cerr <<  COST_WRITE << (const char *)(element) << "]\n";
		}

		// create a new node
		TNode<Whatever> rootNode(element, fio, occupancy);

		// set root to newnode.this_position
		//root = rootNode.this_position;

		return true;
	}

	//Delegate to TNodes insert
	else {
		//calling read constructor
		TNode<Whatever> readRootNode(root, fio);

		
		//call tnode insert on new node
		return readRootNode.Insert(element, fio, occupancy, root);

	} 
}

template <class Whatever>
void TNode<Whatever> :: ReplaceAndRemoveMin (TNode<Whatever> & targetTNode, 
	fstream * fio, offset & PositionInParent) {
	/* YOUR CODE GOES HERE */
}

template <class Whatever>
unsigned long TNode<Whatever> :: Remove (TNode<Whatever> & elementTNode,
	fstream * fio, long & occupancy, offset & PositionInParent,
	long fromSHB) {
	/* YOUR CODE GOES HERE */
	return;
}
	
template <class Whatever>
unsigned long Tree<Whatever> :: Remove (Whatever & element) {
	/* YOUR CODE GOES HERE */
	return 0;
}

template <class Whatever>
void TNode<Whatever> :: SetHeightAndBalance (fstream * fio,
	offset & PositionInParent) {
	/* YOUR CODE GOES HERE */
}
/*----------------------------------------------------------------------
Function Name:		GetCost 
Purpose:            gets the value of Tree<Whatever>::cost variable 
Description:        this funciton exists to get the value of Tree<Whatever>
					::cost variable
Input:              no input values. 
Result:             returns value of Tree<Whatever>::cost 
----------------------------------------------------------------------*/
template <class Whatever>
long Tree <Whatever> :: GetCost () {

	return cost;
}
/*----------------------------------------------------------------------
Function Name:		GetOperation
Purpose:            gets the value of Tree<Whatever>::operation variable 
Description:        this funciton exists to get the value of Tree<Whatever>
					::operation variable
Input:              no input values. 
Result:             returns value of Tree<Whatever>::operation
----------------------------------------------------------------------*/
template <class Whatever>
long Tree <Whatever> :: GetOperation () {

	return operation;
}
/*----------------------------------------------------------------------
Function Name:		IncrementCost	
Purpose:			Increments the value of the Tree<Whatever>::cost variable 
Description:        this funciton exists increment the value Tree<Whatever>
					::operation variable. This should be called when a
					read or write to the disk occurs.
Input:              no input values. 
Result:				no return values.
					increments value of Tree<Whatever>::cost
----------------------------------------------------------------------*/
template <class Whatever>
void Tree <Whatever> :: IncrementCost () {

	cost++;
}
/*----------------------------------------------------------------------
Function Name:		IncrementOperation
Purpose:			Increments the value of the Tree<Whatever>::operation 
					variable 
Description:        this funciton exists increment the value Tree<Whatever>
					::operation variable. This should be called when a
					tree operation occurs (insert, lookup, and remove).	
Input:              no input values. 
Result:             no return value. 
					increments value of Tree<Whatever>::operation
----------------------------------------------------------------------*/
template <class Whatever>
void Tree <Whatever> :: IncrementOperation () {

	operation++;
}

template <class Whatever>
void Tree <Whatever> :: ResetRoot () {
        /* YOUR CODE GOES HERE */       
}

/*----------------------------------------------------------------------
Function Name:         Insert
Purpose:               Insert an element into the binary tree.
Description:           The function exists Insert an element into the binary 
					   tree.
Input:                 element: expected to be the data stored in the TNode.
					   They must be of the same type as the rest of the object
					   fio: expected to be the filestream corresponding to 
					   the datafile where the Tree is stored on disk.
					   PositionInParent: expected to be a reference to the
					   TNode position in the parent TNode used to get to
					   the current TNode's offset in the datafile.
Result:                Returns true or false indicating success of insertion.
----------------------------------------------------------------------*/
template <class Whatever>
unsigned long TNode<Whatever> :: Insert (Whatever & element, fstream * fio,
	long & occupancy, offset & PositionInParent) {

	//Debug messages
	if (Tree<Whatever>::debug) {
		
		cerr <<  "[Tree " << tree_count << COMPARE << (const char *)(element) 
			 << AND << (const char *)(PositionInParent->data) << "]\n";
	}

	//Check if it is a duplicate
	if (data == element) {
		
		//Replace
		data = element;
	}
	//Check if it should got left
	else if (element < data) {
		
		if (left == NULL) { 

			//Debug messages
			if (Tree<Whatever>::debug) {
				
				cerr <<  "[Tree " << tree_count << INSERT 
					 << (const char *)(element) << "]\n";
			}

			//Create a new node to the left of the parent
			left = new TNode<Whatever>(element, *this);
			//left = 
		}
		//Go left
		else {
			
			left->Insert(element, left);
			// TNode<Whatever> readNode(element, fio);
			// readNode.Insert (element, fio, occupancy, root);
		}
	}
	//Check right side
	else {
		
		if (right == NULL) { 
			
			//Debug messages
			if (Tree<Whatever>::debug) {
				
				cerr <<  "[Tree " << tree_count << INSERT 
					 << (const char *)(element) << "]\n";
			}

			//Create a new node to the right of the parent
			right = new TNode<Whatever>(element, *this);
		}
		//Go right
		else {
			
			right->Insert(element, right);
		}
	}

	//Update height and balance
	SetHeightAndBalance(PositionInParent);

	return true;

}

template <class Whatever>
unsigned long Tree<Whatever> :: Lookup (Whatever & element) const {
	/* YOUR CODE GOES HERE */
	return 0;
}

/*----------------------------------------------------------------------
Function Name:      Read
Purpose:			Reads the current tnode on the datafile into memory.
Description:		This function exists to read the current tnode on
					the datafile for use. The TNode is read from 
					position, the tnode's information in the datafile
					overwrites this TNode's data.
Input:              position: expected to be the offset in the data 
					corresponding to the position of the tnode we wish
					to read into memory.
					fio: expected to be the file stream corresponding to
					the datafile where the tree is stored on disk
Result:				no return value. TNode is read from datafile to 
					memory.
----------------------------------------------------------------------*/
template <class Whatever>
void TNode<Whatever> :: Read (const offset & position, fstream * fio) {

	//get current position
	fio->seekg(position);

	//Read form the file to get the TNode
	fio->read((char *)this, sizeof(TNode<Whatever>));

}

/*----------------------------------------------------------------------
Function Name:      TNode
Purpose:			called when reading a tnode present on disk
Description:        This function exists to read a tnode present on the
					disk into memory.
Input:              position: expected to be the offset in the data 
					corresponding to the position of the tnode we wish
					to read into memory.
					fio: expected to be the file stream corresponding to
					the datafile where the tree is stored on disk
Result:				No return value.
----------------------------------------------------------------------*/
template <class Whatever>
TNode<Whatever> :: TNode (const offset & position, fstream * fio) {

	// calls read to get tnode from datafile
	Read(position, fio);
}

/*----------------------------------------------------------------------
Function Name:      TNode
Purpose:			called when creating a TNode for the first time.
Description:        This function exists to be called when creating a
					TNode for the first time.
Input:              element: The data to be stored in the TNode. Must
					be the same type as the rest of the objects present
					in the tree.
					fio: expected to be the file stream corresponding to
					the datafile where the tree is stored on disk
					occupancy: Expected to be a reference to the occupancy
					to the tree to which the new node is being added.
Result:				No return value.
----------------------------------------------------------------------*/
template <class Whatever>
TNode<Whatever> :: TNode (Whatever & element, fstream * fio, long & occupancy): 
		data (element), height (0), balance (0), left (0), right (0) {

	// seek to end
	fio->seekp(0,ios::end);
	this_position = fio->tellp();

	// calls read to get tnode from datafile
	Write(fio);

	occupancy++;
}

/*----------------------------------------------------------------------
Function Name:      Write
Purpose:			Writes the TNode object to disk at this_position in the
					datafile.
Description:        This function exists writes the TNode object to disk at 
					this_position in the datafile.
Input:              fio: expected to be the file stream corresponding to
					the datafile where the tree is stored on disk
Result:				No return value.
----------------------------------------------------------------------*/
template <class Whatever>
void TNode<Whatever> :: Write (fstream * fio) const {

	//get current position
	fio->seekp(this_position);

	//Read form the file to get the TNode
	fio->write((char *)this, sizeof(TNode<Whatever>));

}

/*------------------------------------------------------------------------------
Function Name:      Tree<Whatever> :: Tree
Purpose:			Called when creating a Tree. Allocates memory for
					the tree
Description:        Guarantee initialization of occupancy and root. It 
					also initializes the tree_count using a static 
					counter.
Input:              No input value.
Result:             No return value.
------------------------------------------------------------------------------*/
template <class Whatever>
Tree<Whatever> :: Tree (const char * datafile) :
	fio (new fstream (datafile, ios :: out | ios :: in)), occupancy(0), root(0),
	tree_count(0) {

	//one more tree
	tree_count++;

	if (debug_on) {
		
		cerr << "[Tree " << tree_count << ALLOCATE;
	}
	
	//check for empty file
	fio->seekp(0,ios::beg);
	offset beginning = fio->tellp();

	fio->seekp(0, ios::end);
	offset end = fio->tellp();

	if (beginning == end) {
		
		//reserve space
		fio->seekp(0, ios::beg);
		fio->write((const char *) & root, sizeof(root));
		fio->write((const char *) & occupancy, sizeof(occupancy));
		root = fio->tellp();
	}
	//read root and occupancy
	else {
		
		//
		fio->seekp(0, ios::beg);
		fio->read((char*) & root, sizeof(root));
		fio->read((char*) & occupancy, sizeof(occupancy));

	}
}

template <class Whatever>
Tree<Whatever> :: ~Tree (void)
/***************************************************************************
% Routine Name : Tree :: ~Tree  (public)
% File :         Tree.c
% 
% Description :  deallocates memory associated with the Tree.  It
%                will also delete all the memory of the elements within
%                the table.
***************************************************************************/

{

	if (debug_on) {
		
		cerr << "[Tree " << tree_count << DEALLOCATE;
	}

	//rewrite to datafile
	fio->seekp(0, ios::beg);
	fio->write((const char *) & root, sizeof(root));
	fio->write((const char *) & occupancy, sizeof(occupancy));

	//delete pointer to file
	delete fio;
	tree_count--;

}

template <class Whatever>
ostream & operator << (ostream & stream, const TNode<Whatever> & nnn) {
	stream << "at height:  :" << nnn.height << " with balance:  "
		<< nnn.balance << "  ";
	return stream << nnn.data << "\n";
}

template <class Whatever>
ostream & Tree<Whatever> :: Write (ostream & stream) const
/***************************************************************************
% Routine Name : Tree :: Write (public)
% File :         Tree.c
% 
% Description : This funtion will output the contents of the Tree table
%               to the stream specificed by the caller.  The stream could be
%               cerr, cout, or any other valid stream.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% stream             A reference to the output stream.
% <return>           A reference to the output stream.
***************************************************************************/

{
        long old_cost = cost;

	stream << "Tree " << tree_count << ":\n"
		<< "occupancy is " << occupancy << " elements.\n";

	fio->seekg (0, ios :: end);
	offset end = fio->tellg ();

	// check for new file
	if (root != end) {
		TNode<Whatever> readRootNode (root, fio);
		readRootNode.Write_AllTNodes (stream, fio);
	}

        // ignore cost when displaying nodes to users
        cost = old_cost;

	return stream;
}

template <class Whatever>
ostream & TNode<Whatever> ::
Write_AllTNodes (ostream & stream, fstream * fio) const {
	if (left) {
		TNode<Whatever> readLeftNode (left, fio);
		readLeftNode.Write_AllTNodes (stream, fio);
	}
	stream << *this;
	if (right) {
		TNode<Whatever> readRightNode (right, fio);
		readRightNode.Write_AllTNodes (stream, fio);
	}

	return stream;
}

