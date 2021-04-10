#include <iostream>
#include <string>
#include <fstream>
#define NUMOFINDATES 10
using namespace std;
class Termo
{
private:
    struct Data
    {
        int day, month;
        double* temp;
        int datacode;
    };
    int CntOfRec,MemorySize,StHour,year;
    Data* mass;
    int RecInMonths[12] = { 0 };
    void operator= (const Termo&){};
    void MemoryAllocator()
    {
        Data* nmass = new Data[MemorySize*2];
        for(int i = 0;i < MemorySize;i++){
            nmass[i].day = mass[i].day;
            nmass[i].month = mass[i].month;
            nmass[i].datacode = mass[i].datacode;
            for(int k=0;k<24;k++){
                nmass[i].temp[k] = mass[i].temp[k];
            }
        }
        delete [] mass;
        mass = nmass;
        MemorySize*=2;
    }
    void QSort(int low,int high)
    {
    int i = low;
    int j = high;
    int pivot = mass[(i + j) / 2].datacode;
    while (i <= j)
    {
        while (mass[i].datacode < pivot)
            i++;
        while (mass[j].datacode > pivot)
            j--;
        if (i <= j)
        {
            double* temp = mass[i].temp;
            int day = mass[i].day;
            int month = mass[i].month;
            int datacode = mass[i].datacode;
            mass[i].temp = mass[j].temp;
            mass[i].day = mass[j].day;
            mass[i].month = mass[j].month;
            mass[i].datacode = mass[j].datacode;
            mass[j].temp = temp;
            mass[j].day = day;
            mass[j].month = month;
            mass[j].datacode = datacode;
            i++;
            j--;
        }
    }
    if (j > low){
        QSort(low,j);
    }
    if (i < high){
        QSort(i,high);
    }
    }
public:
    Termo() : CntOfRec(0),MemorySize(NUMOFINDATES)
    {
        mass = new Data[NUMOFINDATES];
    }
    Termo(int _day, int _month, int _hour,int _year) : CntOfRec(1),MemorySize(NUMOFINDATES)
    {
        mass = new Data[NUMOFINDATES];
        mass[0].day = _day;
        mass[0].month = _month;
        mass[0].temp = new double[24];
        for (int i = 0; i < 24; i++) {
            mass[0].temp[i] = 255.0;
        }
        mass[0].datacode  =_day + _month*100;
        RecInMonths[_month-1]++;
        year = _year;
        StHour = _hour;
    }
    ~Termo()
    {
        for(int i = 0;i < CntOfRec;i++){
            delete [] mass[i].temp;
        }
        delete [] mass;
    }
    Termo(const Termo& other)
    {
        CntOfRec = other.CntOfRec;
        MemorySize = other.MemorySize;
        StHour = other.MemorySize;
        year = other.year;
        mass = new Data [MemorySize];
        for(int k = 0;k < 12;k++){
            RecInMonths[k] = other.RecInMonths[k];
        }
        for(int i = 0;i < CntOfRec;i++){
            mass[i].day = other.mass[i].day;
            mass[i].month = other.mass[i].month;
            mass[i].datacode = other.mass[i].datacode;
            mass[i].temp = new double [24];
            for(int z = 0;z < 24;z++){
                mass[i].temp[z] = other.mass[i].temp[z];
            }
        }
    }
    bool Set_In(int _day, int _month, int _hour,int _year)
    {
        if(CntOfRec > 0){return false;}
        mass[0].day = _day;
        mass[0].month = _month;
        mass[0].temp = new double[24];
        for (int i = 0; i < 24; i++) {
            mass[0].temp[i] = 255.0;
        }
        RecInMonths[_month-1]++;
        CntOfRec = 1;
        StHour = _hour;
        year = _year;
        mass[0].datacode = _day + _month * 100;
        return true;
    }
    void Get_Init(int& _day, int& _month, int& _hour,int& _year)
    {
        _day = mass[0].day;
        _month = mass[0].month;
        _hour = StHour;
        _year = year;
    }
    bool Set_Obs(int _day, int _month, int _hour, double _temp)
    {
        if (!CntOfRec) { return false; }
        if ((_day > 31) || (_month > 12)) { return false; }
        if(CntOfRec == MemorySize){MemoryAllocator();}
        if((mass[0].day == _day)&&(mass[0].month == _month)&&(_hour < StHour))
        {return false;}
        mass[CntOfRec].temp = new double[24];
        for (int i = 0; i < 24; i++) {
            mass[CntOfRec].temp[i] = 255.0;
        }
        RecInMonths[_month-1]++;
        mass[CntOfRec].temp[_hour] = _temp;
        mass[CntOfRec].day = _day;
        mass[CntOfRec].month = _month;
        mass[CntOfRec].datacode = _day + _month * 100; 
        CntOfRec++;
        QSort(0,CntOfRec-1);
        return true;
    }
    double Get_Obs(int _day, int _month, int _hour)
    {
        if (!CntOfRec) { return -1.0; }
        if ((_day > 31) || (_month > 12)) { return -1.0; }
        int k = 0;
        for (int i = 0; i < _month-1; i++) {
            k += RecInMonths[i];
        }
        for (int z = k; z < k+RecInMonths[_month-1]; z++) {
        if (mass[z].day == _day) {
                if ((mass[z].temp[_hour] > 250) || (mass[z].temp[_hour] < -250)) {}
                else {
                    return mass[z].temp[_hour];
                }
            }
        }
        throw string("No record with this time,day,month");
    }
    bool Set_Obs_Serial(int _day, int _month, int _shour, int _ehour, double _temp[])
    {
        if(!CntOfRec){return false;}
        if(CntOfRec == MemorySize ){MemoryAllocator();}
        if ((_day > 31) || (_month > 12)) { return false; }
        if((mass[0].day == _day)&&(mass[0].month == _month)&&(_shour < StHour))
        {return false;}
        mass[CntOfRec].temp = new double[24];
        for (int i = _shour - 1; i < _ehour; i++) {
            mass[CntOfRec].temp[i] = _temp[i + 1 - _shour];
        }
        mass[CntOfRec].day = _day;
        mass[CntOfRec].month = _month;
        RecInMonths[_month-1]++;
        CntOfRec++;
        QSort(0,CntOfRec-1);
        return true;
    }
    double Get_Av_Day(int _day,int _month)
    {
        int k = 0;
        for (int i = 0; i < _month-1; i++) {
            k += RecInMonths[i];
        }
        for (int z = k; z < k + RecInMonths[_month - 1]; z++) {
            if (mass[z].day == _day) {
                double av = 0.0;
                double r = 0.0;
                for(int b = 0;b < 24;b++){
                    if ((mass[z].temp[b] > 250) || (mass[z].temp[b] < -250)) {}
                    else{
                        r++;
                        av += mass[z].temp[b];
                    }
                }
            return av/r;
            }
        }
        throw string("No record with this day and month");
    }
    double Get_Av_Month(int _month)
    {
        int k = 0;
        for (int i = 0; i < _month-1; i++) {
            k += RecInMonths[i];
        }
        int count = 0;
        double av = 0.0;
        double r = 0.0;
        for (int z = k; z < k+ RecInMonths[_month-1]; z++) {
            for(int b = 0;b < 24;b++){
                if ((mass[z].temp[b] > 250) || (mass[z].temp[b] < -250)) {}
                else{
                    r++;
                    av+=mass[z].temp[b];
                    count++;
                }
            }
        }
        if(!count){throw string("No record with month");}
        return av/r;
    }
    double Get_Av_All()
    {
        if(!CntOfRec){throw string("There are no records");}
        double av = 0.0;
        int r = 0;
        for (int k = 0; k < CntOfRec; k++) {
            for(int z = 0;z < 24;z++){
                if ((mass[k].temp[z] > 250) || (mass[k].temp[z] < -250)) {}
                else {
                    r++;
                    av+=mass[k].temp[z];
                }
            }
        }
        return av / r;
    }
    bool To_File(string path)
    {
        ofstream fout;
        fout.open(path);
        if (!fout) { return false; }
        fout << year << " " << CntOfRec << " " << StHour << endl;
        fout << mass[0].day << " " << mass[0].month << " " << -1 << " " << 255 << endl;
        for (int i = 0; i < CntOfRec; i++) {
            for (int k = 0; k < 24; k++) {
                if ((mass[i].temp[k] > 250) || (mass[i].temp[k] < -250)) {}
                else {
                    fout << mass[i].day << " " << mass[i].month << " " << k << " " << mass[i].temp[k] << endl;
                }
            }
        }
        fout.close();
        return true;
    }
    bool From_File(string path)
    {
        int buf;
        int day,month;
        int oldday, oldmonth,oldt = -1;
        ifstream fin;
        fin.open(path);
        if (!fin) { return false; }
        else {
        for (int i = 0; i < CntOfRec; i++) {
            delete[] mass[i].temp;
        }
        delete[] mass;
        for (int i = 0; i < 12; i++) {
            RecInMonths[i] = 0;
        }
        fin >> year >> CntOfRec >> StHour;
        mass = new Data[CntOfRec];
        int i = 0;
        fin >> day >> month;
        oldday = day;
        oldmonth = month;
        mass[0].day = day;
        mass[0].month = month;
        mass[0].datacode = day + 100 * month;
        RecInMonths[month-1]++;
        fin >> buf >> buf;
        mass[0].temp = new double[24];
        for (int i = 0; i < 24; i++) {
            mass[0].temp[i] = 255.0;
        }
        while (!fin.eof()) {
            fin >> day >> month;
            if ((day!=oldday)||(month!=oldmonth)){
                i++;
                mass[i].temp = new double[24];
                for (int z = 0; z < 24; z++) {
                    mass[i].temp[z] = 255.0;
                }
            }
            else{
                oldday = day;
                oldmonth = month;
            }
            fin >> buf;
            if (buf == oldt) {
                break;
            }
            fin >> mass[i].temp[buf];
            buf = oldt;
            mass[i].day = day;
            mass[i].month = month;
            mass[i].datacode = day + 100*month;
            RecInMonths[month-1]++;
            }
        }
        fin.close();
        MemorySize = CntOfRec;
        return true;
    }
};
int main() {
    try{
        Termo a(1,1,2,2020);;
        a.Set_Obs(2,2,2,4);
        a.Set_Obs(4,5,6,7);
        a.Set_Obs(8,5,6,14);
        a.Set_Obs(9,5,6,21);
        a.Set_Obs(1,2,3,2);
        a.Set_Obs(4,4,5,-5);
        a.Set_Obs(12,13,10,43);
        cout << a.Get_Obs(2,2,2) << endl;
        cout << a.Get_Obs(9,5,6) << endl;
        cout << a.Get_Av_Day(8,5) << endl;
        cout << a.Get_Av_Month(5) << endl;
        cout << a.Get_Av_All() << endl;
        a.To_File("Dict.txt");
        a.From_File("Dict.txt");
        a.To_File("Dict.txt");
        int day,month,hour,year;
        a.Get_Init(day,month,hour,year);
        cout << day<<";"<<month<<";"<<hour<<";"<<year<< ";" << endl;
        return 0;
    }
    catch(string a){
        cout << "Error:" << a << endl;
    }
    catch(bad_alloc& e){
        cout << "Error: Memory overflow" << endl;
    }
    
}

