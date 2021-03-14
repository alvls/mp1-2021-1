/* 
Разработать класс Динамический массив.
Класс должен хранить заданное число вещественных элементов, размещаемых в динамической памяти.
Класс должен предоставлять следующие операции: 
1) задать размер массива, 
2) узнать размер массива, 
3) задать элемент массива по его индексу, 
4) узнать элемент массива по его индексу, 
5) найти минимальный элемент массива, 
6) проверить, является ли массив упорядоченным, 
7) выделить из массива подмассив с элементами с нечетными индексами.
Класс должен содержать все необходимые конструкторы, деструктор, оператор присваивания, а также «уметь» выводить себя на консоль. 
*/

#include <iostream>
#include <math.h>
using namespace std;
#pragma
class DynamicArray 
{
private:
    int size; //размер массива
    double *d_array; //динамический массив
public:
    DynamicArray() //конструктор класса
    {
        size = 1;
        d_array = new double[size];
    }
    DynamicArray(int size_k) //конструктор класса
    {
        SetDynamicArray(size_k);
    }
    void SetDynamicArray(int size_k) //создает массив пользователем введенного размера 
    {
        size = size_k;
        d_array = new double[size];
        for (int i = 0; i < size; i++)
        {
            d_array[i] = 0;
        }
    }
    void PrintArray() //печатает массив для наглядности 
    {
        for (int i = 0; i < size; i++)
        {
            cout << d_array[i] << " ";
        }
        cout << endl;
    }
    double FindValue(int num) //находит значение по индексу 
    {
        return d_array[num];
    }
    void SetValue(int ind, double znachenie) //задает значение по индексу 
    {
        d_array[ind] = znachenie;
    }
    double FindMin() //находит минимальное значение в массиве
    {
        int min = 0;
        for (int i = 0; i < size; i++)
        {
            if (d_array[min] > d_array[i])
                min = i;
        }
        return d_array[min];
    }
    bool CheckOrder() //проверка на упорядоченность
    {
        int k = 0, m = 0; //для отслеживания упорядоченности
        for (int i = 0; i < size; i++)
        {
            if ((d_array[i] >= d_array[i + 1]) && (k == 0) && (i + 1 < size))
            {
                k = 1; //Массив не является упорядоченным по возрастанию
            }
            if ((d_array[i] < d_array[i + 1]) && (m == 0) && (i + 1 < size))
            {
                m = 1; //Массив не является упорядоченным по убыванию
            }
        }
        if ((k == 1) && (m == 1))
            return false;
        if (((k == 1) && (m == 0)) || ((k == 0) && (m == 1)))
            return true;
    }
    DynamicArray* OddIndex() //создание нового массива, включающего в себя элементы исходного, стоящие на нечетных позициях
    {
        int s = ceil((size) / 2);
        DynamicArray* odd_array = new DynamicArray(s);
        int i, j;
        for ( i = 0, j = 0; j<size; i++, j+=2)
        {
            odd_array->SetValue(i, d_array[j]);
        }
        odd_array->PrintArray();
        return odd_array;
    }
    ~DynamicArray() //деструктор класса
    {
         delete[]d_array;
    }
};

int main()
{
    setlocale(LC_ALL, "rus");
    int size_arr = 0;
    int choice_operation; //номер операции
    int index = -1;//индекс переменной, которую хочет задать пользователь
    double valueOfIndex; //новое значение элемента массива
    int number; //номер переменной, значение которой запрашивает пользователь
    DynamicArray objDynamicArray(size_arr);
    cout << " Добро пожаловать в программу, позволяющую создавать динамические массивы и производить некоторые действия с ними! " << endl;
    while (1)
    {
        cout << " \nСписок операций:\n1) задать размер массива, \n2) узнать размер массива,\n3) задать элемент массива по его индексу,\n4) узнать элемент массива по его индексу, \n5) найти минимальный элемент массива, \n6) проверить, является ли массив упорядоченным,\n7) выделить из массива подмассив с элементами с нечетными индексами.\n8) Выход\n9) Печать\n  " << endl;
        cout << "Введите номер нужного Вам пункта меню:  ";
        cin >> choice_operation;
        while (choice_operation < 1 || choice_operation>9)
        {
            cout << " Операции с таким номером нет. Пожалуйста, ведите нужный номер ещё раз: ";
            cin >> choice_operation;
        }
        switch (choice_operation) 
        {
        case 1:
        {
            cout << " \nВведите размер массива: "; 
            cin >> size_arr;
            objDynamicArray.SetDynamicArray(size_arr);
            cout << " \nМассив на данный момент: ";
            objDynamicArray.PrintArray(); //печатает массив для наглядности 
            break;
        }
        case 2:
        {
            cout << " \nРазмер массива: " << size_arr << endl;
            break;
        }
        case 3:
        {
            cout << " \nЗадайте индекс элемента массива, значение которого вы хотите изменить: ";
            cin >> index;
            while (index < 0 || index > size_arr)
            {
                cout << "Элемента с таким индексом нет. Пожалуйста, введите нужный индекс ещё раз: ";
                cin >> index;
            }
            cout << " \nЗадайте значение элемента массива: ";
            cin >> valueOfIndex;
            objDynamicArray.SetValue(index, valueOfIndex);
            break;
        }
        case 4:
        {
            cout << " \nЗадайте индекс элемента массива, значение которого вы хотите узнать: ";
            cin >> number;
            while (number < 0 || number > size_arr)
            {
                cout << " Элемента с таким индексом нет. Пожалуйста, введите нужный индекс ещё раз: ";
                cin >> number;
            }
            cout << " \nЭлемент массива с индексом " << number << ": "<< objDynamicArray.FindValue(number);
            break;
        }
        case 5:
        {
            cout << " \nМинимальный элемент массива: "<<objDynamicArray.FindMin();
            break;
        }
        case 6://является ли упорядоченным 
        {
            if (objDynamicArray.CheckOrder() == true)
                cout << " \nМассив является упорядоченным. " << endl;
            if (objDynamicArray.CheckOrder() == false)
                cout << " \nМассив не является упорядоченным. " << endl;
            break;
        }
        case 7:
        {
            cout << " \nМассив элементов с нечетными индексами: ";
            objDynamicArray.OddIndex();
            break;
        }
        case 8:
        {
            return 0;
        }
        case 9:
        {
            objDynamicArray.PrintArray(); //печатает массив для наглядности
            break;
        }
        }
    }
    return 0;
}