/*******************************************************************************

                                                        Adam Kabbara, cs12xbr
							Tim Ferido, cs12xaf
                                                        CSE 12, SS2 
                                                        09-06-2017
                                Assignment Nine

File Name:      Tree.c
Description:    This file contains the implementations for a binary tree.
		It includes functionality for persistent data.
		Debug option is also included.
*******************************************************************************/
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

/*------------------------------------------------------------------------------
Function Name		<<
Purpose			operator overload function declaration.
------------------------------------------------------------------------------*/
template <class Whatever>
ostream & operator << (ostream &, const TNode<Whatever> &);

/*------------------------------------------------------------------------------
Class Name		TNode
Description		This class defines the object to make up the tree and 
			its member values
Members			Whatever data:
				the data member field of the node
			long height:
				the height of the specific node in the tree
			long balance:
				the difference of the heights between the left
				and right nodes of a specific noed in the tree
			offset left:
				where the left node exists in the datafile
			offset right:
				where the right node exists in the datafile
			offset this_position:
				where the node's memory begins in the 
				datafile
			TNode():
				default constructor
			TNode(Whatever & element):
				constructor that takes in an element and
				creates a new node
			TNode (const offset &, element):
				constructor that reads a node from disk
			TNode (Whatever &, fstream *, long &):
				constructor that adds a new node to disk
			Insert:
				inserts a new node or existing node into
				memory tree
			Read:
				reads a node from the disk
			Remove:
				'removes' a node from the disk
			ReplaceAndRemoveMin:
				replaces the current node with its successor 
				node
			SetHeightAndBalance:
				updates the node's height and balance
			Write:
				update node to disk
			Write_AllTNodes:
				displays all node on disk
------------------------------------------------------------------------------*/
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
	unsigned long Lookup (Whatever &, fstream *, 
		const offset &) const;
	void Read (const offset &, fstream *);	// read node from disk
	unsigned long Remove (TNode<Whatever> &, fstream *, long &, offset &,
		long fromSHB = FALSE);
	void ReplaceAndRemoveMin (TNode<Whatever> &, fstream *, offset &);
	void SetHeightAndBalance (fstream *, offset &);
	void Write (fstream *) const;		// update node to disk

	ostream & Write_AllTNodes (ostream &, fstream *) const;
};

/*------------------------------------------------------------------------------
Function Name:         Tree<Whatever> :: Set_Debug_Off
Purpose:               Set Debugger off.
Description:           The function sets the debugger messeges off.
Input:                 No input value.
Result:                No return value. Debug messages don't show
------------------------------------------------------------------------------*/
template <class Whatever>
void Tree<Whatever> :: Set_Debug_Off () {

	debug_on = false; //Debugger turned off
}

/*------------------------------------------------------------------------------
Function Name:         Tree<Whatever> :: Set_Debug_On
Purpose:               Set Debugger on.
Description:           The function sets the debugger messeges on.
Input:                 No input value.
Result:                No return value. Debug messages show.
------------------------------------------------------------------------------*/
template <class Whatever>
void Tree<Whatever> :: Set_Debug_On() {

	debug_on = true; //Debugger turned on
}

