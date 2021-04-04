#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include "ClassContact.h"
#ifndef CLASS_CONTACTS_STORAGE
#define CLASS_CONTACTS_STORAGE

using namespace std;


class contactsStorage
{
  vector <Contact> contacts;
public:
  contactsStorage(){}
  ~contactsStorage(){}
  void createContact(const Contact& object);
  size_t getAmountOfContacts();
  void destroyStorage();
  void deleteContact(const int& index);
  void favouriteContactsOutput();
  Contact& operator[](const int& i);
  Contact contactByFullName(string _firstName, string lastName, string patronymic);
  Contact contactByPhoneNumber(string _phoneNumber);
  vector <Contact> everyContactByFirstLetter(char _letter);
  void saveContactsToFile();
  int loadContactsFromFile();
  void storageOutput();
  void changeContact(const int& index, string _firstName, string _lastName, string _patronymic, string _day, string _month, string _year,
      string _phoneNumber, bool _favourite);
};
#endif