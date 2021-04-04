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
  setlocale (LC_ALL, "Russian");
  Contact object1("����", "������", "��������", "09", "10", "1997", "89990612689", true);
  Contact object3("�����", "������", "��������", "09", "10", "1997", "89990612688", false);
  //Contact object2("�������", "������", "��������", "09", "10", "1997", "89990612688", false);
  contactsStorage storage1;
  storage1.createContact(object1);
  storage1.createContact(object3);
  storage1.deleteContact(0);
  storage1.storageOutput();
  setlocale(LC_ALL, "Russian");
  return 0;
}