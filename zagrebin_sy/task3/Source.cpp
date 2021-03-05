#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

class Menu {
private:
	int size = 0, last = 0;
	string *a = nullptr;
public:
	Menu() {
		size = last = 0;
		a = nullptr;
	}
	~Menu() {
		delete []a;
	}
	void show(int x, int y) {
		system("cls");
		int i;
		for (i = 0; i < y; i++)
			cout << '\n';
		for (i = 0; i < x; i++)
			cout << ' ';
		cout << '<';
		for (i = 0; i < size; i++)
			cout << "| " << a[i] << " |";
		cout << ">\n";
	}
	void set_size(int _size) {
		if (_size > 0) {
			size = _size;
			delete[]a;
			a = new string[size];
			for (int i = 0; i < size; i++)
				a[i] = "";
		}
	}
	int get_size() {
		return size;
	}
	void set(int i, string &_s) {
		if (i > size || i < 1)
			cout << "*Error* Index out of range\n";
		else
			a[i - 1] = _s;
	}
	int get(string &str) {
		int i;
		for (i = size - 1; i >= 0; i--)
			if (a[i] == str)
				break;
		return i + 1;
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
		cout << "(check your language)\n";
		cout << "\nPress the button\n";

		choice = _getch();
		if (choice == 224) 
			choice = _getch();

		switch (choice) {
		case 49:		// 1
			cout << "Enter size: ";
			cin >> i;
			menu.set_size(i);
			break;
		case 50:		// 2
			cout << "Size: " << menu.get_size() << endl;
			_getch();
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
			cout << "Tap to continue\n";
			_getch();
			break;
		case 53:		// 5
			cout << "Enter index: ";
			cin >> str;
			cout << menu.get(str);
			_getch();
			break;
		case 120:		// x-exit
			return 0;
		default:
			cout << "No such option\n";
			_getch();
		}
	}
}