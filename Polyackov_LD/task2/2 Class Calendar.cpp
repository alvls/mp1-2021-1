#include "all.h"

Calendar::Calendar()
{
	size = MAX_EVENTS;
    counter = 0;
	arr = new Date[size];
}

Calendar::Calendar(const Calendar& other)
{
    size = other.size;
    counter = other.counter;
    arr = new Date[size];
    for (int i = 0; i < size; i++)
        arr[i] = other.arr[i];
}

void Calendar::PrintCalendar()
{
    cout << "\n �������� �������: " << endl;
    for (int i = 0; i < counter; i++)
        cout << i + 1 << ") " << arr[i].GetEvent() << endl;
}

int Calendar::ExistLastDate()
{
    //�������� �� ��������� � �������� >= 01.01.0001
    if (arr[counter - 1].GetYear() <= 0)
        return 1;
    //�������� �� ������������
    for (int i = 0; i < counter - 1; i++)
        if (arr[counter - 1] == arr[i])
            return 2;
    return 0;
}

void Calendar::DeleteLastDate()
{
    Date tmp;
    arr[--counter] = tmp;
}

void Calendar::AddMemory()
{
    Calendar tmp(*this);
    size *= 2;
    delete[]arr;
    arr = nullptr;
    arr = new Date[size];
    for (int i = 0; i < size/2; i++)
        arr[i] = tmp[i];
    // ����� ������ �� ���� ������� ���������� ~Calendar() ��� tmp
}

Calendar& Calendar::operator= (const Calendar& other)
{
    if (this == &other)
        return *this;
    size = other.size;
    counter = other.counter;
    delete[]arr;
    arr = new Date[size];
    for (int i = 0; i < size; i++)
        arr[i] = other.arr[i];
    return *this;
}

Date& Calendar::operator[] (const int index)
{
    return arr[index];
}

Calendar::~Calendar()
{
	delete[]arr;
}
