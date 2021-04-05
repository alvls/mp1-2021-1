#include <iostream>
#include <memory>
#ifndef CLASS_CONTACT
#define CLASS_CONTACT

using namespace std;

class Contact
{
  string firstName;
  string lastName;
  string patronymic;
  string day;
  string month;
  string year;
  string phoneNumber;
  bool favourite;
public:
  Contact();
  Contact(string _firstName, string _lastName, string _patronymic, string _day, string _month, string _year,
    string _phoneNumber, bool _favourite);
  string getFirstName();
  void setFirstName(string _firstName);
  string getLastName();
  void setLastName(string _lastName);
  string getPatronymic();
  void setPatronymic(string _patronymic);
  string getPhoneNumber();
  void setPhoneNumber(string _phoneNumber);
  string getBirthDay();
  void setBirthDay(string _day);
  string getBirthMonth();
  void setBirthMonth(string _month);
  string getBirthYear();
  void setBirthYear(string _year);
  bool favouriteStatus();
  void addContactToFavourites();
  void removeContactFromFavourites();
  void Output();
  void setFavouriteStatus(bool status);
  Contact& operator=(const Contact& object);
};
#endif