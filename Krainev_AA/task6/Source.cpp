#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <limits>
#include <string>
using namespace std;

const int LEFT_BOUND = 0;
const int RIGHT_BOUND = 10;

class RandomGenerator {
private:
	unsigned int leftBound = LEFT_BOUND;
	unsigned int rightBound = RIGHT_BOUND;
	bool initialized = false;
	vector <int> computerValue;
	unsigned int length;
public:
	unsigned int getLength();
	vector <int> getRandomValue();
	RandomGenerator(int _length) :length(_length) { randomSequence(); }
	void setLenght(int _length) { length = _length; }
	void init();
	int getRandom();
	void randomSequence();
	~RandomGenerator() {}
};

class Game {
private:
	RandomGenerator* RaGn;
	vector <int> playerValue;
	unsigned int cows = 0; //для подсчета коров
	unsigned int bulls = 0; //для подсчета быков
public:
	Game(RandomGenerator* _RaGn) :cows(0), bulls(0) {
		RaGn = _RaGn;
	}
	bool gameProcess();
	int j = 0;
	int countCows();
	int countBulls();
	void setPlayerValue(vector <int> _playerValue);
	void printCountCowsAndBulls();
};

int main() {
	setlocale(0, "");
	unsigned int len;
	cout << "+---------------------+-------------+-------+ " << endl;
	cout << "|         Игра  быки    и коровы            | " << endl;
	cout << "+---------------------+-------------+-------+ " << endl;
	cout << "->Правила: " << endl;
	cout << "Компьютер загадает число с выбранной вами длиной с неповторяющимися цифрами." << endl;
	cout << "Вы введете предполагаемое число с точностью до числа цифр." << endl;
	cout << "Компьютер сообщает, сколько цифр угадано без совпадения с их позициями в загаданном числе - число <коров>" << endl;
	cout << "и сколько угадано вплоть до позиции в загаданном числе - число <быков> ." << endl;
	cout << " " << endl;
	cout << "->Введите длину числа, которое хотите угадать:" << endl;
	cin >> len;
	while ((len < 2) || (len > 10)) {
		cout << "-> Введите число в диапазоне от 2 до 10:" << endl;
		cin >> len;
	}
	RandomGenerator ranGen(len);
	Game gameMain(&ranGen);
	bool gameCheck = true;
	vector <int> playerValue;
	do {
		do {
			int num;
			cout << "->Введите ваше предположение: " << endl;
			cin >> num;
			playerValue.clear();
			while (num) {
				playerValue.push_back(num % 10);
				num = num / 10;
			}
			reverse(playerValue.begin(), playerValue.end());
			if (playerValue.size() != ranGen.getLength()) { cout << "Повторите ввод заново" << endl; }
		} while (playerValue.size() != ranGen.getLength());
		gameMain.setPlayerValue(playerValue);
		gameCheck = gameMain.gameProcess();
	} while (gameCheck == true);

	cout << "+---------------------+-------------+-------+ " << endl;
	cout << "|              Вы выиграли!                 | " << endl;
	cout << "+---------------------+-------------+-------+ " << endl;
}

bool Game::gameProcess() {
	countCows();
	countBulls();
	printCountCowsAndBulls();
	if (playerValue.size() == bulls) {
		return false;
	}
	return true;
}

int Game::countCows() {
	cows = 0;
	for (int i = 0; i < playerValue.size(); i++) {
		for (j = 0; j < playerValue.size(); j++) {
			if (RaGn->getRandomValue()[i] == playerValue[j]) {
				cows++;
			}
		}
		j++;
	}
	return cows;
}

int Game::countBulls() {
	bulls = 0;
	for (int i = 0; i < playerValue.size(); i++) {
		if ((RaGn->getRandomValue()[i] == playerValue[i])) {
			bulls++;
		}
	}
	return bulls;
}

void Game::setPlayerValue(vector<int> _playerValue) {
	playerValue = _playerValue;
}

void Game::printCountCowsAndBulls() {
	cout << "Коров " << cows - bulls << endl;
	cout << "Быков " << bulls << endl;
}

unsigned int RandomGenerator::getLength() {
	return length;
}

vector<int> RandomGenerator::getRandomValue() {
	return computerValue;
}

void RandomGenerator::init() {
	srand(time(NULL));
	initialized = true;
}

int RandomGenerator::getRandom() {
	if (!initialized) {
		init();
	}
	return rand() % (rightBound - leftBound) + leftBound;
}

void RandomGenerator::randomSequence() {
	do {
		computerValue.clear();
		int numeral;
		bool count = false;
		while (computerValue.size() != length) {
			numeral = getRandom();
			for (size_t i = 0; i < computerValue.size(); i++) {
				if (numeral == computerValue[i]) {
					count = true;
					break;
				}
			}
			if (count == false) {
				computerValue.push_back(numeral);
			}
			count = false;
		}
	} while (computerValue[0] == 0);
	cout << "Рандомное число в генераторе: ";
	for (size_t i = 0; i < computerValue.size(); i++) { cout << computerValue[i]; } //печать рандомного числа
	cout << endl;
}