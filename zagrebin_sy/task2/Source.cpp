#include <iostream>
using namespace std;

class Vector {
private:
	int size = 0;
	int *arr = nullptr;
public:
	Vector() {		// Constructors
		size = 0;
		arr = nullptr;
	}
	Vector(int n) {
		if (n < 1 || n > 20)
			cout << "*Init Error* Out of range [1;20]\n";
		else {
			size = n;
			arr = new int[n];
			for (int i = 0; i < n; i++)
				arr[i] = 0;
		}
	}
	Vector(const Vector& v) {
		size = v.size;
		arr = new int[size];
		for (int i = 0; i < size; i++)
			arr[i] = v.arr[i];
	}
	Vector(int n, int ...) {
		if (n < 1 || n > 20)
			cout << "*Init Error* Out of range [1;20]\n";
		else {
			size = n;
			int *arr = &n;
			arr = new int[n];
			if (sizeof(int*) == 4)	// x86
				for (int i = 0; i < n; i++)
					arr[i] = arr[i+1];	
			else
				for (int i = 0; i < n; i++)	// x64
					arr[i] = arr[2 * (i + 1)];
		}
	}
	~Vector() {		// destructor
		delete []arr;
	}
	void operator=(const Vector &v) {	//	=
		if (size == v.size) {
			size = v.size;
			for (int i = 0; i < size; i++)
				arr[i] = v.arr[i];
		}else {
			size = v.size;
			delete []arr;
			arr = new int[size];
			for (int i = 0; i < size; i++)
				arr[i] = v.arr[i];
		}

	}
	void show() {	// for tester
		cout << '[';
		for (int i = 0; i < size; i++)
			cout << arr[i] << ", ";
		cout << "]\n";
	}
	void set_size(int n) {	// set size
		if (n < 1 || n > 20)
			cout << "*Error* Size out of range [1;20]\n";
		else {
			size = n;
			delete []arr;
			arr = new int[n];
			for (int i = 0; i < n; i++)
				arr[i] = 0;
		}
	}
	int get_size() {	// get size
		return size;
	}
	void set(int i, int x) {	// set component
		if (size < i || i < 1)	// index from 1!
			cout << "*Error* Index out of range\n";
		else
			arr[i-1] = x;
	}
	int get(int i) {	// get component
		if (size < i || i < 1) {
			cout << "*Error* Index out of range\n";
			return 0;
		}else
			return arr[i-1];
	}
	double length() {	// get length
		if (size < 1) {
			cout << "*Error* Vector wasn't initialized\n";
			return 0;
		}else {
			double len = 0;
			for (int i = 0; i < size; i++) {
				len += arr[i] * arr[i];
			}
			return sqrt(len);
		}
	}
	long scalar(const Vector &v) {	// scalar
		if (size < 1 || v.size != size) {
			cout << "*Error* Wrong sizes\n";
			return 0;
		}else {
			long res = 0;
			for (int i = 0; i < size; i++)
				res += arr[i] * v.arr[i];
			return res;
		}
	}
	Vector add(const Vector &v) {		// +
		Vector res;
		if (size != v.size) {
			cout << "*Error* Different sizes\n";
			return res;
		}else{
			res.set_size(size);
			for (int i = 0; i < size; i++)
				res.set(i + 1, arr[i] + v.arr[i]);
			return res;
		}
	}
};

void main() {
	Vector v[3];
	Vector v1, v2(3), v3(3, -1, 0, 1);
	v[0] = v1; v[1] = v2; v[2] = v3;
	int choice = 0, again = 0, i, j, k;

	cout << "Without initializaton: v1 = ";
	v1.show();
	cout << "size = 3, without coordinates: v2 = ";
	v2.show();
	cout << "size = 3, (-1, 0, 1): v3 = ";
	v3.show();
	
	cout << "\nWant to test operations? (0 - NO)";
	cin >> again;
	while (again) {
		system("cls");
		for (int i = 0; i < 3; i++) {
			cout << 'v' << i + 1 << ' ';
			v[i].show();
		}

		cout << "\nOperations:\n";
		cout << "1) show v_i \n";
		cout << "2) Set size for v_i: \n";
		cout << "3) Get size for v_i: \n";
		cout << "4) Set i component in v_j \n";
		cout << "5) Get i component in v_j \n";
		cout << "6) Get length for v_i: \n";
		cout << "7) Scalar for v_i, v_j: \n";
		cout << "8) Sum for v_i, v_j: \n";
		cout << "9) Set v_i = v_j: \n";
		cout << "\n$Choose:  ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Show v_i: ";
			cin >> i;
			v[(i - 1) % 3].show();
			break;
		case 2:
			cout << "Set size in v_i: ";
			cin >> i;
			cout << "Size: ";
			cin >> j;
			v[(i - 1) % 3].set_size(j);
			break;
		case 3:
			cout << "Get size from v_i: ";
			cin >> i;
			cout << v[(i - 1) % 3].get_size();
			break;
		case 4:
			cout << "Set i component: ";
			cin >> i;
			cout << "In v_j: ";
			cin >> j;
			cout << "Enter number: ";
			cin >> k;
			v[(j - 1) % 3].set(i, k);
			break;
		case 5:
			cout << "Get i component: ";
			cin >> i;
			cout << "From v_j: ";
			cin >> j;
			cout << v[(j - 1) % 3].get(i);
			break;
		case 6:
			cout << "Length of v_i: ";
			cin >> i;
			cout << v[(i - 1) % 3].length();
			break;
		case 7:
			cout << "Enter i: ";
			cin >> i;
			cout << "Enter j: ";
			cin >> j;
			cout << v[(i - 1) % 3].scalar(v[(j - 1) % 3]) << '\n';
			break;
		case 8:
			cout << "Enter i: ";
			cin >> i;
			cout << "Enter j: ";
			cin >> j;
			v[(i - 1) % 3].add(v[(j - 1) % 3]).show();
			break;
		case 9:
			cout << "Enter i: ";
			cin >> i;
			cout << "Enter j: ";
			cin >> j;
			v[(i - 1) % 3] = v[(j - 1) % 3];
			break;
		default:
			cout << "No such option\n";
		}
		cout << "\nContinue? (0 - NO):";
		cin >> again;
	}
	
	system("pause");
}