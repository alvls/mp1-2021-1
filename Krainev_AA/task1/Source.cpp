/*Разработать класс Конвертер весов.
Класс должен хранить вес в килограммах и предоставлять методы по его преобразованию в другие единицы измерения(например, аптечный фунт, тройская унция, пуд, …).
Класс должен предоставлять операции : 1) установить текущий вес в килограммах, 2) узнать текущий вес в килограммах, 3) узнать текущий вес в выбранной единице измерения(из списка поддерживаемых).
Класс должен содержать все необходимые конструкторы, оператор присваивания, а также «уметь» выводить себя на консоль.
*/
#include <iostream>
using namespace std;

int getNumberOfWeidth();
void printMainMenu();
void printMenuWithNamesOfWeights();
void infornationAbConverted(int varianOfMenu, class ScaleConverter measuring);
void welcomeMessage();


class ScaleConverter {
private:
    double enteredWeight; //введенная масса(вес)
    double convertedWeight; //конвертированная масса(вес)
public:
    ScaleConverter(double i); // construct для задания значения веса
    //методы для конвертации в другие меры веса
    void setTheValue(double i);


    double kgToTroyOunce();
    double  kgToPharmacyPound();
    double kgToOunce();//унция обыкновенная
    double kgToStones();//стоны 
    double kgToAmericanTones();//американская тонна

    //вывод enteredWeight значения
    void printOfEnteredWeight();
    //вывод convertedWeight значения
    void printOfConvertedWeight();
};
int main() {
    setlocale(LC_ALL, "Rus");
    welcomeMessage();
    double kg = -1;
    while (kg < 0) {
        cout << "Введите массу в кг. и нажмите ENTER\n" << endl;
        cin >> kg;
        if (kg < 0) {
            cout << "Некорректная величина для конвертации" << endl;
        }
    }
    ScaleConverter measuring(kg);
    while (1) {
        int variantOfMenu = -1;

        printMainMenu();
        while (variantOfMenu <= 0 || variantOfMenu > 4) {
            cin >> variantOfMenu;
            if (variantOfMenu <= 0 || variantOfMenu > 4) {
                cout << "Неверный выбор меню, попробуйте снова!" << endl;
            }
        }

        switch (variantOfMenu) {
        case 1: //конвертировать
            printMenuWithNamesOfWeights();
            variantOfMenu = getNumberOfWeidth();
            infornationAbConverted(variantOfMenu, measuring);
            break;
        case 2://изменить конвертируемую величину
            cout << "Введите новую конвертируемую величину (в кг.): " << endl;
            cin >> kg;
            measuring.setTheValue(kg);
            break;
        case 3: //просмотр текущего значения (в кг.)
            measuring.printOfEnteredWeight();
            break;
        case 4: //выход из программы
            //measuring.printOfEnteredWeight();
            return 0;
            break;
        }
    }
    return 0;
}

void welcomeMessage() {
    cout << "Добро пожаловать в приложение конвертер весов!\n" << endl;
    cout << "Сначала Вам будет предложено ввести значение для конвертации (в кг.)\n"
        << "Затем вы сможете выбрать единицу меры веса, в которую хотите провести конвертацию \n"
        << "Или изменить введенную величину в метрах\n"
        << "Перевод может выведен с некоторой погрешностью, из-за разных значений мер в справочниках\n"
        << "Значения для перевода взяты с сайта конвертер единиц измерения google.com\n" << endl;
}
void printMainMenu() {
    cout << "Выберите вариант меню:\n" << endl;
    cout << "1. Конвертировать в другую единицу измерения\n"
        << "2. Изменить конвертируемую величину\n"
        << "3. Просмотр текущего выбранного значения (в кг.) \n"
        << "4. Выйти\n" << endl;
}
void printMenuWithNamesOfWeights() {
    cout << "Выберите вариант\n" << endl;
    cout << "1. Конвертация в тройскую унцию \n"
        << "2. Конвертация в аптечный фунт\n"
        << "3. Конвертация унцию (обыкновенная) \n"
        << "4. Конвертация в стоны \n"
        << "5. Конвертация в американскую тонну\n"
        << "6. Выйти из программы\n" << endl;
}

ScaleConverter::ScaleConverter(double i) {
    setTheValue(i);
    convertedWeight = -1;
}

void ScaleConverter::setTheValue(double i)
{
    enteredWeight = i;
}

double ScaleConverter::kgToTroyOunce() {
    convertedWeight = 32.150743 * enteredWeight;
    return convertedWeight;
    //cout << enteredWeight;
}

double ScaleConverter::kgToPharmacyPound() {
    convertedWeight = 2.679229 * enteredWeight;
    return convertedWeight;
}

double ScaleConverter::kgToOunce() {
    convertedWeight = 35.274 * enteredWeight;
    return convertedWeight;
}

double ScaleConverter::kgToStones() {
    convertedWeight = 0.157473 * enteredWeight;
    return convertedWeight;
}

double ScaleConverter::kgToAmericanTones() {
    convertedWeight = 0.00110231 * enteredWeight;
    return convertedWeight;
}

void ScaleConverter::printOfEnteredWeight() {
    cout << enteredWeight << endl;
}

void ScaleConverter::printOfConvertedWeight() {
    cout << convertedWeight << endl;
}

int getNumberOfWeidth() {
    int variant = -1;
    while (variant <= 0 || variant >= 7) {
        cin >> variant;
        if (variant <= 0 || variant >= 7) {
            cout << "Неверный выбор меню, попробуйте снова!" << endl;
        }
    }
    return variant;
}

void infornationAbConverted(int variantOfMenu, class ScaleConverter measuring) {
    switch (variantOfMenu) {
    case 1: //тройская унция
        cout << " В тройских унциях: " << endl;
        measuring.kgToTroyOunce();
        measuring.printOfConvertedWeight();
        break;
    case 2: //аптечная унция
        cout << " В аптечных фунтах: " << endl;
        measuring.kgToPharmacyPound();
        measuring.printOfConvertedWeight();
        break;
    case 3: //унция обыкновенная
        cout << " В унциях: " << endl;
        measuring.kgToOunce();
        measuring.printOfConvertedWeight();
        break;
    case 4: //стоны
        cout << " В стонах: " << endl;
        measuring.kgToStones();
        measuring.printOfConvertedWeight();
        break;
    case 5: //американская тонна
        cout << " В американских тоннах: " << endl;
        measuring.kgToAmericanTones();
        measuring.printOfConvertedWeight();
        break;
    case 6:
        exit(1);
    }
}