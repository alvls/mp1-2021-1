/*
- Разработать класс Словарь переводчика.
- Класс должен предоставлять возможность формировать англо-русский словарь.
- В минимальном варианте каждому английскому слову соответствует ровно одно русское слово-перевод.
- Класс должен содержать необходимые служебные методы (конструкторы, деструктор и пр.).
- Класс должен предоставлять следующие операции:
+1) добавить в словарь слово и его перевод,
+2) изменить перевод указанного слова,
+3) узнать перевод выбранного слова,
+4) проверить наличие слова в словаре,
+5) узнать число слов в словаре,
+6) сохранить словарь в файл, //файл должен лежать в одной папке с прогой, пользователь вводит имя файла
+7) считать словарь из файла.
*/
#include <iostream>
#include <clocale> 
#include <string>
#include <windows.h>
#include <fstream> //для работы с файлами
#include <sstream> //для рабрты с файлами
#include <cctype> //для преобразования в строчные
#include <cstring>
#include <locale>

using namespace std;
const int SIZE_DIC = 100; //размер словаря
string Tolower(string str);

class Dictionary
{
private:
    string rus[SIZE_DIC];
    string eng[SIZE_DIC];
    int countDic; //кол-во слов в словаре
public:
    Dictionary()
    {
        rus[0];
        eng[0];
        countDic = 0;
    }
    Dictionary(string file)
    {
        ifstream in(file);
        int i = 0;
        countDic = 0;
        string line; // сюда читаем строки их файла 
        string rus_l, eng_l;
        if (!in) 
        {
            cout << "Файл не открылся. Выйдите из программы и создайте в папке с программой текстовый документ с именем Dictionary." << endl;
        }
        while (getline(in, line))
        {
            istringstream ist(line);
            ist >> eng_l;
            ist >> rus_l;
            eng[i] = eng_l;
            rus[i] = rus_l;
            i++;
        }
        countDic = i - 1;
    }
    Dictionary(string eng_word, string rus_word)
    {
        eng[0] = eng_word;
        rus[0] = rus_word;
        countDic = 1;
    }
    Dictionary& operator=(const Dictionary& str) //оператор присваивания
    {
        if (this == &str)
        {
            return *this;
        }
        for (int i = 0; i < countDic; i++)
        {
            eng[i] = str.eng[i];
            rus[i] = str.rus[i];
        }
        return *this;
    }
    void AddWord(string word, string translation) //добавить слово
    {
        int INDEX = countDic + 1;
        eng[INDEX] = word;
        rus[INDEX] = translation;
        countDic++; //увеличиваем кол-во слов в словаре
    }
    void changeTranslation(string word, string translation) //изменить перевод
    {
        for (int i = 0; i <= countDic; i++)
        {
            if (word == eng[i])
            {
                rus[i] = translation;
                break;
            }
        }
    }
    string getTranslation(string word) //узнать перевод
    {
        string str;
        for (int i = 0; i <= countDic; i++)
        {
            if (eng[i] == word)
            {
                int j = i;
                str = rus[i];
                return str;
            }
        }
    }

    bool presence(string word) //присутствие слова в словаре
    {
        for (int i = 0; i <= countDic; i++)
        {
            if (eng[i] == word)
            {
                return true;
                break;
            }
        }
        return false;
    }
    int sizeDictionary()
    {
        return countDic;
    }
    void saveDictoinary() //сохранить
    {
        ofstream file;
        file.open("Dictionary.txt");
        for (int i = 0; i <= countDic; i++)
        {
            file << eng[i];
            file << " ";
            file << rus[i];
            if (i < countDic) 
            { 
                file << endl; 
            }
        }
        file.close();
    }
    void readDictionary(string file) //считать
    {
        ifstream in(file);
        if (in.is_open())
        {
            string line; // сюда читаем строки из файла 
            while (getline(in, line))
            {
                cout << line << endl; 
            }
        }
        in.close();
    }
    ~Dictionary()
    {
    }
};
string Tolower(string str) //функция перевода в строчные 
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}
int main()
{
    setlocale(LC_ALL, "rus");
    int size_arr = 0;
    int choice_operation; //номер операции
    string word = "";
    string translation;
    SetConsoleCP(1251); //правильное чтение русского языка
    SetConsoleOutputCP(1251); //правильный вывод на консоль русских слов
    Dictionary objDictionary("Dictionary.txt");
    cout << "Добро пожаловать в Англо-русский словарь переводчика! " << endl;
    cout << "Все действия, произведенные Вами над словарем, не будут сохранены в файле," <<endl << "если по окончанию работы не выполнить пункт 6." << endl;
    while (1)
    {
        cout << " \nСписок операций:\n1) Добавить в словарь слово и его перевод, \n2) Изменить перевод указанного слова,\n3) Узнать перевод выбранного слова,\n4) Проверить наличие слова в словаре,\n5) Узнать число слов в словаре,\n6) Сохранить словарь в файл,\n7) Считать словарь из файла.\n8) Выход\n  " << endl;
        cout << "Введите номер нужного Вам пункта меню:  ";
        cin >> choice_operation;
        while (choice_operation < 1 || choice_operation>8)
        {
            cout << " Операции с таким номером нет. Пожалуйста, ведите нужный номер ещё раз: ";
            cin >> choice_operation;
        }
        switch (choice_operation)
        {
        case 1:
        {
            cout << " \nВведите слово(на английском языке), перевод которого вы хотите добавить в словать: ";
            cin >> word;
            word = Tolower(word);
            cout << " \nВведите перевод: ";
            cin >> translation;
            translation = Tolower(translation);
            objDictionary.AddWord(word, translation);
            break;
        }
        case 2:
        {
            cout << " \nВведите слово, перевод которого вы хотите изменить: ";
            cin >> word;
            word = Tolower(word);
            while (objDictionary.presence(word) != true)// проверка на существование этого слова в словаре 
            {
                cout << "Такого слова в словаре нет. Пожалуйста, введите нужное слово ещё раз: ";
                cin >> word;
                word = Tolower(word);
            }
            cout << " \nВведите новый перевод: ";
            cin >> translation;
            translation = Tolower(translation);
            objDictionary.changeTranslation(word, translation);
            break;
        }
        case 3:
        {
            cout << " \nВведите слово, перевод которого вы хотите узнать: ";
            cin >> word;
            word = Tolower(word);
            while (objDictionary.presence(word) == false)// проверка на существование этого слова в словаре 
            {
                cout << "Такого слова в словаре нет. Пожалуйста, введите нужное слово ещё раз: ";
                cin >> word;
                word = Tolower(word);
            }
            cout << "\nПеревод: " << objDictionary.getTranslation(word) << endl;
            break;
        }
        case 4:
        {
            cout << " \nВведите слово, наличие котрого вы хотите проверить: ";
            cin >> word;
            word = Tolower(word);
            if (objDictionary.presence(word) == false) {// проверка на существование этого слова в словаре 
                cout << "Такого слова в словаре нет." << endl;
            }
            if (objDictionary.presence(word) == true) {
                cout << "Такое слово есть в словаре." << endl;
            }
            break;
        }
        case 5:
        {
            cout << " \nЧисло слов в словаре: " << objDictionary.sizeDictionary() + 1 << endl;
            break;
        }
        case 6:
        {
            cout << " \nСохраняем словарь в файл." << endl;
            objDictionary.saveDictoinary();
            break;
        }
        case 7:
        {
            cout << " \nПроисходит считывание словаря из файла." << endl;
            objDictionary.readDictionary("Dictionary.txt");
            break;
        }
        case 8:
        {
            return 0;
        }
        }
    }
}