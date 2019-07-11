/*
 * List.h
 *
 * Class Description: List data collection ADT.
 * Class Invariant: Data collection with the following characteristics:
 *                   - Each element is unique (no duplicates).
 *                   - A capacity of MAX_ELEMENTS
 *                   - CareCard number must only be 10 digits
 *
 * Author:  Denys Dziubii and Xubin Wang
 * Date: January 22, 2019
 */

#pragma once
#include <string>
#include "Patient.h"
using namespace std;
class List
{

private:
	static const int MAX_ELEMENTS = 5; // Small capacity so can test when data collection becomes full
	                                   // ***As we are testing the code of our assignment, we can
	                                   //    change the value given to this constant.***
	Patient elements[MAX_ELEMENTS];    // Data structure with capacity of MAX_ELEMENTS
	int elementCount;                  // Current element count in element array
	int capacity;                      // Actual maximum capacity of element array

public:
	//Description: Default Constructor
	List();

	//Description: Returns the total element count currently stored in List.
	//Postcondition: return the number of Patients in the list
	int  getElementCount() const;

	// Description: Insert an element.
	// Precondition: newElement must not already be in data collection.
	// Postcondition: newElement inserted and elementCount has been incremented.
	bool insert(const Patient& newElement);

	//Description: Removes the element that needs to be removed
	//Precondition: The list is not empty and the element should be in the list, so we run checks on these.
	//Postcondition: Return true if the action was successfull and decrement element count, return false otherwise
	bool remove( const Patient& toBeRemoved );

	//Desctiption: Removes all elements from the list
	//Precondition: if the list is enpty, there would be nothing to remove
	//Postcondition: element count reset to zero
	void removeAll();

	//Description: Searches for a traget element from the list
	//Precondtion: the list is not empty
	//Potsondition: return a pointer to the target element at position elemets[i], returns the null-pointer otherwise
	Patient* search(const Patient& target);

	//Description: Prints the list of Patients with their details present in it
	//Precondtion: the list is not empty
	void printList() const;

	//Description: checks if the card number already exists in the list.
	//Potscondition: returns false if the element is not a duplicate
	bool duplicate(const string& card);


}; // end List.h
