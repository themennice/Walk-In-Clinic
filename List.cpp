/*
 * List.cpp
 *
 * Class Description: List data collection ADT.
 * Class Invariant: Data collection with the following characteristics:
 *                   - Each element is unique (no duplicates).
 *                   - It has a fixed possible length
 *                   - CareCard number must only be 10 digits
 *
 * Author:  Denys Dziubii and Xubin Wang
 * Date: January 22, 2019
 */

#include "List.h"

List::List()
{
	this->elementCount = 0;
	this->capacity = this->MAX_ELEMENTS;
}

int List::getElementCount() const
{
	return this->elementCount;
}

bool List::insert(const Patient& newElement)
{
	if(this->elementCount >= this->capacity)// check that 0 <= elementCount <= 5
    {
        cout << "The Patient Line is Full Now, Please wait Someone to leave" << endl;
		return false;
    }
	for(int i = 0; i < elementCount-1; i++) // use - 1 since the indeces start at 0
	{
		if(elements[i] == newElement) // check for duplicates
        {
            cout << "The Patient is Already in the Line. Duplicate." << endl;
			return false;
        }
	}
	int index = 0; // initialise the index variable
	if(newElement.getCareCard() < this->elements[0].getCareCard()) // check if the care card number is the smallest of the ones in the list
		index = 0; // so it should be in 1st position
	else if(newElement.getCareCard() > this->elements[this->elementCount - 1].getCareCard())
		index = this->elementCount; /* if the new carecard number is greater than the biggest carecard number in the list,
		and there is 4 elements at most, we set index to element count, so we get the position to put the new Patient*/
	for(int i = 0; i < this->elementCount+1; i++) // find the first instance when the new carecard number is smaller than an old number in the list
	{ //this is possible because we are inserting into the list in ascending order, so it will be sorted at all  times
		//some testing was used to troubleshoot and understand how to implement this without errors
		if(this->elements[i].getCareCard() > newElement.getCareCard())
			{
				index = i;
				break;
			}
	}
	for(int i = this->elementCount; i > index; i--) // iterate through the loop starting at the last present element down to the index
			this->elements[i] = this->elements[i-1]; // and set the next value to be equal to previous Patient value

	this->elements[index] = newElement;// since we stopped at index, it is time to insert a new element into that position
	this->elementCount++; // increase element count as a result of the insert function being performed successfully
	return true;

}


bool List::remove(const Patient& toBeRemoved)
{
	if(this->getElementCount() == 0) // check if there is no elements to be removed i.e. the list is empty
		return false;
	int index = -1; // initialise index
	for(int i = 0;i < this->elementCount; i++) // iterate through the list to find the index of the element to be removed
		if(this->elements[i].getCareCard() == toBeRemoved.getCareCard())
			index = i; // set the index to i, so that we keep track of it
	if(index == -1) // this would mean that index was not set, so the element we are looking for is not in the list, return false
		return false;
	for(int i = index; i < this->elementCount-1; i++)
	{
		this->elements[i] = this->elements[i+1]; //copy over the next element after i = index into the current element, effectively shifting to the left by one
	}
	this->elementCount--; // decrease element count since we removed one element
	this->elements[elementCount] = Patient();// we now have two equal elements at then end of the list, so we set the last one of them to the default value
	return true; //return true, because removing the needed Patient was successfull
}

void List::removeAll()
{
	if(this->getElementCount() == 0) // check if there is no elements to be removed i.e. the list is empty
		return;
	// we are aware of just setting the element count to zero,
	// however, we decided to  go extra safe and set all values to default
	for(int i = 0;i < this->capacity; i++)
	{
		this->elements[i] = Patient(); //run a loop and
	}
	this->elementCount = 0;
}


Patient* List::search(const Patient& target)
{
	if(this->getElementCount() == 0) // check if the list is empty
		return nullptr;
	for(int i = 0; i < this->elementCount; i++)
	{
		if(this->elements[i].getCareCard() == target.getCareCard())
			return &this->elements[i];
	}
	return nullptr;
}


void List::printList() const
{
	if (this->getElementCount() == 0)
		cout << "The list of patients is empty." << endl;
   for(int i = 0; i < this->elementCount; i++) // Don't forget to change to elementCount right before submitiing
   {
     cout << elements[i] << endl;
   }
}


bool List::duplicate(const string& card)
{
	for(int i = 0; i < elementCount; i++)
	{
		if(elements[i].getCareCard() == card)
        {
			return true;
        }
	}
	return false;
}
