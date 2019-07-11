
/*
 * Patient.cpp
 *
 * Class Description: Models a walk-in clinic patient.
 * Class Invariant: Each patient has a unique care card number.
 *                  This care card number must have 10 digits.
 *                  This care card number cannot be modified.
 *
 * Author:  Denys Dziubii and Xubin Wang
 * Date: January 22, 2019
 */
#include "Patient.h"

Patient::Patient()
{
	this->name = "To be entered";
	this->address = "To be entered";
	this->email = "To be entered";
	this->phone = "To be entered";
	this->careCard = "0000000000";

}

Patient::Patient(string aCareCard)
{
	this->name = "To be entered";
	this->address = "To be entered";
	this->email = "To be entered";
	this->phone = "To be entered";
	if(aCareCard.length() != 10)
	{
		this->careCard = "0000000000";
		return;
	}
	this->careCard = aCareCard;
}


string Patient::getName() const
{
	return this->name;
}


string Patient::getAddress() const
{
	return this->address;
}


string Patient::getPhone() const
{
	return this->phone;
}


string Patient::getEmail() const
{
	return this->email;
}


string Patient::getCareCard() const
{
	return this->careCard;
}


void Patient::setName(const string Name)
{
	this->name = Name;
}


void Patient::setAddress(const string anAddress)
{
	this->address = anAddress;
}


void Patient::setPhone(const string aPhone)
{
	this->phone = aPhone;
}


void Patient::setEmail(const string anEmail)
{
	this->email = anEmail;
}


bool Patient::operator == (const Patient & rhs)
{
	if (this->careCard == rhs.getCareCard() )
		return true;
	else
		return false;
}


bool Patient::operator > (const Patient & rhs)
{
	if (this->careCard > rhs.getCareCard() )
		return true;
	else
		return false;

}


ostream& operator << (ostream & os, const Patient & p)
{
	os << p.getCareCard() << " - Patient: ";
	os << p.getName() << ", ";
	os << p.getAddress() << ", ";
	os << p.getPhone() << ", ";
	os << p.getEmail();
	return os;

}
