#include <iostream>
using namespace std;

class ScaleConverter
{
private:
    bool check = true;
    double weight, originalWeight;
public:
    void scanWeight()
    {
        while (check)
        {
            cout << "Введите вес в килограммах (Если число не целое, вводите так: 3.5): ";
            cin >> originalWeight;
            if (originalWeight < 0)
            {
                cout << "Введенно отрицательное значение, программа работает только с положительными числами. Пожалуйста, попробуйте еще раз. \n" << endl;
            }
            else
            {
                check = false;
            }
        }
    }
    void printOriginalWeight()
    {
        cout << "Исходный вес = " << originalWeight << "кг" << "\n" << endl;
    }
    void printConvertWeight(char* str)
    {
        cout << "Перевод " << originalWeight << "кг = " << weight << str << "\n" << endl;
    }
    void convertGrams()
    {
        weight = originalWeight * 1000;
    }
    void convertPharmacyPound()
    {
        weight = originalWeight * 2.679;
    }
    void convertTroyOunce()
    {
        weight = originalWeight * 32.151;
    }
    void convertPood()
    {
        weight = originalWeight / 16.381;
    }
};

int main()
{
    setlocale(LC_ALL, "rus");
    int indexMenu = 0;
    bool end = true;
    char* str;
    ScaleConverter convert;
    convert.scanWeight();
    cout << "\nПрограмма умеет: \n" << "1. Перевести килограммы в граммы;\n" << "2. Перевести килограммы в аптечный фунт;\n"
        << "3. Перевести килограммы в тройскую унцию;\n" << "4. Перевести килограммы в пуды;\n" << "5. Вывести изначально веденные килограммы;\n"
        << "6. Выйти из программы. \n" << endl;
    while (end)
    {
        cout << "Выберите пункт меню: ";
        cin >> indexMenu;
        cout << endl;
        switch (indexMenu)
        {
            case 1:
            {
                convert.convertGrams();
                str = " грамм";
                convert.printConvertWeight(str);
                break;
            }
            case 2:
            {
                convert.convertPharmacyPound();
                str = " аптечных фунтов";
                convert.printConvertWeight(str);
                break;
            }
            case 3:
            {
                convert.convertTroyOunce();
                str = " тройских унций";
                convert.printConvertWeight(str);
                break;
            }
            case 4:
            {
                convert.convertPood();
                str = " пуд";
                convert.printConvertWeight(str);
                break;
            }
            case 5:
            {
                convert.printOriginalWeight();
                break;
            }
            case 6:
            {
                cout << "До свидания! Спасибо что воспользовались нашей программой!\n" << endl;
                end = false;
                break;
            }
            default:
            {
                cout << "Данный пункт меню не найден, попробуйте еще раз!" << endl << endl;
                break;
            }
        }
    }
    system("pause");
    return 0;
}