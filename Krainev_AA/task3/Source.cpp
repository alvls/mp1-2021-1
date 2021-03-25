#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;
void printWelcomeMessege();
void printMenyWithTeylorsFunction();
void printMainMenu();
void printMessegeForMenu();
int getMenuItem(int sizeMenu);
double getDataFromUser();
const int SIZE_MAIN_MENU = 9;
const int SIZE_MENU_WITH_TEYLORS_FUNCTION = 3;
class TaylorSeries {
private:
    double realVariable;
    int numberOfMembers;
    int selectedFunctionNumber;
public:
    void setSelectedFunctiomNumber(int choiceFunction);
    int getAndPrintSelectedFunctionNumber();
    void setNumberOfMembers(int otherNumberOfMembers);
    int setAndPrintNumberOfMembers();
    TaylorSeries();// конструктор по умолчанию
    void printSelectedTaylorFormula();
    void setRealVariable(double otherRealVariable);
    double getTheValueOfTheSelectedMember(int selectedMember);
    double calculateTheValueOfSeriesAtThePoint();
    double deviationFromTheEtalon();
};

int main()
{
    setlocale(LC_ALL, "rus");
    printWelcomeMessege();
    int choiceMenu = -1;
    double getX;
    int getNumber, choiceFunction;
    TaylorSeries Tey;
    while (choiceMenu != 9) { //пока пользователь не нажмет на пункт выхода из программы
        printMainMenu(); //печатаем главное меню (с функционалом)
        printMessegeForMenu();
        choiceMenu = getMenuItem(SIZE_MAIN_MENU);
        cout << "Выбран " << choiceMenu << " пункт главного меню " << endl;
        switch (choiceMenu) {
        case 1: { // 1. Задать текущую функцию и получаем значение икс 
            printMenyWithTeylorsFunction();
            int choiceFunction = getMenuItem(SIZE_MENU_WITH_TEYLORS_FUNCTION);
            Tey.setSelectedFunctiomNumber(choiceFunction);
            double realVariable;
            cout << "Введите значение х: " << endl;
            realVariable = getDataFromUser();
            Tey.setRealVariable(realVariable);
            break;
        }
        case 2: { //2. Узнать текующую функцию
            Tey.getAndPrintSelectedFunctionNumber();
            break;
        }
        case 3: { //3. Задать текущее значение членов ряда
            int numberOfMembers;
            cout << "Задайте число членов (целое число!)" << endl;
            numberOfMembers = getDataFromUser();
            Tey.setNumberOfMembers(numberOfMembers);
            break;
        }
        case 4: { //4. Узнать текущее число членов ряда
            Tey.setAndPrintNumberOfMembers();
            break;
        }
        case 5: { //5. Выдать формулу ряда выбранной функции
            Tey.printSelectedTaylorFormula();
            break;
        }
        case 6: { //6. Выдать значение заданного члена ряда
            cout << "Значение какого члена хотите узнать (целое число!)" << endl;
            int selectedMember;
            selectedMember = getDataFromUser();
            cout << "Значение " << selectedMember <<"-го члена равняется: " << Tey.getTheValueOfTheSelectedMember(selectedMember) << endl;
            break;
        }
        case 7: { //Рассчитать значение ряда в выбранной точке
            cout << "Вычисленное значение: " << Tey.calculateTheValueOfSeriesAtThePoint() << endl;
            break;
        }
        case 8: { //Вывести отклонение значения ряда
            cout  << "Отклонение от эталонного значения: " << Tey.deviationFromTheEtalon() << endl;
            break;
        }
        }
    }

}

