
#include "all.h"

//private

vector<OneDay> Pedometer::GetVecOfFirstDaysInMonths()
{
    size_t SizeOfVec = VecOfDays.size();
    vector<OneDay> tmpvec;
    int CountOfMonths = 0;
    tmpvec.push_back(Date());
    tmpvec[0] = VecOfDays[0];
    for (size_t i = 1; i < SizeOfVec; i++)
    {
        if (tmpvec[CountOfMonths].GetDate().GetMonth() != VecOfDays[i].GetDate().GetMonth())
        {
            tmpvec.push_back(Date());
            tmpvec[++CountOfMonths] = VecOfDays[i];
        }
    }
    return tmpvec;
}

vector<OneDay> Pedometer::GetMonth(size_t pos)
{
    size_t SizeOfVec = VecOfDays.size();
    vector<OneDay> tmpvec = GetVecOfFirstDaysInMonths();
    OneDay tmponeday = tmpvec[pos - 1];
    tmpvec.clear();
    tmpvec.push_back(Date());
    tmpvec[0] = tmponeday;
    for (size_t i = 0; i < SizeOfVec; i++)
        if ((tmponeday.GetDate().GetMonth() == VecOfDays[i].GetDate().GetMonth()) && (tmponeday.GetDate().GetYear() == VecOfDays[i].GetDate().GetYear()))
            tmpvec.push_back(VecOfDays[i]);
    return tmpvec;
}

//Конструкторы

Pedometer::Pedometer()
{
    StartDate = Date();
    VecOfDays = vector<OneDay>();
}

Pedometer::Pedometer(Date date)
{
    StartDate = date;
    VecOfDays = vector<OneDay>();
}

//Вывод на экран 

void Pedometer::PrintPedometer(int type)
{
    cout << "\n Перечень событий: " << endl;
    size_t SizeOfVec = VecOfDays.size();
    if (type == 0)
        for (size_t i = 0; i < 10 && i < SizeOfVec; i++)
        {
            cout << i + 1 << ") ";
            VecOfDays[i].PrintDateOfDay();
            cout << "\n";
        }
    else
    {
        system("cls");
        for (size_t i = 0; i < SizeOfVec; i++)
        {
            cout << i + 1 << ") ";
            VecOfDays[i].PrintDateOfDay();
            cout << "\n";
        }
    }
}

size_t Pedometer::PrintMonths()
{
    vector<OneDay> tmpvec = GetVecOfFirstDaysInMonths();
    const string MonthName[12] = { "январь", "февраль", "март", "апрель", "май", "июнь", "июль", "август", "сентябрь", "октябрь", "ноябрь", "декабрь" };
    size_t sizeoftmpvec = tmpvec.size();
    cout << "\n Перечень доступных месяцев:\n";
    for (size_t i = 0; i < sizeoftmpvec; i++)
    {
        cout << " " << i + 1 << ") ";
        tmpvec[i].PrintMonthOfDay();
    }
    return sizeoftmpvec;
}

//Обработка "интересной" информации

double Pedometer::AverageInMonth(size_t pos)
{
    vector<OneDay> tmpvec = GetMonth(pos);
    size_t SizeOfVec = tmpvec.size();
    int AllSteps = 0;
    for (size_t i = 1; i < SizeOfVec; i++)
        AllSteps += tmpvec[i].GetStepsDay();
    double Days[13] = { 29,31,28,31,30,31,30,31,31,30,31,30,31 };
    int tmpmonth = tmpvec[0].GetDate().GetMonth();
    if ((tmpmonth == 2) && leap(tmpmonth, tmpvec[0].GetDate().GetYear()))
        tmpmonth = 0;
    return double(AllSteps) / Days[tmpmonth];
}

double Pedometer::AverageInAllHistory()
{
    int daysbtwbounds = StartDate.DateDifference(VecOfDays[VecOfDays.size() - 1].GetDate()); // Days between bounds
    int AllSteps = 0;
    size_t SizeOfVec = VecOfDays.size();
    for (size_t i = 0; i < SizeOfVec; i++)
        AllSteps += VecOfDays[i].GetStepsDay();
    return double(AllSteps) / (double(daysbtwbounds) + 1);
}

double Pedometer::AverageInWeekDay(int selectedweekday)
{
    size_t SizeOfVec = VecOfDays.size();
    int CountOfWeekDays = 0;
    int StepsInWeekDay = 0;
    int daysbtwbounds = StartDate.DateDifference(VecOfDays[VecOfDays.size() - 1].GetDate()); // Days between bounds
    // Для того, чтобы понять, сколько было дней недели за весь период подсчётов
    // Например: у нас может быть заполнено 3 понедельника, в то время как всего понедельников 
    // в рамках ведения подсчётов было 5. Код с 87 стр. по 95 стр. считает кол-во понедельников == 5, а не 3
    int tmpweekday = VecOfDays[0].GetDate().GetWeekDay();
    for (int i = 0; i <= daysbtwbounds; i++)
    {
        if (selectedweekday == tmpweekday)
            CountOfWeekDays++;
        tmpweekday++;
        if (tmpweekday == 7)
            tmpweekday = 0;
    }
    for (size_t i = 0; i < SizeOfVec; i++)
        if (selectedweekday == VecOfDays[i].GetDate().GetWeekDay())
            StepsInWeekDay += VecOfDays[i].GetStepsDay();
    if (StepsInWeekDay == 0)
        return 0;
    return double(StepsInWeekDay) / double(CountOfWeekDays);
}

