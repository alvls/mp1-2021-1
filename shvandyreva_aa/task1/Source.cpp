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

class KonverterDlin {
private:
    double metr;double foot, yard, fathom, arshin;
public:
    
    KonverterDlin(double metr_k) // конструктор класса
    {
        setMetr(metr_k);
    }
    void setMetr(double metr_k)
    {
        metr = metr_k;
        foot = 0;
        yard = 0;
        fathom = 0;
        arshin = 0;
    }
    void perevod_in_foot(double metr_k) //перевод в футы
    {
        double foot_one = 3.28083989501;
        foot = metr_k * foot_one;
    }
    void perevod_in_yard(double metr_k) //перевод в ярды
    {
        double yard_one = 1.09361329834;
        yard = metr_k * yard_one;
    }
    void perevod_in_fathom(double metr_k) //перевод в сажени
    {
        double fathom_one = 2.1336;
        fathom = metr_k * fathom_one;
    }
    void perevod_in_arshin(double metr_k) //перевод в аршины
    {
        double arshin_one = 0.7112;
        arshin = metr_k * arshin_one;
    }
    void CurrentMetr()
    {
        cout << " \nТекущая длина в метрах:  " << get_in_metr() << endl;
    }
    void CurrentFoot()
    {
        cout << " \nТекущая длина в футах:  " << get_in_foot() << endl;
    }
    void CurrentYard()
    {
        cout << " \nТекущая длина в ярдах:  " << get_in_yard() << endl;
    }
    void CurrentFathom()
    {
        cout << " \nТекущая длина в саженях:  " << get_in_fathom() << endl;
    }
    void CurrentArshin()
    {
        cout << " \nТекущая длина в аршинах:  " << get_in_arshin() << endl;
    }
    double get_in_metr() 
    {
        return metr;
    }
    double get_in_foot()
    {
        return foot;
    }
    double get_in_yard()
    {
        return yard;
    }
    double get_in_fathom()
    {
        return fathom;
    }
    double get_in_arshin()
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
                objKonverterDlin.perevod_in_foot(Metr);
                objKonverterDlin.CurrentFoot();
                break;
            }
            case 2:
            {
                objKonverterDlin.perevod_in_yard(Metr);
                objKonverterDlin.CurrentYard();
                break;
            }
            case 3:
            {
                objKonverterDlin.perevod_in_fathom(Metr);
                objKonverterDlin.CurrentFathom();
                break;
            }
            case 4:
            {
                objKonverterDlin.perevod_in_arshin(Metr);
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