void printMenyWithTeylorsFunction() {
    cout << "Список доступных функций:" << endl;
    cout << "1. cos(x)" << endl;
    cout << "2. sin(x)" << endl;
    cout << "3. exp(x)" << endl;
}
void printMainMenu() {
    cout << "МЕНЮ: " << endl;
    cout << "1. Задать текущую функцию" << endl;
    cout << "2. Узнать текующую функцию" << endl;
    cout << "3. Задать текущее значение членов ряда" << endl;
    cout << "4. Узнать текущее число членов ряда" << endl;
    cout << "5. Выдать формулу ряда выбранной функции" << endl;
    cout << "6. Выдать значение заданного члена ряда" << endl;
    cout << "7. Рассчитать значение ряда в выбранной точке" << endl;
    cout << "8. Вывести отклонение значения ряда " << endl;
    cout << "9. Завершить работу с программой " << endl;
}
void printMessegeForMenu() {
    cout << "Введите нужный пункт меню " << endl;
}
int getMenuItem(int sizeMenu) //получение выбранного пункта и меню (передаем ему размерность меню)
{
    int menuItem = -1;;
    while (menuItem < 1 || menuItem > sizeMenu) {
        cin >> menuItem;
        if (menuItem < 1 || menuItem > sizeMenu) { cout << "Несуществующий пункт меню. Введите нужный номер ещё раз." << endl; }
    }
    return menuItem;
}
double getDataFromUser()
{
    double information;
    cin >> information;
    return information;
}
void TaylorSeries::setSelectedFunctiomNumber(int choiceFunction) {
    selectedFunctionNumber = choiceFunction;
}
int TaylorSeries::getAndPrintSelectedFunctionNumber() {
    switch (selectedFunctionNumber) {
    case 1: {  cout << " cos(x) " << endl; break; }
    case 2: {  cout << " sin(x) " << endl; break; }
    case 3: {  cout << " exp(x) " << endl; break; }
    case 0: {  cout << " Функция еще не выбрана: вернитесь в пункт меню 1. " << endl; break; }
    }
    return selectedFunctionNumber;
}
void TaylorSeries::setNumberOfMembers(int otherNumberOfMembers) {
    numberOfMembers = otherNumberOfMembers;
}
int TaylorSeries::setAndPrintNumberOfMembers() {
    cout << "Заданное число членов ряда Тейлора: " << numberOfMembers << endl;
    return numberOfMembers;
}
TaylorSeries::TaylorSeries() {
    realVariable = 0;
    numberOfMembers = 0;
    selectedFunctionNumber = 0;
}
void TaylorSeries::printSelectedTaylorFormula() {
    switch (selectedFunctionNumber) {
    case 1: { //косинусик
        cout << " cos(x) = ";
        cout << "1";
        for (int i = 2; i <= numberOfMembers; i++) {
            if (i % 2 == 1) { cout << "+"; }
            else { cout << "-"; }
            cout << "x^(" << (2 * i - 2) << ")/" << (2 * i - 2) << "!";
            if (i % 7 == 1) { //чтобы для большого числа членов не было все в строчку
                cout << "+" << endl;
            }
        }
        cout << endl;
        break;
    }
    case 2: {//синусик
        cout << " sin(x) = ";
        cout << "1";
        for (int i = 2; i <= numberOfMembers; i++) {
            if (i % 2 == 1) { cout << "+"; }
            else { cout << "-"; }
            cout << "x^(" << (2 * i - 1) << ")/" << (2 * i - 1) << "!";
            if (i % 7 == 1) { //чтобы для большого числа членов не было все в строчку
                cout << "+" << endl;
            }
        }
        cout << endl;
        break;

    }
    case 3: {//экспонента
        cout << " exp(x) = ";
        cout << "1";
        for (int i = 1; i <= numberOfMembers - 1; i++) {
            cout << "+x^(" << i << ")/" << i << "!";
            if (i % 7 == 1) { //чтобы для большого числа членов не было все в строчку
                cout << "+" << endl;
            }
        }
        cout << endl;
        break;
    }
    }
}
void TaylorSeries::setRealVariable(double otherRealVariable) {
    realVariable = otherRealVariable;
}
double TaylorSeries::getTheValueOfTheSelectedMember(int selectedMember)
{
    switch (selectedFunctionNumber) {
    case 1: { //если был выбран косинус
        double numerator, denominator;
        if (selectedMember == 1) { return 1; }
        else {
            numerator = pow(-1, selectedMember + 1) * pow(realVariable, (2 * selectedMember));
            denominator = 1;
            for (int j = 1; j <= (2 * selectedMember); j++) {
                denominator = denominator * j;
            }
        }
        return numerator / denominator;
    }
    case 2: {//если был выбран синус
        double numerator, denominator;
        if (selectedMember == 1) { return realVariable; }
        else {
            numerator = pow(-1, selectedMember + 1) * pow(realVariable, 2 * selectedMember - 1);
            denominator = 1;
            for (int j = 1; j <= (2 * selectedMember - 1); j++) {
                denominator = denominator * j;
            }

        }
        return numerator / denominator;
    }
    case 3: {//если был выбран экспонента
        double numerator, denominator;
        if (selectedMember == 1) { return 1; }
        else {
            numerator = pow(realVariable, selectedMember);
            denominator = 1;
            for (int j = 1; j <= selectedMember; j++) {
                denominator = denominator * j;
            }
        }
        return numerator / denominator;
    }
    }
}
double TaylorSeries::calculateTheValueOfSeriesAtThePoint() {
    double res = 0;
    if (numberOfMembers == 0) { cout << "Выбранное число слагаемых 0, укажите больше в пункте 3 меню! Будет возвращено значение -1 " << endl; return -1; }
    switch (selectedFunctionNumber) {
    case 1: { //если был выбран косинус
        double _realVariable = ((realVariable * M_PI) / 180);
        res = 1;
        double term = 1;
        for (int i = 2; i <= numberOfMembers; i++)
        {
            term = (-1) * term * _realVariable * _realVariable / ((2 * i - 2) * (2 * i - 3));
            res = res + term;
        }
        return res;
        break;
    }
    case 2: {//если был выбран синус
        double _realVariable = ((realVariable * M_PI) / 180);
        res = _realVariable;
        double term = _realVariable;
        for (int i = 2; i <= numberOfMembers; i++) {
            term = (-1) * term * _realVariable * _realVariable / ((2 * i - 1) * (2 * i - 2));
            res = res + term;
        }
        return res;
        break;
    }

    case 3: {//если был выбран экспонента
        res = 1;
        double term = 1;
        for (int i = 2; i <= numberOfMembers; i++) {
            term = term * realVariable / (i - 1);
            res = res + term;
        }
        return res;
        break;
    }
    }

}
double TaylorSeries::deviationFromTheEtalon() {
    double etalon;
    double delta;

    switch (selectedFunctionNumber) {
    case 1: { //если был выбран косинус
        double _realVariable = ((realVariable * M_PI) / 180);
        etalon = cos(_realVariable);
        cout << "Эталонное значение " << etalon << endl;
        delta = abs(etalon - calculateTheValueOfSeriesAtThePoint());
        return delta;
        break;
    }
    case 2: {//если был выбран синус
        double _realVariable = ((realVariable * M_PI) / 180);
        etalon = sin(_realVariable);
        cout << "Эталонное значение " << etalon << endl;
        delta = abs(etalon - calculateTheValueOfSeriesAtThePoint());
        return delta;
        break;
    }

    case 3: {//если был выбран экспонента
        etalon = exp(realVariable);
        cout << "Эталонное значение " << etalon << endl;
        delta = abs(etalon - calculateTheValueOfSeriesAtThePoint());
        return delta;
        break;
    }
    }

}
void printWelcomeMessege() {
    cout << "Добро пожаловать в программу Ряд Тейлора!" << endl;
    cout << "Вам будет предложено выбрать функцию и значение точки, в которой будет вычисляться значение." << endl;
    cout << "Значение точки нужно вводить в градусах (для тригонометрических функций)!" << endl;;
    cout << "Смена точки вычисления происходит только при выборе функции (пункт 1 меню)." << endl;
    cout << "Расчет функции (пункт 7 меню) происходит до количества слагаемых, выбранных вами в пункте 3." << endl;
    cout << "Пункт 5 меню выдаст Вам формулу для самостоятельного расчета функции (для количества слагаемых, выбранных в пункте 3)" << endl;
    cout << "Сейчас будет выведено главное меню, где Вам стоит начать с пункта 1." << endl << endl;
}