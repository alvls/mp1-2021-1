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
    int index_element; //индекс элемента
    double* odd_array; //динамический массив элементов на нечетных индексах
public:
    DynamicArray() //конструктор класса
    {
        d_array = new double[1];
        d_array[0] = 0;
    }
    DynamicArray(int size_k) //конструктор класса
    {
        index_element = 0;
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
        odd_array = new double[ceil((size)/2)]; //размер массива с нечетными в два раза меньше исходного
        for (int i = 0; i < ceil((size)/2); i++) //ceil - округление в бОльшую сторону
        {
            odd_array[i] = 0;
        }
    }
    void PrintArray(int size_k) //печатает массив для наглядности 
    {
        size = size_k;
        for (int i = 0; i < size; i++)
        {
            cout << d_array[i] << " ";
        }
        cout << endl;
    }
    double FindValue(int num) //находит значение по индексу 
    {
        return d_array[num - 1];
    }
    void SetValue(int ind, double znachenie) //задает значение по индексу 
    {
        index_element = ind-1;
        d_array[index_element] = znachenie;
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
    void CheckOrder() //проверка на упорядоченность
    {
        int k=0,m=0; //для отслеживания упорядоченности
        for (int i = 0; i < size; i++)
        {
            if ((d_array[i] > d_array[i + 1])&&(k==0)&&(i+1<size))
            {
                k = 1; //Массив не является упорядоченным по возрастанию
            }
            if ((d_array[i] < d_array[i + 1])&&(m==0) && (i + 1 < size))
            {
                m = 1; //Массив не является упорядоченным по убыванию
            }
        }
        if ((k==1)&&(m==1))
        {
            cout << "Массив не является упорядоченным. ";
        }
        if ((k==1)&&(m==0))
        {
            cout << "Массив является упорядоченным по убыванию. ";
        }
        if ((k==0)&&(m==0))
        {
            cout << "Элементы массива имеют одинаковые значения. ";
        }
        if ((k==0)&&(m==1))
        {
            cout << "Массив является упорядоченным по возрастанию. ";
        }
    }
    void OddIndex() //создание нового массива, включающего в себя элементы исходного, стоящие на нечетных позициях
    {
        int i, j;
        for ( i = 0, j = 0; j<size; i++, j+=2)
        {
            odd_array[i] = d_array[j];
            cout << odd_array[i] << " ";
        }
    }
    ~DynamicArray() //деструктор класса
    {
         delete[]d_array;
         delete[]odd_array;
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
            objDynamicArray.PrintArray(size_arr); //печатает массив для наглядности 
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
        case 6:
        {
            objDynamicArray.CheckOrder();//является ли упорядоченным 
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
            objDynamicArray.PrintArray(size_arr); //печатает массив для наглядности
            break;
        }
        }
    }
    return 0;
}