#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

enum err { out_of_range, wrong_date, wrong_parameter, wrong_time
};	//	errors
int months[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
struct Hall {	// uses in creating place number
	unsigned places_size[2], vip_size[2]; // row and number
};
struct Session{	// booked places on session
	unsigned id_film;
	bool **places, **vip;
	Session(unsigned pr, unsigned pn, unsigned vr, unsigned vn) {
		int i, j;
		for (i = 0; i < pr; i++)
			places[i] = new bool[pn];
		for (i = 0; i < vr; i++)
			places[i] = new bool[vn];
	}
};
class Time {	// Time
	unsigned hour : 5;
	unsigned min : 11;
public:
	Time() : hour(0), min(0) {};
	Time(int h, int m) {
		if (h > 23 || m > 59)
			throw err::wrong_time;
		hour = h; min = m;
	};
};
struct Film {	// Film
	string name;
	unsigned price;
};
class Cinema {	// CINEMA GREAT CLASS
	Hall* halls; unsigned n_halls, n_sessions; Time* sessions;
	vector<Film> films;
	//	31 days for playbill * sessions * halls
	unsigned **table[31];	
	// 3 days for booking * sessions * halls
	Session **reserve[3];	
	friend class Booking_office;
public:
	Cinema(unsigned nh, unsigned ns) {
		int i, j;
		n_halls = nh; n_sessions = ns;
		halls = new Hall[nh];
		sessions = new Time[ns];
		for (i = 0; i < 31; i++) {	// space for playbill
			table[i] = new unsigned*[ns];
			for (j = 0; j < ns; j++)
				table[i][j] = new unsigned[nh];
		}
	}
	unsigned n_halls() { return n_halls; }
	unsigned n_sessions() { return n_sessions; }
	void set_hall(unsigned i, unsigned pr, unsigned pn, unsigned vr, unsigned vn) {
		int i, j;
		halls[i].places_size[0] = pr;
		halls[i].places_size[1] = pn;
		halls[i].vip_size[0] = vr;
		halls[i].vip_size[1] = vn;
		for (i = 0; i < 3; i++) {
			reserve[i] = new Session*[n_sessions];
			for (j = 0; j < n_halls; j++)
				reserve[i][j] = new Session(pr, pn, vr, vn);
		}
	}
	void add_film(string s, unsigned cost) {
		Film f = { s, cost };
		films.push_back(f);
	}
	void set_film(unsigned date, unsigned session, unsigned hall, unsigned id) {
		if (date > 31 || session > n_sessions || hall > n_halls || id > films.size())
			throw err::wrong_parameter;
		table[date][hall][session] = id;
	}
};

class Booking_office {	// BOOKING GREAT CLASS
public:
	void book(unsigned char date, unsigned char session, string film, 
		unsigned char hall, bool vip, unsigned short n) {
		const time_t tm = time(nullptr);
		int d, m, h, min;
		char buf[12]; bool choice = 0;
		strftime(buf, size(buf), "%d.%m-%H:%M", localtime(&tm));
		sscanf_s(buf, "%d.%d-%d:%d", &d, &m, &h, &min);
		if (date > months[m] || session > sessions || hall > halls || n == 0)
			throw err::wrong_parameter;
		if ((date - d > 3) || ((d > date) && (months[m] - d + date > 3))) {
			cout << "Can't book earlier than 3 days in advance\n";
			return;
		}
		if (films[theatre.table[date][hall][session].id_film].name
			!= film) {
			cout << "There isn't such film\n";
			return;
		}
		if (theatre.table[date][hall][session].place[vip] + n < places[vip]) {
			cout << "There are places for the session\n";
			cout << "Do you want to borrow?\n";
			cin >> choice;
			if (!choice)
				cout << "See you soon!\n";
			else {
				theatre.table[date][hall][session].place[vip] += n;
				cout << "Your ticket:\n";
				cout << "Date: " << d << '.' << m << endl;
				cout << "Session: " << times[session][0] << 
					':' << times[session][1] << endl;
				cout << film << endl;
				cout << "Hall ¹" << hall << endl;
				cout << "Your place (row/¹):";
				cout << (theatre.table[date][hall][session].place[vip] - n + 1) / row[vip]
					<< '/' << (theatre.table[date][hall][session].place[vip] - n + 1) % row[vip];
				if (n != 1) {
					cout << '-' << (theatre.table[date][hall][session].place[vip]) / row[vip]
						<< '/' << (theatre.table[date][hall][session].place[vip]) % row[vip];
				}
				cout << endl;
				cout << "Price: "
					<< n * films[theatre.table[date][hall][session].id_film].price << endl;
			}
		}
	}
	
};
Booking_office cashbox;


int main() {
	int i, j, k, n;
	Cinema theatre(3, 4);	// building theatre
	theatre.set_hall(0, 10, 20, 5, 20);	//	front
	theatre.set_hall(1, 15, 30, 2, 10); // big
	theatre.set_hall(2, 10, 20, 5, 20); // front
	theatre.add_film("Blue screen", 100);
	theatre.add_film("C++ in 20 hour", 350);
	theatre.add_film("JS. How to 1 + '2'", 150);
	for (i = 0; i < 31; i++) {	//	add playbill
		for (j = 0; j < theatre.n_sessions(); j++)
			for (k = 0; k < theatre.n_halls(); k++)
				theatre.set_film(i, j, k, k);
	}

	//cashbox.book();

	system("pause");
	return 0;
}