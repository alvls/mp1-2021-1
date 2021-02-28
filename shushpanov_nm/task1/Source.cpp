#include <iostream>
using namespace std;

class ScaleConverter
{
private:
    bool check = true;
    double weight, originalWeight;
public:
    ScaleConverter()
    {
        weight = 9;
        originalWeight = 3.5;
    }
    void scanWeight(double weightInput)
    {
        originalWeight = weightInput;
    }
    void printOriginalWeight()
    {
        cout << "Исходный вес = " << originalWeight << " кг" << "\n" << endl;
    }
    void printConvertWeight(char* str)
    {
        cout << "Перевод " << originalWeight << "кг = " << weight << str << "\n" << endl;
    }
    double convertGrams()
    {
        weight = originalWeight * 1000;
        return weight;
    }
    double convertPharmacyPound()
    {
        weight = originalWeight * 2.679;
        return weight;
    }
    double convertTroyOunce()
    {
        weight = originalWeight * 32.151;
        return weight;
    }
    double convertPood()
    {
        weight = originalWeight / 16.381;
        return weight;
    }
};

int main()
{
    setlocale(LC_ALL, "rus");
    int indexMenu = 0;
    double weightInput;
    bool end = true, check = true;
    char* str;
    ScaleConverter convert;
    while (check)
    {
        cout << "Введите вес в килограммах (Если число не целое, вводите так: 3.5): ";
        cin >> weightInput;
        if (weightInput < 0)
        {
            cout << "Введенно отрицательное значение, программа работает только с положительными числами. Пожалуйста, попробуйте еще раз. \n" << endl;
        }
        else
        {
            convert.scanWeight(weightInput);
            check = false;
        }
    }
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