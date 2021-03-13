#include "all.h"

bool menu()
{
    static Calendar list;
    int vibor = -1;
    cout << "\n Сейчас Вы находитесь в меню. Выберите, что нужно сделать :\n\t(1) Установить событие \n\t(2) Узнать дату выбранного события \n\t(3) Вычислить разницу между заданной датой и датой события \n\t(4) Сформировать новое событие, сдвинув выбранное существующее\n\tсобытие на заданное смещение в меньшую или в большую сторону\n\t(0) Выйти из программы" << endl;
    vibor = proverka(0, 4);
    if ((list.GetCounter() == 0) && ((vibor == 2) || (vibor == 3) || (vibor == 4)))
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
        // 1) Установить событие
        rezhim1(list);
        break;
    case 2:
        // 2) Узнать дату выбранного события
        rezhim2(list);
        break;
    case 3:
        // 3) вычислить разницу между заданной датой и датой события (в днях), 
        rezhim3(list);
        break;
    case 4:
        // 4) сформировать новое событие, сдвинув выбранное существующее событие на заданное смещение(в днях) в меньшую и в большую сторону.
        rezhim4(list);
        break;
    case 0:
        return false;
        break;
    default:
        cout << "Непредвиденная ошибка." << endl;
        return false;
        break;
    }
    CheckingForExistence(list);
    MemoryAssistant(list);
    system("pause");
    system("cls");
    return true;
}

void CheckingForExistence(Calendar& list)
{
    switch (list.ExistLastDate())
    {
    case 1:
        cout << "\n К сожалению, дата последнего события получила неподдерживаемое значение.\n Программа удалила данное событие.\n" << endl;
        list.DeleteLastDate();
        break;
    case 2:
        cout << "\n К сожалению, дата последнего события совпала с одной из существующих дат.\n Программа удалила данное событие.\n" << endl;
        list.DeleteLastDate();
        break;
    default:
        break;
    }
}

void MemoryAssistant(Calendar& list)
{
    if (list.GetCounter() == list.GetSize())
        list.AddMemory();
}

void rezhim1(Calendar& list)
{
    int count = list.GetCounter();
    cout << "\n Вы выбрали действие \n\t\"Установить событие\"." << endl;
    list[count] = CreateNewDate();
    list.SetCounterPlusOne();
    system("cls");
    cout << "\n Вы сформировали событие \"" << list[count].GetEvent() << "\"\n Номер события: " << count + 1 << endl << endl;
}

void rezhim2(Calendar& list)
{
    int tmpnum = -1;
    cout << "\n Вы выбрали действие \n\t\"Узнать дату выбранного события\"." << endl;;
    tmpnum = SelectedEvent(list);
    cout << "\n Дата выбранного события: ";
    list[tmpnum].PrintDate();
    cout << endl;
}

void rezhim3(Calendar& list)
{
    int tmpnum = -1;
    Date tmpDate;
    int tmpdays;
    cout << "\n Вы выбрали действие \n\t\"Вычислить разницу между заданной датой и датой события (в днях)\".\n\n Задайте дату.\n\n Введите год (>=1): ";
    cout << "";
    tmpDate.SetYear(proverka(1, INT_MAX));
    cout << "\n Введите месяц (от 1 до 12): ";
    tmpDate.SetMonth(proverka(1, 12));
    tmpdays = MonthDays(tmpDate.GetMonth(), tmpDate.GetYear());
    cout << "\n Введите день (от 1 до " << tmpdays << "): ";
    tmpDate.SetDay(proverka(1, tmpdays));
    cout << "\n Теперь выберите нужное событие " << endl;
    tmpnum = SelectedEvent(list);
    cout << "\n Заданная дата: ";
    tmpDate.PrintDate();
    cout << "\n Разница между датой события и Вашей датой: " << list[tmpnum].DateDifference(tmpDate) << " д." << endl << endl;
}

void rezhim4(Calendar& list)
{
    int tmpnum = -1;
    int vibor = -1;
    int tmpdays = -1;
    int count = list.GetCounter();
    cout << "\n Вы выбрали действие \n\t\"Сформировать новое событие, сдвинув выбранное существующее\n\tсобытие на заданное смещение в меньшую или в большую сторону\"." << endl;
    tmpnum = SelectedEvent(list);
    cout << "\n На сколько дней Вы хотите передвинуть событие? (>=1)" << endl;
    tmpdays = proverka(1, INT_MAX);
    cout << "\n В какую сторону Вы хотите передвинуть выбранное событие?\n\t1) В большую сторону\n\t2) В меньшую сторону" << endl;
    vibor = proverka(1, 2);
    if (vibor == 1)
        list[count] = list[tmpnum] + tmpdays;
    if (vibor == 2)
        list[count] = list[tmpnum] - tmpdays;
    list.SetCounterPlusOne();
    system("cls");
    cout << "\n Вы сформировали событие \"" << list[count].GetEvent() << "\"\n Номер события: " << count + 1 << endl << endl;
}
