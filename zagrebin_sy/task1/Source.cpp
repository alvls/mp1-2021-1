#include <iostream>

using namespace std;

class long_number {
private:
	int p1;
	unsigned int p2;
public:
	long_number() {
		p1 = p2 = 0;
	}
	void set() {	//SET
		long int x;
		cin >> x;
		p1 = x >> (sizeof(long) * 4);
		p2 = x;
	}
	void show() {	//SHOW
		long x = long((long(p1) << (sizeof(long) * 4)) | p2);
		cout << x << '\n';
	}
	int get1() {	//GET and SET P1
		return p1;
	}
	void set1(int x) {
		p1 = x;
	}
	unsigned int get2() {	//GET and SET P2
		return p2;
	}
	void set2(unsigned int x) {
		p2 = x;
	}

	long_number inv() {				// -x
		long_number r;
		//r.set1(~p1 + (long(~p2) & 0x0000ffff + 1) >> (sizeof(long) * 4));
		r.set2(~p2 + 1);
		return r;
	}
	long_number add(long_number x) {	// +
		long_number r;
		r.set2(p2 + x.get2());
		//r.set1(p1+ x.get1() + long(p2 + x.get2()) >> (sizeof(long) * 4));
		return r;
	}
	long_number sub(long_number x) {	// -
		long_number r;
		x = x.inv();
		r.set2(p2 + x.get2());	// p1: But what about me?(
		//r.set1(p1+ x.get1() + long(p2 + x.get2()) >> (sizeof(long) * 4));
		return r;
	}
	long_number mult(long_number x) {	// *
		long_number r;
		r.set2(p2 * x.get2());
		r.set1(p1 * x.get2() + p2 * x.get1());// (*~*)

		return r;
	}
	long_number div(long_number x) {	// /
		long_number r;
		if (x.get2() == 0)
			cout << "Division by Zero\n";
		else
			r.set2(p2 / x.get2());
		//r.set1(p1 * x.get2() + p2 * x.get1()); (0_0) OK.

		return r;
	}
};

void main() {
	long_number n1, n2, n3;
	int mode, again = 1;
	while (again) {
		system("cls");
		cout << "Long range:" << (1 << 31) << " to " << ~(1 << 31) << '\n';
		cout << "Choose example :\n";
		cout << "1 Inversion\n";
		cout << "2 Adding\n";
		cout << "3 Substraction\n";
		cout << "4 Multip\n";
		cout << "5 Division\n";
		cin >> mode;
		switch (mode) {
		case 1:
			cout << "n1: ";
			n1.set();
			n1 = n1.inv();
			n1.show();
			break;
		case 2:
			cout << "n1: ";
			n1.set();
			cout << "n2: ";
			n2.set();
			n3 = n1.add(n2);
			n3.show();
			break;
		case 3:
			cout << "n1: ";
			n1.set();
			cout << "n2: ";
			n2.set();
			n3 = n1.sub(n2);
			n3.show();
			break;
		case 4:
			cout << "n1: ";
			n1.set();
			cout << "n2: ";
			n2.set();
			n3 = n1.mult(n2);
			n3.show();
			break;
		case 5:
			cout << "n1: ";
			n1.set();
			cout << "n2: ";
			n2.set();
			n3 = n1.div(n2);
			n3.show();
			break;
			break;
		default:
			cout << "Don't understand\n";
		}
		cout << "\nAgain?";
		cin >> again;
	}
}