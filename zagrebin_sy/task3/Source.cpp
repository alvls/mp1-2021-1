#include <iostream>
#include <string>
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
	void set(int index, string str) {	// SET NAME
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
	void open_menu() {
		string str = "";
		int choice = 0;
		show(5, 5);
		cout << "Enter x to exit" << endl;
		while (str != "x") {
			cin >> str;
			choice = get(str);
			if (choice)
				cout << choice << endl;
			else
				cout << "No such option" << endl;
		}
	}
	int Last() {	// LAST CHOSEN
		return last;
	}
};


int main() {
	int choice = 0, i = 0, j = 0;
	string str;
	Menu menu;
	menu.set_size(3);
	menu.set(1, "First");
	menu.set(2, "Second");
	menu.set(3, "Third");
	menu.open_menu();
}