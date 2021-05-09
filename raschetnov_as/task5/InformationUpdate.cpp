#define _CRT_NONSTDC_NO_DEPRECATE
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <direct.h>
#include "Menu.h"

using namespace std;

void deleteExtraFolders(int& counter)
{
  ifstream filein;
  bool flag = 0;
  string tempstring;
  string path = "Days1\\";
  string pathcopy = "Days1\\";
  string pathtoinfo = "Days1\\CurrentInfo.txt";
  filein.open(pathtoinfo);
  while(!flag)
  {
    filein >> tempstring;
    if (tempstring == getDate1())
      flag = true;
    counter++;
  }
  filein.close();
  filein.open(pathtoinfo);
  for (int i = 0; i < counter - 1; i++)
  {
    filein >> tempstring;
    pathcopy += tempstring;
    filesystem::remove_all(pathcopy);
    pathcopy = path;
  }
  filein.close();
}

void initFolders(string pathcopy)
{
  int i = 0;
  ofstream fileout;
  string path = "Days1\\";
  string path1 = pathcopy;
  string defaultpath = "Days1\\Default\\";
  string defaultpathcopy = "Days1\\Default\\";
  string cars[12] = {"\\Car1.txt", "\\Car2.txt", "\\Car3.txt", "\\Car4.txt", "\\Car5.txt", "\\Car6.txt", "\\Car7.txt", "\\Car8.txt", "\\Car9.txt", "\\Car10.txt", "\\Car11.txt", "\\Car12.txt"};
  mkdir((path1 += "\\Lastochka0929NN").c_str());
  fileout.open(path1 += "\\Clients.txt");
  fileout.close();
  path1 = pathcopy;
  path1 += "\\Lastochka0929NN";
  for (i = 0; i < 10; i++)
  {
    path1 += cars[i];
    defaultpathcopy += "DefaultLastochka.txt";
    filesystem::copy_file(defaultpathcopy, path1);
    defaultpathcopy = defaultpath;
    path1 = pathcopy;
    path1 += "\\Lastochka0929NN";
  }
  path1 = pathcopy;
  mkdir((path1 += "\\Lastochka1331NN").c_str());
  fileout.open(path1 += "\\Clients.txt");
  fileout.close();
  path1 = pathcopy;
  path1 += "\\Lastochka1331NN";
  for (i = 0; i < 10; i++)
  {
    path1 += cars[i];
    defaultpathcopy += "DefaultLastochka.txt";
    filesystem::copy_file(defaultpathcopy, path1);
    defaultpathcopy = defaultpath;
    path1 = pathcopy;
    path1 += "\\Lastochka1331NN";
  }
  path1 = pathcopy;
  mkdir((path1 += "\\Lastochka1755NN").c_str());
  fileout.open(path1 += "\\Clients.txt");
  fileout.close();
  path1 = pathcopy;
  path1 += "\\Lastochka1755NN";
  for (i = 0; i < 10; i++)
  {
    path1 += cars[i];
    defaultpathcopy += "DefaultLastochka.txt";
    filesystem::copy_file(defaultpathcopy, path1);
    defaultpathcopy = defaultpath;
    path1 = pathcopy;
    path1 += "\\Lastochka1755NN";
  }
  path1 = pathcopy;
  mkdir((path1 += "\\Firmennii1514NN").c_str());
  fileout.open(path1 += "\\Clients.txt");
  fileout.close();
  path1 = pathcopy;
  path1 += "\\Firmennii1514NN";
  for (i = 0; i < 4; i++)
  {
    path1 += cars[i];
    defaultpathcopy += "DefaultReserved.txt";
    filesystem::copy_file(defaultpathcopy, path1);
    defaultpathcopy = defaultpath;
    path1 = pathcopy;
    path1 += "\\Firmennii1514NN";
  }
  for (i = 4; i < 10; i++)
  {
    path1 += cars[i];
    defaultpathcopy += "DefaultCoupe.txt";
    filesystem::copy_file(defaultpathcopy, path1);
    defaultpathcopy = defaultpath;
    path1 = pathcopy;
    path1 += "\\Firmennii1514NN";
  }
  for (i = 10; i < 12; i++)
  {
    path1 += cars[i];
    defaultpathcopy += "DefaultLuxe.txt";
    filesystem::copy_file(defaultpathcopy, path1);
    defaultpathcopy = defaultpath;
    path1 = pathcopy;
    path1 += "\\Firmennii1514NN";
  }
  path1 = pathcopy;
  mkdir((path1 += "\\Skorii1824NN").c_str());
  fileout.open(path1 += "\\Clients.txt");
  fileout.close();
  path1 = pathcopy;
  path1 += "\\Skorii1824NN";
  for (i = 0; i < 8; i++)
  {
    path1 += cars[i];
    defaultpathcopy += "DefaultReserved.txt";
    filesystem::copy_file(defaultpathcopy, path1);
    defaultpathcopy = defaultpath;
    path1 = pathcopy;
    path1 += "\\Skorii1824NN";  
  }
  for (i = 8; i < 12; i++)
  {
    path1 += cars[i];
    defaultpathcopy += "DefaultCoupe.txt";
    filesystem::copy_file(defaultpathcopy, path1);
    defaultpathcopy = defaultpath;
    path1 = pathcopy;
    path1 += "\\Skorii1824NN";  
  }
  path1 = pathcopy;
  mkdir((path1 += "\\Lastochka0929MSK").c_str());
  fileout.open(path1 += "\\Clients.txt");
  fileout.close();
  path1 = pathcopy;
  path1 += "\\Lastochka0929MSK";
  for (i = 0; i < 10; i++)
  {
    path1 += cars[i];
    defaultpathcopy += "DefaultLastochka.txt";
    filesystem::copy_file(defaultpathcopy, path1);
    defaultpathcopy = defaultpath;
    path1 = pathcopy;
    path1 += "\\Lastochka0929MSK";
  }
  path1 = pathcopy;
  mkdir((path1 += "\\Lastochka1331MSK").c_str());
  fileout.open(path1 += "\\Clients.txt");
  fileout.close();
  path1 = pathcopy;
  path1 += "\\Lastochka1331MSK";
  for (i = 0; i < 10; i++)
  {
    path1 += cars[i];
    defaultpathcopy += "DefaultLastochka.txt";
    filesystem::copy_file(defaultpathcopy, path1);
    defaultpathcopy = defaultpath;
    path1 = pathcopy;
    path1 += "\\Lastochka1331MSK";
  }
  path1 = pathcopy;
  mkdir((path1 += "\\Lastochka1755MSK").c_str());
  fileout.open(path1 += "\\Clients.txt");
  fileout.close();
  path1 = pathcopy;
  path1 += "\\Lastochka1755MSK";
  for (i = 0; i < 10; i++)
  {
    path1 += cars[i];
    defaultpathcopy += "DefaultLastochka.txt";
    filesystem::copy_file(defaultpathcopy, path1);
    defaultpathcopy = defaultpath;
    path1 = pathcopy;
    path1 += "\\Lastochka1755MSK";
  }
  path1 = pathcopy;
  mkdir((path1 += "\\Firmennii1514MSK").c_str());
  fileout.open(path1 += "\\Clients.txt");
  fileout.close();
  path1 = pathcopy;
  path1 += "\\Firmennii1514MSK";
  for (i = 0; i < 4; i++)
  {
    path1 += cars[i];
    defaultpathcopy += "DefaultReserved.txt";
    filesystem::copy_file(defaultpathcopy, path1);
    defaultpathcopy = defaultpath;
    path1 = pathcopy;
    path1 += "\\Firmennii1514MSK";
  }
  for (i = 4; i < 10; i++)
  {
    path1 += cars[i];
    defaultpathcopy += "DefaultCoupe.txt";
    filesystem::copy_file(defaultpathcopy, path1);
    defaultpathcopy = defaultpath;
    path1 = pathcopy;
    path1 += "\\Firmennii1514MSK";
  }
  for (i = 10; i < 12; i++)
  {
    path1 += cars[i];
    defaultpathcopy += "DefaultLuxe.txt";
    filesystem::copy_file(defaultpathcopy, path1);
    defaultpathcopy = defaultpath;
    path1 = pathcopy;
    path1 += "\\Firmennii1514MSK";
  }
  path1 = pathcopy;
  mkdir((path1 += "\\Skorii1824MSK").c_str());
  fileout.open(path1 += "\\Clients.txt");
  fileout.close();
  path1 = pathcopy;
  path1 += "\\Skorii1824MSK";
  for (i = 0; i < 8; i++)
  {
    path1 += cars[i];
    defaultpathcopy += "DefaultReserved.txt";
    filesystem::copy_file(defaultpathcopy, path1);
    defaultpathcopy = defaultpath;
    path1 = pathcopy;
    path1 += "\\Skorii1824MSK";
  }
  for (i = 8; i < 12; i++)
  {
    path1 += cars[i];
    defaultpathcopy += "DefaultCoupe.txt";
    filesystem::copy_file(defaultpathcopy, path1);
    defaultpathcopy = defaultpath;
    path1 = pathcopy;
    path1 += "\\Skorii1824MSK";
  }
  path1 = pathcopy;
}