OneDay Pedometer::MaxInMonth(size_t pos)
{
    vector<OneDay> tmpvec = GetMonth(pos);
    size_t SizeOfVec = tmpvec.size();
    OneDay tmpmax = tmpvec[0];
    for (size_t i = 1; i < SizeOfVec; i++)
        if (tmpmax.GetStepsDay() < tmpvec[i].GetStepsDay())
            tmpmax = tmpvec[i];
    return tmpmax;
}

OneDay Pedometer::MaxInDay()
{
    size_t SizeOfVec = VecOfDays.size();
    OneDay tmponeday = VecOfDays[0];
    for (size_t i = 1; i < SizeOfVec; i++)
        if (tmponeday.GetStepsDay() < VecOfDays[i].GetStepsDay())
            tmponeday = VecOfDays[i];
    return tmponeday;
}

//Работа с файлами

void Pedometer::SaveInFile()
{
    fstream fs;
    fs.open("Pedometer.txt", fstream::out);
    if (!fs.is_open())
        throw exception("Не удалось открыть файл!");
    size_t SizeOfVecOfDays = VecOfDays.size();
    fs << StartDate << " " << SizeOfVecOfDays << "\n";
    for (size_t i = 0; i < SizeOfVecOfDays; i++)
        fs << VecOfDays[i];
    fs.close();
}

void Pedometer::ReadFromFile()
{
    fstream fs;
    fs.open("Pedometer.txt", fstream::in);
    if (!fs.is_open())
        throw exception("Не удалось открыть файл!");
    fs >> StartDate;
    size_t NewSizeOfVec;
    fs >> NewSizeOfVec;
    VecOfDays.clear();
    for (size_t i = 0; i < NewSizeOfVec; i++)
    {
        OneDay tmpday;
        fs >> tmpday;
        VecOfDays.push_back(tmpday);
    }
    fs.close();
}

//Операторы

ostream& operator<<(ostream& os, const Pedometer& pedometer)
{
    size_t SizeOfVecOfDays = pedometer.VecOfDays.size();
    os << pedometer.StartDate << " " << SizeOfVecOfDays << "\n";
    for (size_t i = 0; i < SizeOfVecOfDays; i++)
        os << pedometer.VecOfDays[i] << "\n";
    return os;
}

istream& operator>>(istream& is, Pedometer& pedometer)
{
    is >> pedometer.StartDate;
    size_t NewSizeOfVec;
    is >> NewSizeOfVec;
    pedometer.VecOfDays.clear();
    for (size_t i = 0; i < NewSizeOfVec; i++)
    {
        OneDay tmpday;
        is >> tmpday;
        pedometer.VecOfDays.push_back(tmpday);
    }
    return is;
}

//Random Generator

void Pedometer::RandomGenerator(size_t value)
{
    srand(time(NULL));
    int tmprand;
    Date tmpdate;
    Time tmpLB;
    Time tmpRB;
    int tmpsteps;
    VecOfDays.clear();
    VecOfDays.push_back(Date());
    VecOfDays[0].SetDate(StartDate);
    tmprand = rand() % 7 + 1;
    for (int k = 0; k < tmprand; k++)
    {
        tmpLB.hour = k;
        tmpLB.minutes = k;
        tmpRB.hour = k + 1;
        tmpRB.minutes = k + 1;
        tmpsteps = rand() % 6000 + 100;
        VecOfDays[0].SetOneCount(Count(tmpLB, tmpRB, tmpsteps));
    }
    VecOfDays[0].SetStepsDay();
    for (size_t i = 1; i < value; i++)
    {
        tmprand = rand() % 2 + 1;
        VecOfDays.push_back(Date());
        tmpdate = VecOfDays[i - 1].GetDate() + tmprand;
        VecOfDays[i].SetDate(tmpdate);
        tmprand = rand() % 7 + 1;
        for (int k = 0; k < tmprand; k++)
        {
            tmpLB.hour = k;
            tmpLB.minutes = k;
            tmpRB.hour = k + 1;
            tmpRB.minutes = k + 1;
            tmpsteps = rand() % 6000 + 100;
            VecOfDays[i].SetOneCount(Count(tmpLB, tmpRB, tmpsteps));
        }
        VecOfDays[i].SetStepsDay();
    }
}
