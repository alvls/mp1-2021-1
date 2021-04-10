#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "ClassContact.h"
#include "ClassContactsStorage.h"
#include <memory>

using namespace std;

int main()
{
  size_t tempvar = 0 ;
  setlocale(LC_ALL, "Russian");
  Contact object1("�����", "���������", "��������", "02", "03", "1977", "89999999999", true);
  contactsStorage storage1;
  storage1.createContact(object1);
  tempvar = storage1.getAmountOfContacts();
  storage1.contactByFullName("�����", "���������", "��������");
  storage1.contactByPhoneNumber("89999999999");
  storage1.everyContactByFirstLetter('�');
  storage1.favouriteContactsOutput();
  storage1.saveContactsToFile();
  storage1.loadContactsFromFile();
  return 0;
}