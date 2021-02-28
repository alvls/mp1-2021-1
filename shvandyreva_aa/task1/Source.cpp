/*
Разработать класс Конвертер длин.
- Класс должен хранить длину в метрах и предоставлять методы по ее преобразованию 
в другие единицы измерения (например, фут, ярд, аршин, сажень, …).
- Класс должен предоставлять операции: 
+ 1) установить текущую длину в метрах, 
+ 2) узнать текущую длину в метрах, 
+ 3) узнать текущую длину в выбранной единице измерения (из списка поддерживаемых).
- Класс должен содержать все необходимые конструкторы, оператор присваивания, а 
также «уметь» выводить себя на консоль.
*/
#include <iostream>
using namespace std;

class KonverterDlin 
{
private:
    double metr;
    double foot, yard, fathom, arshin;
public:
    
    KonverterDlin(double metr_k) // конструктор класса
    {
        setMetr(metr_k);
    }
    void setMetr(double metr_k)
    {
        metr = metr_k;
        foot = metr_k * 3.28083989501;//перевод в футы
        yard = metr_k * 1.09361329834;//перевод в ярды
        fathom = metr_k * 2.1336;//перевод в сажени
        arshin = metr_k * 0.7112;//перевод в аршины
    }
    void CurrentMetr()
    {
        cout << " \nТекущая длина в метрах:  " << GetMetr() << endl;
    }
    void CurrentFoot()
    {
        cout << " \nТекущая длина в футах:  " << GetFoot() << endl;
    }
    void CurrentYard()
    {
        cout << " \nТекущая длина в ярдах:  " << GetYard() << endl;
    }
    void CurrentFathom()
    {
        cout << " \nТекущая длина в саженях:  " << GetFathom() << endl;
    }
    void CurrentArshin()
    {
        cout << " \nТекущая длина в аршинах:  " << GetArshin() << endl;
    }
    double GetMetr() 
    {
        return metr;
    }
    double GetFoot()
    {
        return foot;
    }
    double GetYard()
    {
        return yard;
    }
    double GetFathom()
    {
        return fathom;
    }
    double GetArshin()
    {
        return fathom;
    }
};

int main()
{
    setlocale(LC_ALL, "rus");
    double Metr=0;
    int choice_operation, choice_ed_izm;
    KonverterDlin objKonverterDlin(Metr);
    cout << " Добро пожаловать в конвертер длин! " << endl;
    while (1) 
    {
        cout << " Список операций:\n1) Установить текущую длину в метрах\n2) Узнать текущую длину в метрах\n3) Перевести в новую единицу измерения (из списка поддерживаемых)\n4) Выход\n " << endl;
        cout << " Введите номер нужного Вам пункта меню:  ";
        cin >> choice_operation;
        while (choice_operation < 1 || choice_operation>4)
        {
            cout << " Операции с таким номером нет. Пожалуйста, ведите нужный номер ещё раз:\n " << endl;
            cin >> choice_operation;
        }
        switch (choice_operation)
        {
        case 1:
        {
            cout << " \nВведите длину в метрах: " << endl; //вывод на экрна
            cin >> Metr;
            objKonverterDlin.setMetr(Metr);
            break;
        }
        case 2:
        {
            objKonverterDlin.CurrentMetr();
            break;
        }
        case 3:
        {
            cout << " \nВыберите из списка единицу измерения, в которую вы бы хотели перевести метры: \n" << endl;
            cout << "1) Футы\n2) Ярды\n3) Сажени\n4) Аршины\n " << endl;
            cin >> choice_ed_izm;
            while (choice_ed_izm < 1 || choice_ed_izm>4)
            {
                cout << " Операции с таким номером нет. Пожалуйста, ведите нужный номер ещё раз:\n " << endl;
                cin >> choice_ed_izm;
            }
            switch (choice_ed_izm)
            {
            case 1:
            {
                objKonverterDlin.CurrentFoot();
                break;
            }
            case 2:
            {
                objKonverterDlin.CurrentYard();
                break;
            }
            case 3:
            {
                objKonverterDlin.CurrentFathom();
                break;
            }
            case 4:
            {
                objKonverterDlin.CurrentArshin();
                break;
            }
            }
            break;
        }
        case 4:
        {
            system("pause");
            return 0;
        }
        }
    }
    return 0;
}