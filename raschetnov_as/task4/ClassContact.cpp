#include <iostream>
#include "ClassContact.h"
#include "ClassContactsStorage.h"
using namespace std;

Contact::Contact()
{
  firstName = "DEFAULT_FIRST_NAME";
  lastName = "DEFAULT_LAST_NAME";
  patronymic = "DEFAULT_PATRONYMIC";
  day = "00";
  month = "00";
  year = "0000";
  phoneNumber = "00000000000";
  favourite = false;
}

Contact::Contact(string _firstName, string _lastName, string _patronymic, string _day, string _month, string _year,
    string _phoneNumber, bool _favourite)
{
  firstName = _firstName;
  lastName = _lastName;
  patronymic = _patronymic;
  day = _day;
  month = _month;
  year = _year;
  phoneNumber = _phoneNumber;
  favourite = _favourite;
}

void Contact::Output()
{
  cout << "Person's name: " << firstName << endl;
  cout << "Person's last name: " << lastName << endl;
  cout << "Person's patronymic: " << patronymic << endl;
  cout << "Person's date of birth: " << day << "\\" << month << "\\" << year << endl;
  cout << "Person's phone number: " << phoneNumber << endl;
  cout << "Is person in a list of favourites ? ";
  if (favourite)
    cout << "Yes" << endl;
  else
    cout << "No" << endl;
  cout << endl;
}

void Contact::addContactToFavourites()
{
  favourite = true;
}

void Contact::removeContactFromFavourites()
{
  favourite = 0;
}

bool Contact::favouriteStatus()
{
  return favourite;
}

string Contact::getFirstName()
{
  return firstName;
}

string Contact::getLastName()
{
  return lastName;
}

string Contact::getPatronymic()
{
  return patronymic;
}

string Contact::getPhoneNumber()
{
  return phoneNumber;
}

string Contact::getBirthDay()
{
  return day;
}

string Contact::getBirthMonth()
{
  return month;
}

string Contact::getBirthYear()
{
  return year;
}

void Contact::setFirstName(string _firstName)
{
  firstName = _firstName;
}

void Contact::setLastName(string _lastName)
{
  lastName = _lastName;
}

void Contact::setPatronymic(string _patronymic)
{
  patronymic = _patronymic;
}

void Contact::setPhoneNumber(string _phoneNumber)
{
  phoneNumber = _phoneNumber;
}

void Contact::setBirthDay(string _day)
{
  day = _day;
}

void Contact::setBirthMonth(string _month)
{
  month = _month;
}

void Contact::setBirthYear(string _year)
{
  year = _year;
}

void Contact::setFavouriteStatus(bool status)
{
  favourite = status;
}

Contact& Contact::operator=(const Contact& object)
{
  if(this == &object)
    return *this;
  firstName = object.firstName;
  lastName = object.lastName;
  patronymic = object.patronymic;
  day = object.day;
  month = object.month;
  year = object.year;
  phoneNumber = object.phoneNumber;
  favourite = object.favourite;
  return *this;
}