void addNewFolders(int counter)
{
  int i = 0;
  ifstream filein;
  string tempstring;
  string path = "Days1\\";
  string pathcopy = "Days1\\";
  string pathtoinfo = "Days1\\CurrentInfo.txt";
  filein.open(pathtoinfo);
  for (i = 0; i < 30 - (counter - 1); i++)
  {
    filein >> tempstring;
  }
  for(i; i < 30 ;i++)
  {
    filein >> tempstring;
    pathcopy += tempstring;
    mkdir(pathcopy.c_str());
    initFolders(pathcopy);
    pathcopy = path;
  }
  filein.close();
}

bool currentInfoUpdate(int counter)
{
  int i = 0;
  int j = 0;
  ifstream filein;
  ofstream fileout;
  string tempstring;
  string path = "Days1\\";
  string pathcopy = "Days1\\";
  string pathtoinfo = "Days1\\CurrentInfo.txt";
  string pathtostorage = "Days1\\Storage.txt";
  string oldname = "Days1\\CurrentInfoTemp.txt";
  string newname = "Days1\\CurrentInfo.txt";
  size_t indicator;
  string tmp;
  if(counter == 1)
    return true;
  filein.open(pathtoinfo);
  fileout.open(pathcopy += "CurrentInfoTemp.txt");
  for(i = 0; i < counter - 1; i++)
    filein >> tempstring;
  for(i; i < 30 - (counter - 1); i++)
  {
    filein >> tempstring;
    fileout << tempstring << endl;
  }
  pathcopy = path;
  filein.close();
  filein.open(pathtostorage);
  filein >> tmp;
  while (tempstring != tmp)
  {
    filein >> tmp;
  }
  for (i = 0; i < counter - 1; i ++)
  {
    filein >> tmp;
    fileout << tmp << endl;
  }
  filein >> tmp;
  fileout << tmp;
  filein.close();
  fileout.close();
  remove(pathtoinfo.c_str());
  indicator = rename(oldname.c_str(), newname.c_str());
  return true;
}