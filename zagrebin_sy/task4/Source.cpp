#include <iostream>
#include <fstream>
#include <cstdio>
#include <list>
#include <string>
#include <clocale>
using namespace std;

enum err{out_of_range, wrong_date, wrong_parameter};	//	errors
struct Date_struct {	// date
	unsigned int day    : 5;
	unsigned int month : 4;
	unsigned int year   : 15;
};
int months[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
class Date {
	Date_struct date;
public:
	void set(string s) {
		int d, m, y;
		if (sscanf(s.c_str(), "%02d.%02d.%d", &d, &m, &y) == 3)
			if (y > 0 && y < 10000 && m > 0 && m < 13 && d > 0 && d <= months[m - 1]) {
				date.year = y;
				date.month = m;
				date.day = d;
			}
	}
	string get() {
		string s = to_string(date.day) + '.' + to_string(date.month)
			+ '.' + to_string(date.year);
		return s;
	}
};
struct Song {			// song
	string parameter[6];
	Date date;
};
enum params{name, poet, composer, executor, album, date};// 0 - 5
class Player {			// Player
	list<Song> l;
public:
	~Player() {
		l.clear();
	}
	void add(Song s) {
		bool f = true;
		for (list<Song>::iterator i = l.begin(); i != l.end(); ++i)
			if (i->parameter[0] > s.parameter[0]) {
				l.insert(i, s);
				f = false;
			}
		if (f)
			l.push_back(s);
	}
	void set(int ind, params j, string s) {
		if (ind < 0 || ind > l.size())
			throw err::out_of_range;
		else {
			list<Song>::iterator it = l.begin();
			advance(it, ind - 1);
			if (j == date) {
				it->date.set(s);
			}else {
			it->parameter[j] = s;
			}
		}
	}
	Song search(string _name, string _composer) {	// erase
		Song i;
		for (Song i : l)
			if ((i.parameter[0] == _name) && (i.parameter[2] == _composer))
				break;
		return i;
	}
	list<Song*> get_by_param(params param, string s) {
		list<Song*> tmp;
		if (param < 1 || param > 3)
			throw wrong_parameter;
		else {
			for (list<Song>::iterator i = l.begin(); i != l.end(); ++i)
				if (i->parameter[param] == s)
					tmp.push_back(&(*i));
		}
		return tmp;
	}
	int get_size() {
		return l.size();
	}
	void del(int i) {
		list<Song>::iterator it = l.begin();
		advance(it, i - 1);
		l.erase(it);
	}
	void save(string s) {
		ofstream f(s);
		int j;
		for (list<Song>::iterator i = l.begin(); i != l.end(); ++i) {
			for (j = 0; j < 6; j++)
				f << i->parameter[j] << '\n';
			f << i->date.get() << '\n';
		}
		f.close();
	}
	void load(string s) {
		ifstream f(s); string str; Song song; int i;
		l.clear();
		while (true) {
			for (i = 0; i < 7; i++) {
				if (getline(f, str))
					if (i != 7)
						song.parameter[i] = str;
					else
						song.date.set(str);
			}			

		}
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	Player box;



	system("pause");
}
