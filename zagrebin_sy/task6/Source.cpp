#include <iostream>
#include <windows.h>
#include <conio.h>
#include <queue>
#include <ctime> 
using namespace std;

enum class Color {
	Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray,
	DarkGray, LightBlue, LightGreen, LightCyan, LightRed,
	LightMagenta, Yellow, White
};
void paint(char c, Color col) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)(col));
	cout << c;
}
enum class err { wrong_parameter };
enum direction { up = 1, right = 2, down = -1, left = -2 };
			//	72			77			80		75
struct Cell {
	char sign;
	Color color;
};
struct Body {
	Cell* cell; bool fake;
	Body(Cell* c) {
		fake = true;
		cell = c;
		c->sign = 'o';
		c->color = Color::Green;
	}
	Body(const Body& b) {
		cell = b.cell; fake = false;
	}
	~Body() {
		if (!fake) {
			cell->sign = ' ';
			cell->color = Color::White;
		}
	}
};
class Field {		// Field
	unsigned height, width;
	Cell **field;
public: 
	Field(unsigned h, unsigned w) {
		if (w < 7 || h < 3)
			throw err::wrong_parameter;
		unsigned i, j;
		height = h + 2; width = w + 2;	// Real sizes with borders
		field = new Cell*[height];	// Create
		for ( i = 0; i < height; i++)
			field[i] = new Cell[width];
	}
	void show() {
		unsigned i, j;
		system("cls");
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++)
				paint(field[i][j].sign, field[i][j].color);
			cout << endl;
		}
	}
	void food() {
		unsigned y, x;
		do {
			y = rand() % (height - 2) + 1;
			x = rand() % (width - 2) + 1;
		}
		while (field[y][x].sign != ' ');
		field[y][x].color = Color::Yellow;
		field[y][x].sign = '*';
	}
	void start(unsigned l) {
		unsigned i, j; bool f = true; int c;
		queue<Body> snake;
		unsigned y, x;	// head coordinates
		direction dir;
		// Build map
		for (j = 0; j < width; j++)	// First row		
			field[0][j] = Cell{ '#', Color::LightGray };
		for (i = 1; i < height - 1; i++) {	// Inner
			field[i][0] = Cell{ '#', Color::LightGray };
			for (j = 1; j < width - 1; j++)
				field[i][j] = Cell{ ' ', Color::White };
			field[i][width - 1] = Cell{ '#', Color::LightGray };
		}
		for (j = 0; j < width; j++)	// Last row
			field[height - 1][j] = Cell{ '#', Color::LightGray };

		for (int i = 0; i < 5; i++) // Snake start
			snake.push(Body(field[2] + 2 + i));
		field[2][6].sign = '@'; field[2][6].color = Color::Red;
		dir = direction::right;
		y = 2; x = 6;	// head coordinates
		food();						// Create food
		show();		// Start ready
		cout << "\nReady to start\n";
		_getch();

		while (true) {
			if (_kbhit()) {
				c = _getch();	// Check new direction
				if (c == 224) {
					c = _getch();
				}
				switch (c) {
				case 80:
					if (dir != direction::down)
						dir = direction::up;
					break;
				case 77:
					if (dir != direction::left)
						dir = direction::right;
					break;
				case 72:
					if (dir != direction::up)
						dir = direction::down;
					break;
				case 75:
					if (dir != direction::right)
						dir = direction::left;
					break;
				}
			}
			field[y][x].sign = 'o';	// Change head to body
			field[y][x].color = Color::Green;
			y += dir % 2;  x += (dir + 1) % 2;

			switch (field[y][x].sign) {	// What is next?
			case ' ':
				snake.push(field[y] + x);
				field[y][x].sign = '@';
				field[y][x].color = Color::Red;
				snake.pop();
				break;
			case '*':
				snake.push(field[y] + x);
				field[y][x].sign = '@';
				field[y][x].color = Color::Red;
				if (snake.size() == l)
					goto end;
				food();
				break;
			default:
				f = false;
				goto end;
			}
			show();
			Sleep(250);
		}
		end:
			if (f)
				cout << "\nYou win!\n";
			else
				cout << "\nYou lose\n";
	}
	~Field(){
		for (unsigned i = 0; i < height; i++)
			delete field[i];
		delete[] field;
	}
};

void main() {
	unsigned h = 16, w = 16; bool again = true;
	srand(time(NULL));

	//cout << "Enter heigth and width of the field: ";
	//cin >> h; cin >> w;
	Field field(h, w);

	while (again) {
		field.start(10);
		cout << "Try again? (Yes - 1, No - 0): ";
		cin >> again;
	}
	
	system("pause");
}