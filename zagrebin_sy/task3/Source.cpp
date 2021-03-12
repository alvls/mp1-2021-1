#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

class Menu {
private:
	int size = 0, last = 0;
	string *names = nullptr;
public:
	Menu() {
		size = last = 0;
		names = nullptr;
	}
	~Menu() {
		delete []names;
	}
	void show(int x, int y) {	// SHOW MENU
		system("cls");
		int i;
		for (i = 0; i < y; i++)
			cout << '\n';
		for (i = 0; i < x; i++)
			cout << ' ';
		cout << '<';
		for (i = 0; i < size; i++)
			cout << "| " << names[i] << " |";
		cout << ">\n";
	}
	void set_size(int _size) {	// SET SIZE
		if (_size > 0) {
			size = _size;
			delete[]names;
			names = new string[size];
			for (int i = 0; i < size; i++)
				names[i] = "";
		}else
			cout << "*Error* Size can't be less than 1\n";
	}
	int get_size() {	// GET SIZE
		return size;
	}
	void set(int index, string &str) {	// SET NAME
		if (index < 1 || index > size)	// numbers are natural 
			cout << "*Error* Index out of range\n";
		else
			names[index - 1] = str;
	}
	int get(string &str) {	// CHOOSE ITEM - RETURN INDEX
		int i;
		for (i = size - 1; i >= 0; i--)
			if (names[i] == str)
				break;
		last = i + 1;
		return i + 1;	// RETURN 0 IF NOT FOUND
	}
	int Last() {	// LAST CHOSEN
		return last;
	}
};


int main() {
	int choice = 0, i = 0, j = 0;
	string str;
	Menu menu;

	while (1) {
		system("cls");
		cout << "Instruction: \n";
		cout << "x - exit \n";
		cout << "SPACE - show instruction\n";
		cout << "1 - set number of commands \n";
		cout << "2 - get number of commands \n";
		cout << "3 - set name for i field \n";
		cout << "4 - set position of the window and show \n";
		cout << "5 - get field's index \n";
		cout << "6 - get last chosen \n";
		cout << "(check your language)\n";
		cout << "\nPress any corrent button\n";

		choice = _getch();
		if (choice == 224)	// IF SPECIALS KEYS
			choice = _getch();

		switch (choice) {
		case 49:		// 1
			cout << "Enter size: ";
			cin >> i;
			menu.set_size(i);
			break;
		case 50:		// 2
			cout << "Size: " << menu.get_size();
			break;
		case 51:		// 3
			cout << "Enter index: ";
			cin >> i;
			cout << "Enter name:\n";
			cin.ignore();
			getline(cin, str);
			menu.set(i, str);
			break;
		case 52:		// 4
			cout << "Enter x: ";
			cin >> i;
			cout << "Enter y: ";
			cin >> j;
			menu.show(i, j);
			break;
		case 53:		// 5
			cout << "Enter name of field: ";
			cin >> str;
			cout << menu.get(str);
			break;
		case 54:		// 6
			cout << "Last chosen: " << menu.Last();
			break;
		case 120:		// x-exit
			return 0;
		default:
			cout << "No such option\n";
		}
		cout << "\nTap to continue";
		_getch();
	}
}