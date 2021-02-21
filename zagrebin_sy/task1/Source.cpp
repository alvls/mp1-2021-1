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
	void set(long long x) {	//SET long long
		p1 = x >> 32;
		p2 = x;
	}
	void set(long_number x) {	//SET long_number
		p1 = x.get1();
		p2 = x.get2();
	}
	long long show() {	// RETURN AS long long
		return long long(p1) << (sizeof(long long) * 4) | p2;
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
		r.set2(~p2);
		r.set1(~p1);
		r = r.add(1);
		return r;
	}
	long_number add(long_number x) {	// + long_number
		long_number r;
		r.set2(p2 + x.get2());
		r.set1(p1+ x.get1() + int((long long(p2) + x.get2()) >> 32));
		return r;
	}
	long_number add(int x) {	// + int
		long_number r;
		r.set2(p2 + x);
		r.set1(p1 + int((long long(p2) + x) >> 32));
		return r;
	}
	long_number sub(long_number x) {	// -
		long_number r;
		x = x.inv();
		r.set2(p2 + x.get2());
		r.set1(p1 + x.get1() + int((long long(p2) + x.get2()) >> 32));
		return r;
	}
	long_number mult(long_number x) {	// *
		long_number r;
		r.set2(p2 * x.get2());
		r.set1(p1 * x.get2() + p2 * x.get1() + int((long long(p2) * x.get2()) >> 32));

		return r;
	}
	long_number div(long_number x) {	// /
		long_number r, y; y.set(show()); // y / x
		int sign;
		if ((x.get1() | x.get2()) != 0)
			if ((y.get1() >= 0) ^ (x.get1() >= 0))
				while (abs(y.show()) >= abs(x.show())) {// +-
					r = r.add(-1);
					y = y.add(x);
				}
			else
				while (abs(y.show()) >= abs(x.show())) {// ++ --
					r = r.add(1);
					y = y.sub(x);
				}
		else
			cout << "Division by Zero\n";
		
		return r;
	}
};

void main() {
	long_number n1, n2, n3;
	int mode, again = 1; long long x;
	while (again) {
		system("cls");
		cout << "Long long range (8 BYTE!!!): " << (long long(1) << (sizeof(long long) * 8 - 1)) << " to " << ~(long long(1) << (sizeof(long long) * 8 - 1)) << '\n';
		
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
			cin >> x;
			n1.set(x);
			n1 = n1.inv();
			cout << n1.show();
			break;
		case 2:
			cout << "n1: ";
			cin >> x;
			n1.set(x);
			cout << "n2: ";
			cin >> x;
			n2.set(x);
			n3 = n1.add(n2);
			cout << n3.show();
			break;
		case 3:
			cout << "n1: ";
			cin >> x;
			n1.set(x);
			cout << "n2: ";
			cin >> x;
			n2.set(x);
			n3 = n1.sub(n2);
			 cout << n3.show();
			break;
		case 4:
			cout << "n1: ";
			cin >> x;
			n1.set(x);
			cout << "n2: ";
			cin >> x;
			n2.set(x);
			n3 = n1.mult(n2);
			cout << n3.show();
			break;
		case 5:
			cout << "n1: ";
			cin >> x;
			n1.set(x);
			cout << "n2: "; 
			cin >> x;
			n2.set(x);
			n3 = n1.div(n2);
			cout << n3.show();
			break;
		default:
			cout << "Don't understand\n";
		}
		cout << "\nAgain?";
		cin >> again;
	}
	system("pause");
}