#include <iostream>
#include <string>
#include "ClassContact.h"
#include "ClassContactsStorage.h"

using namespace std;

void contactsStorage::createContact(const Contact& object)
{
  contacts.push_back(object);
}

size_t contactsStorage::getAmountOfContacts()
{
 return contacts.size();
}

void contactsStorage::destroyStorage()
{
  contacts.clear();
}

void contactsStorage::favouriteContactsOutput()
{
  for(int i = 0; i < contacts.size(); i++)
    if(contacts[i].favouriteStatus())
      contacts[i].Output();
}

Contact& contactsStorage::operator[](const int& i)
{
  return contacts[i];
}

/* В данной ситуации, и вообще во всех подобных методах, где нужно что-то найти по
 какому-либо признаку, приходится возвращать копию, а не ссылку на объект, т.к.
 если такого контакта нет, то точно нужно что-то вернуть, а возвращать ссылку нет смысла,
 так как объект удалиться после выполнения функции.
 */
Contact contactsStorage::contactByFullName(string _firstName, string _lastName, string _patronymic, bool& indicator)
{
  int i = 0;
  indicator = 0;
  for(i = 0; i < contacts.size(); i++)
    if(contacts[i].getFirstName() == _firstName && contacts[i].getLastName() == _lastName && contacts[i].getPatronymic() == _patronymic)
    {
      indicator = 1;
      contacts[i].Output();
      return contacts[i];
    }  
  if(!indicator)
  { 
    Contact notExistingContact;
    cout << "No such contact!" << endl;
    return notExistingContact; 
  }
}

Contact contactsStorage::contactByPhoneNumber(string _phoneNumber, bool& indicator)
{
  int i = 0;
  indicator = 0;
  for(i = 0; i < contacts.size(); i++)
    if(contacts[i].getPhoneNumber() == _phoneNumber)
    {
      indicator = 1;
      contacts[i].Output();
      return contacts[i];
    }
  if(!indicator)
  {
    Contact notExistingContact;
    cout << "No such contact!" << endl;
    return notExistingContact;
  }
} 

vector <Contact> contactsStorage::everyContactByFirstLetter(char _letter, bool& indicator)
{
  int i = 0;
  indicator = 0;
  vector <Contact> tempVector;
  for(i = 0; i < contacts.size(); i++)
    if(contacts[i].getFirstName()[0] == _letter)
    {
      contacts[i].Output();
      tempVector.push_back(contacts[i]);
    }
  if(tempVector.size())
    indicator = 1;
  return tempVector;
}

void contactsStorage::saveContactsToFile()
{
  ofstream fileout;
  int i = 0;
  fileout.open("Contacts.txt");
  for(i = 0; i < contacts.size(); i++)
  {
    fileout << contacts[i].getFirstName() << " ";
    fileout << contacts[i].getLastName() << " ";
    fileout << contacts[i].getPatronymic() << " ";
    fileout << contacts[i].getBirthDay() << " ";
    fileout << contacts[i].getBirthMonth() << " ";
    fileout << contacts[i].getBirthYear() << " ";
    fileout << contacts[i].getPhoneNumber() << " ";
    if(contacts[i].favouriteStatus())
      fileout << "1";
    else
      fileout << "0";
    fileout << endl;
  }
  fileout.close();
}

int contactsStorage::loadContactsFromFile()
{
  ifstream filein;
  int i = 0;
  string tempstr;
  bool tempbool;
  Contact tempContact;
  filein.open("Contacts.txt");
  if(!filein.is_open())
  {
    cout << "No such file!" << endl;
    return 0;
  }
  while(!filein.eof())
  {
    filein >> tempstr;
    tempContact.setFirstName(tempstr);
    filein >> tempstr;
    tempContact.setLastName(tempstr);
    filein >> tempstr;
    tempContact.setPatronymic(tempstr);
    filein >> tempstr;
    tempContact.setBirthDay(tempstr);
    filein >> tempstr;
    tempContact.setBirthMonth(tempstr);
    filein >> tempstr;
    tempContact.setBirthYear(tempstr);
    filein >> tempstr;
    tempContact.setPhoneNumber(tempstr);
    filein >> tempbool;
    if(tempbool)
      tempContact.addContactToFavourites();
    else
      tempContact.removeContactFromFavourites();
    contacts.push_back(tempContact);
  }
  contacts.pop_back();
  filein.close();
  return 1;
}

void contactsStorage::storageOutput()
{
  int i = 0;
  for(i = 0; i < contacts.size(); i++)
  {
    contacts[i].Output();
    cout << endl;
  }
}

void contactsStorage::deleteContact(const int index)
{
  contacts.erase(contacts.begin() + index);
}

void contactsStorage::changeContact(const int& index, string _firstName, string _lastName, string _patronymic, string _day, string _month, string _year,
    string _phoneNumber, bool _favourite)
{
  contacts[index].setFirstName(_firstName);
  contacts[index].setLastName(_lastName);
  contacts[index].setPatronymic(_patronymic);
  contacts[index].setBirthDay(_day);
  contacts[index].setBirthMonth(_month);
  contacts[index].setBirthYear(_year);
  contacts[index].setPhoneNumber(_phoneNumber);
  contacts[index].setFavouriteStatus(_favourite);
  }

size_t contactsStorage::getIndex(const Contact& object)
{
  int i = 0;
  for(i = 0; i < contacts.size(); i++)
    if(object.getPhoneNumber() == contacts[i].getPhoneNumber())
      return i;
}
