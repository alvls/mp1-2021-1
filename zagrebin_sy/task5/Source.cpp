#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#define period 31
#define period_book 4
using namespace std;

enum err { out_of_range, wrong_date, wrong_parameter, wrong_time
};						//	errors
unsigned months[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Hall{			// booked places on session
private:				// sizes of halls
	unsigned last_id = 0;
public:
	unsigned n_places[2]; // n - booked, 1 - vip
	unsigned *places[2], sizes[2][2];	//	row * number for vip(1) and not
	Hall(unsigned pr, unsigned pn, unsigned vr, unsigned vn) {
		sizes[0][0] = pr; sizes[1][0] = vr; sizes[0][1] = pn; sizes[1][1] = vn;
		for (int i = 0; i < 2; i++)
			places[i] = new unsigned[sizes[i][0]*sizes[i][1]]{ 0 };
	}
	string book(bool vip, unsigned number) {
		string ticket = "Ticket id: " +to_string(++last_id)+ "\nSeats: "; unsigned i, j;
		n_places[vip] += number;
		for(i = 0; i < sizes[vip][0]; i++)
			for (j = 0; j < sizes[vip][1]; j++) {
				if (places[vip][i * sizes[vip][1] + j] == 0) {
					places[vip][i * sizes[vip][1] + j] = last_id;
					ticket += to_string(i) + '/' + to_string(j) + ' ';
					number--;
				}
				if (number == 0)
					break;
			}
		return ticket;
	}
	void cancel(unsigned id, bool vip) {
		int i, j;
		if (id > last_id || id == 0)
			throw err::wrong_parameter;
		for (i = 0; i < sizes[vip][0]; i++)
			for (j = 0; j < sizes[vip][1]; j++)
				if (places[vip][i * sizes[vip][1] + j] == id) {
					places[vip][i * sizes[vip][1] + j] = 0;
					n_places[vip]--;
				}
	}
	~Hall() {
		for (int i = 0; i < 2; i++)
			delete[] places[i];
	}
};
class Time {			// Time
	unsigned hour : 5;
	unsigned min : 11;
public:
	Time() : hour(0), min(0) {};
	Time(int h, int m) {
		if (h > 23 || m > 59)
			throw err::wrong_time;
		hour = h; min = m;
	}
	int operator-(Time t) {
		return (hour-t.hour)*60+(min-t.min);
	}
	bool operator==(Time t) {
		if (t.hour == hour && t.min == min)
			return true;
		else
			return false;
	}
	friend ostream& operator<<(ostream& os, const Time& t);
};
ostream& operator<<(ostream& os, const Time& t) {
	os << t.hour << ':' << t.min;
	return os;
}
struct Film {			// Film
	string name;
	unsigned price[2];	// vip and not
};
class Cinema {			// CINEMA GREAT CLASS
	unsigned n_halls, n_sessions; Time* sessions;
	vector<Film> films;
	//	31 days for playbill * sessions * halls
	unsigned **table[period];	// id of films
	// today + 3 days for booking * sessions * halls ->
	Hall ***booking[period_book];	//
	friend class Booking_office;
public:
	Cinema(unsigned nh, unsigned ns) {
		int i, j;
		n_halls = nh; n_sessions = ns;
		sessions = new Time[ns];
		for (i = 0; i < period; i++) {		// space for playbill
			table[i] = new unsigned*[ns];
			for (j = 0; j < ns; j++)
				table[i][j] = new unsigned[nh];
		}
		for (i = 0; i < period_book; i++) {
			booking[i] = new Hall**[n_sessions];
			for (j = 0; j < n_sessions; j++)
				booking[i][j] = new Hall*[n_halls];
		}
	}
	~Cinema() {
		delete[] sessions;
		int i, j, k;
		for (i = 0; i < period; i++) {
			for (j = 0; j < n_sessions; j++)
				delete[] table[i][j];
			delete[] table[i];
		}
		for (i = 0; i < period_book; i++) {
			for (j = 0; j < n_sessions; j++) {
				for (k = 0; k < n_halls; k++)
					delete booking[i][j][k];
				delete[] booking[i][j];
			}
			delete[] booking[i];
		}
	}
	void set_hall(unsigned id, unsigned pr, unsigned pn, unsigned vr, unsigned vn) {
		int i, j;
		for (i = 0; i < period_book; i++) {
			for (j = 0; j < n_sessions; j++)
				booking[i][j][id] = new Hall(pr, pn, vr, vn);
		}
	}
	unsigned get_n_sessions() { return n_sessions;}
	unsigned get_n_halls() { return n_halls; }
	void add_film(string s, unsigned cost, unsigned v_cost) {
		Film f = { s, cost, v_cost };
		films.push_back(f);
	}
	void set_session_time(unsigned i, Time t) {
		sessions[i] = t;
	}
	void set_film(unsigned date, unsigned session, unsigned hall, unsigned id) {
		if (date > 31 || session > n_sessions || hall > n_halls || id >= films.size())
			throw err::wrong_parameter;
		table[date][session][hall] = id;
	}
};

class Booking_office {	// BOOKING GREAT CLASS
	Cinema* theatre;	// don't delete, not dynamic
	Time time_now;
public:
	Booking_office(Cinema* _theatre) {
		theatre = _theatre;
	}
	void set_time(unsigned h, unsigned m) {
		time_now = Time(h, m);
	}
	void book(unsigned date, unsigned hour, unsigned min, string film,
		unsigned hall, bool vip, unsigned number) {
		bool choice = 0; unsigned month, day, diff_date, 
			session = -1, price = 0;
		time_t t = time(0);   // get time now
		tm* now = localtime(&t);
		month = now->tm_mon + 1; day = now->tm_mday;
		for (int i = 0; i < theatre->n_sessions; i++)
			if (theatre->sessions[i] == Time(hour, min)) {
				session = i;
				break;
			}
		// CHECKING
		if (date > months[month] || hall > theatre->n_halls || 
			session == -1 || number == 0)
			throw err::wrong_parameter;
		if ((date - day > 3) || ((day > date) && (months[month] - day + date > 3))) {
			cout << "Can't book earlier than 3 days in advance\n";
			return;
		}
		if (time_now - theatre->sessions[session] > 10 && date == day) {
			cout << "Sorry, the movie has already started\n";
			return;
		}
		diff_date = (date > day) ? date - day : months[month] - day + date;
		cout << theatre->table[date][session][hall] << endl;
		system("pause");
		if (theatre->films[theatre->table[date][session][hall]].name != film) {
			cout << "There isn't such film\n";
			return;
		}
		// CHECK FREE PLACES
		if (theatre->booking[diff_date][session][hall]->n_places[vip] + number >
			theatre->booking[diff_date][session][hall]->sizes[vip][0] *
			theatre->booking[diff_date][session][hall]->sizes[vip][1]) {
			cout << "No seats available\n";
			return;
		}
		// BORROWING
		cout << "There are places for the session\n";
		double discount = 1;
		if (theatre->sessions[session] - Time(18, 00) >= 0)
			discount = 1.5;
		if (theatre->sessions[session] - Time(12, 00) < 0)
			discount = 0.75;
		price = int(theatre->films[theatre->table[date][session][hall]].price[vip]
			* number * discount);
		cout << "It will cost - " << price << endl;
		cout << "Do you want to borrow?(NO - 0, YES - 1)\n";
		cin >> choice;
		if (!choice)	// NO
			cout << "Okey. See you soon! Bye\n";
		else {			// YES
			cout << "Ticket:\nDate: " << date << '.';
			if (date >= day)
				cout << month;
			else
				cout << (month + 1) % 12;
			cout << "\nTime: " << theatre->sessions[session] << endl;
			cout << "Film: " << theatre->films[theatre->table[date][session][hall]].name
				<< endl;
			cout << "Hall ¹" << hall << endl;
			cout << theatre->booking[diff_date][session][hall]->book(vip, number) << endl;
			cout << "Total price: " << price << endl;
		}
	}
	void canceling(unsigned id, unsigned date, unsigned session,
		unsigned hall, bool vip) {
		unsigned month, day, diff_date;
		time_t t = time(0);   // get time now
		tm* now = localtime(&t);
		month = now->tm_mon + 1; day = now->tm_mday;
		// CHECKING
		if (date > months[month] || 
			session > theatre->n_sessions || hall > theatre->n_halls)
			throw err::wrong_parameter;
		if ((date - day > 3) || ((day > date) && (months[month] - day + date > 3))) {
			throw err::wrong_parameter;
		}
		diff_date = (date > day) ? date - day : months[month] - day + date;
		theatre->booking[diff_date][session][hall]->cancel(id, vip);
	}
};

void main() {
	unsigned i, j, k, n; Time times[] = { {11, 30}, {14, 30}, {16, 30}, {20, 30} };
	
	Cinema theatre(3, 4);	// building theatre

	Booking_office cashbox(&theatre);
	cashbox.set_time(13, 00); // set time

	theatre.set_hall(0, 10, 20, 5, 20);	//	side
	theatre.set_hall(1, 15, 30, 2, 10); // big
	theatre.set_hall(2, 10, 20, 5, 20); // side
		
	theatre.add_film("Blue screen", 100, 150);	// Films
	theatre.add_film("Python in 1 hour", 350, 400);
	theatre.add_film("1 +'1'", 150, 200);
	
	for (i = 0; i < theatre.get_n_sessions(); i++)	// Sessions' time
		theatre.set_session_time(i, times[i]);
	for (i = 0; i < period; i++)	//	add playbill
		for (j = 0; j < theatre.get_n_sessions(); j++)
			for (k = 0; k < theatre.get_n_halls(); k++)
				theatre.set_film(i, j, k, k);
	// ¹hall = ¹film

	cashbox.book(18, 11, 30, "1+'1'", 3, 1, 4);

	system("pause");
}