/*------------------------------------------------------------------------------
Function Name:		Insert
Purpose:		Insert an element into the binary tree.
Description:		The function exists Insert an element into the binary 
			tree. Inserts at the root TNode if Tree is empty, 
			otherwise delegates to TNode's Insert.
Input:			element: expected to be the data stored in the TNode.
			They must be of the same type as the rest of the object
			present in the tree.
Result:			Returns true or false indicating success of insertion
------------------------------------------------------------------------------*/
template <class Whatever>
unsigned long Tree<Whatever> :: Insert (Whatever & element) {

	// a tree operation is done
	IncrementOperation();

	//Check if first insert 
	if (occupancy == 0) {

		// create a new node
		TNode<Whatever> rootNode(element, fio, occupancy);

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

/*------------------------------------------------------------------------------
Function Name		ReplaceAndRemoveMin
Purpose			This function exists to handle removal of node with two
			children
Description		called when removing a TNode with 2 children. It
			replaces that tnode with the minimum tnode
			in its right subtree or successor node, to 
			maintain structure of tree.
Input			targetTNode: the node to remove
			fio: the filestream to write or read to
			PositionInParent: the offset position in the disk 
			where the current node exists
Output			The current node is removed and the successor node is
			put in its place.
------------------------------------------------------------------------------*/
template <class Whatever>
void TNode<Whatever> :: ReplaceAndRemoveMin (TNode<Whatever> & targetTNode, 
	fstream * fio, offset & PositionInParent) {

	//Find Successor
	if(left != 0) {
		
		//create a new node to call rarm
		TNode<Whatever> leftNode(left, fio);

		leftNode.ReplaceAndRemoveMin(targetTNode, fio, left);

		//Fix height and Balance
		SetHeightAndBalance(fio, PositionInParent);
	}

	//Replace
	else {

		//Replace the data
		targetTNode.data = data;
		
		//Take care of the childern
		if (right)
			PositionInParent = right;
		else
			PositionInParent = 0;

	}
}

/*------------------------------------------------------------------------------
Function Name		Remove
Purpose			This is TNode's remove, that is responsible for
			removing a node from the datafile
Description		The position of the node on the disk is no longer 
			referenced to and it is 'removed' from the tree
			structure.
Input			elementTNode: the tnode to be removed
			fio: the filestream to read and write to
			occupancy: the number of elements in the tree
			PositionInParent: the offset position of the current
			node in the datafile
Output			The tnode in the datafile is 'removed' from the tree
			structure.
------------------------------------------------------------------------------*/
template <class Whatever>
unsigned long TNode<Whatever> :: Remove (TNode<Whatever> & elementTNode,
	fstream * fio, long & occupancy, offset & PositionInParent,
	long fromSHB) {

	// success indicator
	long retval = 0;

	//Base case: found node
	if (elementTNode.data == data) {

		//Store data
		elementTNode.data = data;

		//Check if leaf
		if (left == 0 && right == 0) {

			PositionInParent = 0;	//Set TNode to 0
		}
		
		//Has two children
		else if (left != 0 && right != 0) {

			TNode<Whatever> success(elementTNode.data);

			// create node to call replace and remove node from
			TNode<Whatever> readRightNode(right, fio);
			
			//Find replacement are switch
			readRightNode.ReplaceAndRemoveMin(success, fio, right);

			data = success.data;

			//Fix height and balance if not from SHAB
			if (fromSHB == false) {

				SetHeightAndBalance(fio, PositionInParent);

			}else {

				Write(fio);

			}
		}

		//TNode has one child
		else {

			//Check if there is a left TNode
			if (left != 0) {
				
				PositionInParent = left;
			}
			else {
				
				PositionInParent = right;
			}
		}

		return TRUE;
	}

	//Check to go left or right
	else if (PositionInParent != 0) {
		
		//Call Remove form left
		if ( elementTNode.data < data) {
			if (left != 0) { 

				//create node to call remove from left
				TNode<Whatever> readLeftNode(left, fio);

				retval=readLeftNode.Remove(elementTNode, fio, 
					occupancy, left, fromSHB);
			}
			//Not found
			else {
				
				//return false;
			}
		}
		
		//Call Remove from right
		else {

			if (right != 0) {
			
				// create right node to remove from
				TNode<Whatever> readRightNode(right, fio);

				retval=readRightNode.Remove(elementTNode, fio, 
					occupancy, right, fromSHB);
			}
			//Not found
			else {
				
				//return false;	
			}
		}
	}
	//Fix height
	if (fromSHB == false) {

		SetHeightAndBalance(fio, PositionInParent);
	}

	return retval;
}
	
/*------------------------------------------------------------------------------
Function Name		Remove
Purpose			This is Tree's remove that is responsible for delegating
			to TNode's remove 
Description		This function delegates to tnode's remove in order to 
			remove specific nodes.
Input			element: the node to be removed from the tree
Output			The tnode's remove is called
------------------------------------------------------------------------------*/
template <class Whatever>
unsigned long Tree<Whatever> :: Remove (Whatever & element) {

	long return_value;	//Return value for the Remove function

	// a tree operation is done
	IncrementOperation();

	//Check if tree is empty
	if (occupancy == 0) {

		return false;
	}

	//Not empty so check to find and remove
	else {

		//TNode containing data that identifies the element to remove
		TNode<Whatever> readRootNode(root, fio);

		//Create node to delete
		TNode<Whatever> remove_node(element);

		return_value = readRootNode.Remove(remove_node, fio, occupancy, 
			root, false);
		
		element = remove_node.data;

		//return data if true check occupancy == 1 to put pointer end of
		//datafile
		if (return_value) {
			occupancy--;
		}

		if (occupancy == 0) 
			ResetRoot();

		return return_value;
	}
}

/*------------------------------------------------------------------------------
Function Name		SetHeightAndBalance
Purpose			this function exists to update the height and balance
			of the current node
Description		updates the height and balance of the current
			tnode by comparing the heights of the left and right
			children
Input			fio: the filestream to be written to
			PositionInParent: the offset position of the current
			node in the datafile.
Output			The heights and balances of the current node are updated
------------------------------------------------------------------------------*/
template <class Whatever>
void TNode<Whatever> :: SetHeightAndBalance (fstream * fio,
	offset & PositionInParent) {

	int left_Height;	//Left node height
	int right_Height;	//Right node height

	//Check if there is a left child
	if (left == 0) { 
		
		left_Height = -1;
	}
	else {
		
		TNode<Whatever> TNode_left(left, fio);	//Get left TNode
		left_Height = TNode_left.height;
	}

	//Check if there is a right child
	if (right == 0) { 
		
		right_Height = -1;
	}
	else {
		
		TNode<Whatever> TNode_right(right, fio); //Get right TNode
		right_Height = TNode_right.height;
	}

	//Set height
	if (left_Height > right_Height) {
		
		height = left_Height + 1;
	}
	else {
		
		height = right_Height + 1;
	}

	//Set balance
	balance = left_Height - right_Height;

	//Check to see if the Tree need to be rebalanced
	if (abs(balance) > THRESHOLD) {

		// create long occupancy dummy
		long dummy = 0;
		
		//TNode containing the data that identifies element to remove
		//TNode<Whatever> remove_this(PositionInParent, fio);
		TNode<Whatever> remove_this(data);

		//Remove to put in the correct place
		Remove(remove_this, fio, dummy, PositionInParent, TRUE);

		// create read node at offset
		TNode<Whatever> insert_node(PositionInParent, fio);

		//Reinsert
		insert_node.Insert(remove_this.data,fio,dummy,PositionInParent);
	}
	else {
		
		//Write to the file
		Write(fio);
	}
}

/*------------------------------------------------------------------------------
Function Name:		GetCost 
Purpose:		gets the value of Tree<Whatever>::cost variable 
Description:		this funciton exists to get the value of Tree<Whatever>
			::cost variable
Input:			no input values. 
Result:			returns value of Tree<Whatever>::cost 
------------------------------------------------------------------------------*/
template <class Whatever>
long Tree <Whatever> :: GetCost () {

	return cost;
}
/*------------------------------------------------------------------------------
Function Name:		GetOperation
Purpose:		gets the value of Tree<Whatever>::operation variable 
Description:		this funciton exists to get the value of Tree<Whatever>
			::operation variable
Input:			no input values. 
Result:			returns value of Tree<Whatever>::operation
------------------------------------------------------------------------------*/
template <class Whatever>
long Tree <Whatever> :: GetOperation () {

	return operation;
}

/*------------------------------------------------------------------------------
Function Name:		IncrementCost	
Purpose:		Increments the value of the Tree<Whatever>::cost 
			variable 
Description:		this funciton exists increment the value Tree<Whatever>
			::operation variable. This should be called when a
			read or write to the disk occurs.
Input:			no input values. 
Result:			no return values.
			increments value of Tree<Whatever>::cost
------------------------------------------------------------------------------*/
template <class Whatever>
void Tree <Whatever> :: IncrementCost () {

	cost++;
}
/*------------------------------------------------------------------------------
Function Name:		IncrementOperation
Purpose:		Increments the value of the Tree<Whatever>::operation 
			variable 
Description:		this funciton exists increment the value Tree<Whatever>
			::operation variable. This should be called when a
			tree operation occurs (insert, lookup, and remove).	
Input:			no input values. 
Result:			no return value.  
			increments value of Tree<Whatever>::operation
------------------------------------------------------------------------------*/
template <class Whatever>
void Tree <Whatever> :: IncrementOperation () {

	operation++;
}

/*------------------------------------------------------------------------------
Function Name		ResetRoot
Purpose			This function exists to reset the root datafield of this
			tree to be at the end of the datafile. 
Description		This should be called when the last tnode has been 
			removed from the tree.
Input			no input values
Output			the root is moved to the end of the datafile.
------------------------------------------------------------------------------*/
template <class Whatever>
void Tree <Whatever> :: ResetRoot () {

	// seek to the end of datafile and set equal to the root
	fio->seekp(0,ios::end);
	root = fio->tellp();
}

/*------------------------------------------------------------------------------
Function Name:		Insert
Purpose:		Insert an element into the binary tree.  
Description:		The function exists Insert an element into the binary 
			tree.
Input:			element: expected to be the data stored in the TNode.
			They must be of the same type as the rest of the object
			fio: expected to be the filestream corresponding to 
			the datafile where the Tree is stored on disk.
			PositionInParent: expected to be a reference to the
			TNode position in the parent TNode used to get to
			the current TNode's offset in the datafile.
Result:			Returns true or false indicating success of insertion.
------------------------------------------------------------------------------*/
template <class Whatever>
unsigned long TNode<Whatever> :: Insert (Whatever & element, fstream * fio,
	long & occupancy, offset & PositionInParent) {

	//Check if it is a duplicate
	if (data == element) {
		
		//Replace
		data = element;
	}
	//Check if it should got left
	else if (element < data) {
		
		if (left == 0) { 

			//Create a new node to the left of the parent
			TNode<Whatever> leftNode(element, fio, occupancy);
			left = leftNode.this_position;
		}
		//Go left
		else {
			
			TNode<Whatever> readNode(left, fio);
			readNode.Insert (element, fio, occupancy, left);
		}
	}
	//Check right side
	else {
		
		if (right == 0) { 
			
			//Create a new node to the right of the parent
			TNode<Whatever> rightNode(element, fio, occupancy);
			right = rightNode.this_position;
		}
		//Go right
		else {
			
			TNode<Whatever> readNode(right, fio);
			readNode.Insert (element, fio, occupancy, right);
		}
	}

	//Update height and balance
	SetHeightAndBalance(fio, PositionInParent);

	return true;
}

/*------------------------------------------------------------------------------
Function Name		Lookup
Purpose			Searches for an element in the tree.
Description		This function takes in an element and recursively calls
			until the element is found
Input			element: the element to be searched for
Output			true or false indicating success of look up.
------------------------------------------------------------------------------*/
template <class Whatever>
unsigned long Tree<Whatever> :: Lookup (Whatever & element) const {

	// one more operation
	IncrementOperation();

	//Check if tree is empty
	if (occupancy == 0) {
		
		return false;
	}

	//Not empty: Check the rest of the tree
	else {
		
		TNode<Whatever> readRootNode(root, fio);

		return readRootNode.Lookup(element, fio, root);
	}
}

/*----------------------------------------------------------------------
Function Name:		Lookup
Purpose:		Called when searching for a TNode in the tree.
Description:		This function exists to search for a TNode in the
			tree. This function is called from Tree's insert.
Input:			element: expected to be the data stored in the TNode.
			They must be of the same type as the rest of the 
			object present in the tree.
Result:			Returns true or false indicating success of look up.
----------------------------------------------------------------------*/
template<class Whatever>
unsigned long TNode<Whatever> :: Lookup (Whatever & element,
	fstream * fio, const offset & PositionInParent) const {

		//Check if found
		if (element == data) {
		
			element = data;

			return true;
		}	

		//Find in the tree 
		//Check left tree
		else if(element < data) {
			
			//Check if there is a left TNode before using it
			if (left != 0) {
				
				TNode<Whatever> readLeftNode(left, fio);

				return readLeftNode.Lookup(element, fio, left);
			}
		}

		//Check right tree
		else if(data < element) {
			
			//Check if there is a right TNode before using it
			if (right != 0) {

				TNode<Whatever> readRightNode(right, fio);
				
				return readRightNode.Lookup(element,fio,right);
			}
		}

		//Not found
		return false;

}

/*------------------------------------------------------------------------------
Function Name:		Read
Purpose:		Reads the current tnode on the datafile into memory.
Description:		This function exists to read the current tnode on
			the datafile for use. The TNode is read from 
			position, the tnode's information in the datafile
			overwrites this TNode's data.
Input:			position: expected to be the offset in the data 
			corresponding to the position of the tnode we wish
			to read into memory.
			fio: expected to be the file stream corresponding to
			the datafile where the tree is stored on disk
Result:			no return value. TNode is read from datafile to 
			memory.
------------------------------------------------------------------------------*/
template <class Whatever>
void TNode<Whatever> :: Read (const offset & position, fstream * fio) {
	
	// tree is accessed
	Tree<Whatever>::IncrementCost();

	//get current position
	fio->seekg(position);

	//Read form the file to get the TNode
	fio->read((char *)this, sizeof(TNode<Whatever>));

	if (Tree<Whatever>::debug_on) {
			
		cerr <<  COST_READ << (const char *)(data) << "]\n";
	}
}

/*------------------------------------------------------------------------------
Function Name:		TNode
Purpose:		called when reading a tnode present on disk
Description:		This function exists to read a tnode present on the
			disk into memory.
Input:			position: expected to be the offset in the data 
			corresponding to the position of the tnode we wish
			to read into memory.
			fio: expected to be the file stream corresponding to
			the datafile where the tree is stored on disk
Result:			No return value.
------------------------------------------------------------------------------*/
template <class Whatever>
TNode<Whatever> :: TNode (const offset & position, fstream * fio) {

	// calls read to get tnode from datafile
	Read(position, fio);
}

/*------------------------------------------------------------------------------
Function Name:		TNode
Purpose:		called when creating a TNode for the first time.
Description:		This function exists to be called when creating a
			TNode for the first time.
Input:			element: The data to be stored in the TNode. Must
			be the same type as the rest of the objects present
			in the tree.
			fio: expected to be the file stream corresponding to
			the datafile where the tree is stored on disk
			occupancy: Expected to be a reference to the occupancy
			to the tree to which the new node is being added.
Result:			No return value.
------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------
Function Name:		Write
Purpose:		Writes the TNode object to disk at this_position in the
			datafile.
Description:		This function exists writes the TNode object to disk at 
			this_position in the datafile.
Input:			fio: expected to be the file stream corresponding to
			the datafile where the tree is stored on disk
Result:			No return value.
------------------------------------------------------------------------------*/
template <class Whatever>
void TNode<Whatever> :: Write (fstream * fio) const {

	// tree is accessed
	Tree<Whatever>::IncrementCost();

	//get current position
	fio->seekp(this_position);

	//Read form the file to get the TNode
	fio->write((char *)this, sizeof(TNode<Whatever>));

	if (Tree<Whatever>::debug_on) {
			
		cerr <<  COST_WRITE << (const char *)(data) << "]\n";
	}
}

/*------------------------------------------------------------------------------
Function Name:		Tree<Whatever> :: Tree
Purpose:		Called when creating a Tree. Allocates memory for
			the tree
Description:		Guarantee initialization of occupancy and root. It 
			also initializes the tree_count using a static 
			counter.
Input:			No input value.
Result:			No return value.
------------------------------------------------------------------------------*/
template <class Whatever>
Tree<Whatever> :: Tree (const char * datafile) :
	fio (new fstream (datafile, ios :: out | ios :: in)), occupancy(0), 
	root(0), tree_count(0) {

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
		
		//read existing root and occupancy from disk
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

/*------------------------------------------------------------------------------
Function Name		<<
Purpose			This function exists to overload the << opeartor
Description		This function writes the member fields of the node to 
			the stream in a formatted output.
Input			stream: the stream to write to
			nnn: the node to display the information of to stream
Output			The node's member fields are written to stream.
------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------
Function Name		Write_AllTNodes
Purpose			This function exists to display all the tnodes on the 
			disk
Description		This function writes the nodes by reading them from the
			disk if its left or right child exists and then
			recursively writing the left child or right child.
Input			stream: the stream to write to
			fio: the file stream to read from
Output			The tree on the disk is written out.
------------------------------------------------------------------------------*/
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

