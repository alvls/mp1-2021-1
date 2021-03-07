
#include "all.h"

bool menu()
{
    int tmpnum = -1;
    static int counter = 0;
    static int size = MAX_EVENTS;
    static Date* arr = new Date[size]; //Для хранения событий
    int vibor = -1;
    cout << "\n Сейчас Вы находитесь в меню. Выберите, что нужно сделать :\n\t(1) Установить событие \n\t(2) Узнать дату выбранного события \n\t(3) Вычислить разницу между заданной датой и датой события \n\t(4) Сформировать новое событие, сдвинув выбранное существующее\n\tсобытие на заданное смещение в меньшую или в большую сторону\n\t(0) Выйти из программы" << endl;
    vibor = proverka(0, 4);
    if ((counter == 0) && ((vibor == 2) || (vibor == 3) || (vibor == 4)))
    {
        cout << "\n Для работы режима (" << vibor << ") требуется хотя бы одно событие.\n К сожалению, у Вас нет установленных событий.\n" << endl;
        system("pause");
        system("cls");
        return true;
    }
    system("cls");
    switch (vibor)
    {
    case 1:
        cout << "\n Вы выбрали действие \n\t\"Установить событие\"." << endl;
        arr[counter++] = CreateNewDate();
        system("cls");
        cout << "\n Вы сформировали событие \"" << arr[counter - 1].GetEvent() << "\"\n Номер события: " << counter << endl << endl;
        break;
    case 2:
        cout << "\n Вы выбрали действие \n\t\"Узнать дату выбранного события\"." << endl;;
        tmpnum = SelectedEvent(counter, arr);
        cout << "\n Дата выбранного события: ";
        arr[tmpnum].PrintDate();
        cout << endl;
        break;
    case 3:
        // 3) вычислить разницу между заданной датой и датой события (в днях), 
        rezhim3(arr, counter);
        break;
    case 4:
        // 4) сформировать новое событие, сдвинув выбранное существующее событие на заданное смещение(в днях) в меньшую и в большую сторону.
        // Можно вводить хоть десятки миллионов - работает быстро, чётко и с поддержкой високосности
        rezhim4(arr, counter);
        break;
    case 0:
        delete[]arr;
        arr = nullptr;
        return false;
        break;
    default:
        cout << "Непредвиденная ошибка." << endl;
        delete[]arr;
        arr = nullptr;
        return false;
        break;
    }
    if (counter == size)
        arr = RecreateArr(arr, size, counter);
    ExistDate(arr, counter);
    system("pause");
    system("cls");
    return true;
}

void rezhim3(Date* arr, int& counter)
{
    int tmpnum = -1;
    Date tmpDate;
    int tmpdays;
    cout << "\n Вы выбрали действие \n\t\"Вычислить разницу между заданной датой и датой события (в днях)\".\n\n Задайте дату.\n\n Введите год (>=1): " << endl;
    cout << "";
    tmpDate.SetYear(proverka(1, INT_MAX));
    cout << "\n Введите месяц (от 1 до 12): ";
    tmpDate.SetMonth(proverka(1, 12));
    tmpdays = MonthDays(tmpDate.GetMonth(), tmpDate.GetYear());
    cout << "\n Введите день (от 1 до " << tmpdays << "): ";
    tmpDate.SetDay(proverka(1, tmpdays));
    cout << "\n Теперь выберите нужное событие " << endl;
    tmpnum = SelectedEvent(counter, arr);
    cout << "\n Заданная дата: ";
    tmpDate.PrintDate();
    cout << "\n Разница между датой события и Вашей датой: " << arr[tmpnum].DateDifference(tmpDate) << " д." << endl << endl;
}

void rezhim4(Date* arr, int& counter)
{
    int tmpnum = -1;
    int vibor = -1;
    int tmpdays = -1;
    cout << "\n Вы выбрали действие \n\t\"Сформировать новое событие, сдвинув выбранное существующее\n\tсобытие на заданное смещение в меньшую или в большую сторону\"." << endl;
    tmpnum = SelectedEvent(counter, arr);
    cout << "\n На сколько дней Вы хотите передвинуть событие? (>=1)" << endl;
    tmpdays = proverka(1, INT_MAX);
    cout << "\n В какую сторону Вы хотите передвинуть выбранное событие?\n\t1) В большую сторону\n\t2) В меньшую сторону" << endl;
    vibor = proverka(1, 2);
    if (vibor == 1)
        arr[counter++] = arr[tmpnum] + tmpdays;
    if (vibor == 2)
        arr[counter++] = arr[tmpnum] - tmpdays;
    system("cls");
    cout << "\n Вы сформировали событие \"" << arr[counter - 1].GetEvent() << "\"\n Номер события: " << counter << endl << endl;
}
