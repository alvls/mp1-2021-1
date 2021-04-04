#include <iostream>
#include <fstream>
#include <cstdio>
#include <list>
#include <vector>
#include <string>
#include <clocale>
using namespace std;

enum err{out_of_range, wrong_date, wrong_parameter};	//	errors
int months[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };	// Date
class Date {
	unsigned int day : 5;
	unsigned int month : 4;
	unsigned int year : 15;
public:
	Date() {
		day = month = year = 0;
	}
	void operator=(string s) {
		int d, m, y;
		if (sscanf_s(s.c_str(), "%d.%d.%d", &d, &m, &y) == 3 &&
		y > 0 && m > 0 && m < 13 && d > 0 && d <= months[m - 1]) {
			day = d;
			month = m;
			year = y;
		}else
			throw err::wrong_date;
	}
	void operator=(const char* s) {
		int d, m, y;
		if (sscanf_s(s, "%d.%d.%d", &d, &m, &y) == 3 &&
			y > 0 && m > 0 && m < 13 && d > 0 && d <= months[m - 1]) {
			day = d;
			month = m;
			year = y;
		}
		else
			throw err::wrong_date;
	}
	string get() {
		string s = to_string(day) + '.' + to_string(month)
			+ '.' + to_string(year);
		return s;
	}
};
enum params{name, poet, composer, executor, album, date};// Song 0 - 5
struct Song {			
	string parameter[5];
	Date date;
};
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
				break;
			}
		if (f)
			l.push_back(s);
	}
	void set(int ind, params param, string s) {
		if (ind < 0 || ind > l.size())
			throw err::out_of_range;
		else {
			list<Song>::iterator it = l.begin();
			advance(it, ind - 1);
			if (param == date)
				it->date = s;
			else
				it->parameter[param] = s;
		}
	}
	Song* search(string _name, string _composer) {
		for (list<Song>::iterator i = l.begin(); i != l.end(); ++i)
			if ((i->parameter[0] == _name) && (i->parameter[2] == _composer))
				return &(*i);
		return nullptr;
	}
	vector<Song*> get_by_param(params param, string s) {
		vector<Song*> tmp;
		if (param < 1 || param > 3)
			throw err::wrong_parameter;
		for (list<Song>::iterator i = l.begin(); i != l.end(); ++i)
			if (i->parameter[param] == s)
				tmp.push_back(&(*i));
		return tmp;
	}
	int get_size() {
		return l.size();
	}
	void del(int i) {
		if (i < 0 || i > l.size() - 1)
			throw err::out_of_range;
		list<Song>::iterator it = l.begin();
		advance(it, i - 1);
		l.erase(it);
	}
	void save(string s) {
		ofstream f(s);
		int j;
		for (list<Song>::iterator i = l.begin(); i != l.end(); ++i) {
			for (j = 0; j < 5; j++)
				f << i->parameter[j] << '\n';
			f << i->date.get();
		}
		f.close();
	}
	void load(string s) {
		ifstream f(s); string str; Song song; int i;
		l.clear();
		while (getline(f, str)) {
			for (i = 0; i < 5; i++) {
				song.parameter[i] = str;
				getline(f, str);
			}
			song.date = str;
			l.push_back(song);
		}
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	Player box; Song song; string s = "";
	box.load("player.txt");
	song = {"Автор", "Поэт", "Композитор", "Исполнитель", "Альбом"};
	song.date = "14.11.2002";
	box.add(song);
	box.save("player.txt");
	system("pause");
}
