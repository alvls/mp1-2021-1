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
	int n, dynl, inhour,year;
	Data* mass;
    int CntOfR[12] = {0};

	void operator= (const Termo&){};
    void MemoryAllocator()
    {
        Data* nmass = new Data[dynl*2];
        for(int i = 0;i < dynl;i++){
            nmass[i].day = mass[i].day;
            nmass[i].month = mass[i].month;
            nmass[i].datacode = mass[i].datacode;
            for(int k=0;k<24;k++){
                nmass[i].temp[k] = mass[i].temp[k];
            }
        }
        delete [] mass;
        mass = nmass;
        dynl*=2;
    }
    void QSort()
    {
    int i = 0;
    int j = n;
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
    if (j > 0){
        QSort();
    }
    if (i < n){
        QSort();
    }
    }

public:
	Termo() : n(0),dynl(NUMOFINDATES)
	{
		mass = new Data[NUMOFINDATES];

	}
	Termo(int _day, int _month, int _hour,int _year) : n(1),dynl(NUMOFINDATES)
	{
		mass = new Data[NUMOFINDATES];
		mass[0].day = _day;
		mass[0].month = _month;
		mass[0].temp = new double[24 - _hour];
        year = _year;
		inhour = _hour;
	}
	~Termo()
    {
        for(int i = 0;i < n;i++){
            delete [] mass[i].temp;
        }
        delete [] mass;
    }
    Termo(const Termo& other)
    {
        n = other.n;
        dynl = other.dynl;
        inhour = other.inhour;
        year = other.year;
        mass = new Data [dynl];
        for(int i = 0;i < n;i++){
            mass[i].day = other.mass[i].day;
            mass[i].month = other.mass[i].month;
            mass[i].datacode = other.mass[i].datacode;
            for(int z = 0;z < other.n;z++){
                mass[i].temp[z]=  other.mass[i].temp[z];
            }
        }
    }
    bool Set_In(int _day, int _month, int _hour,int _year)
	{
        if(n){return false;}
		mass[0].day = _day;
		mass[0].month = _month;
		mass[0].temp = new double [24 - _hour];
		inhour = _hour;
        year = _year;
        mass[0].datacode = _day + _month * 100;
        return true;
	}
	void Get_Init(int& _day, int& _month, int& _hour,int& _year)
	{
		_day = mass[0].day;
		_month = mass[0].month;
		_hour = inhour;
        _year = year;
	}
	bool Set_Obs(int _day, int _month, int _hour, double _temp)
	{
		if (!n) { return false; }
		if ((_day > 31) || (_month > 12)) { return false; }
        if(n==dynl){MemoryAllocator();}
		mass[n].temp = new double[24];
		for (int i = 0; i < 24; i++) {
			mass[n].temp[i] = 255.0;
		}
		CntOfR[_month-1]++;
		mass[n].temp[_hour] = _temp;
		mass[n].day = _day;
		mass[n].month = _month;
		mass[n].datacode = _day + _month * 100; 
		n++;
        QSort();
		return true;
	}
	double Get_Obs(int _day, int _month, int _hour)
	{
		if (!n) { return -1; }
		if ((_day > 31) || (_month > 12)) { return false; }
		int k = 0;
		for (int i = 0; i < _month; i++) {
			k += CntOfR[i];
		}
		for (k++; k < CntOfR[_month]; k++) {
			if ((mass[k].day == _day) && (mass[k].temp[_hour] < 250.0)) {
				return mass[k].temp[_hour];
			}
		}
    }
	bool Set_Obs_Serial(int _day, int _month, int _shour, int _ehour, double _temp[])
	{
        if(n==dynl){MemoryAllocator();}
		if ((_day > 31) || (_month > 12)) { return false; }
		mass[n].temp = new double[24];
		for (int i = _shour - 1; i < _ehour; i++) {
			mass[n].temp[i] = _temp[i + 1 - _shour];
		}
		mass[n].day = _day;
		mass[n].month = _month;
        CntOfR[_month-1]++;
		n++;
        QSort();
        return true;
	}
	bool To_File(string path)
	{
		ofstream fout;
		fout.open(path);
		if (!fout) { return -1; }
		fout << year << " " << n << " " << inhour<<endl;
		for (int i = 0; i < n; i++) {
			for (int k = 0; k < 24; k++) {
				if (mass[i].temp[k] < 250.0) {
					fout << mass[i].day << " " << mass[i].month << " " << k << " " << mass[i].temp[k] << endl;
				}
			}
		}
		fout.close();
		return 0;
	}
    double Get_Av_Day(int _day,int _month)
    {
        int k = 0;
		for (int i = 0; i < _month; i++) {
			k += CntOfR[i];
		}
		for (; k < CntOfR[_month]; k++) {
			if (mass[k].day == _day) {
                double av = 0.0;
                double r = 0.0;
                for(int z = 0;z < 24;z++){
                    if(mass[k].temp[z] < 250.0)
                    {
                        r++;
                        av += mass[k].temp[z];
                    }
                }
				return av/r;
			}
		}
    }
    double Get_Av_Month(int _month)
    {
        int k = 0;
		for (int i = 0; i < _month; i++) {
			k += CntOfR[i];
		}
        double av = 0.0;
        double r = 0.0;
		for (int k = 0; k < CntOfR[_month]; k++) {
            for(int z = 0;z < 24;z++){
                if(mass[k].temp[z] < 250.0)
                {
                    r++;
                    av+=mass[k].temp[z];
                }
				return av/r;
			}
		}
    }
    double Get_Av_All()
    {
        double av = 0.0;
        int r = 0;
		for (int k = 0; k < n; k++) {
            for(int z = 0;z < 24;z++){
                if(mass[k].temp[z] < 250.0)
                {
                    r++;
                    av+=mass[k].temp[z];
                }
				return av/k;
			}
		}
    }
	int From_File(string path)
	{
		int buf;
        int day,month;
        int olday,olmonth;
		ifstream fin;
		fin.open(path);
		if (!fin) { return -1; }
		else {
        //clean
        delete[] mass;
        for (int i = 0; i < 12; i++) {
            CntOfR[i] = 0;
        }
        fin >> year >> n >> inhour;
        mass = new Data[n];
        int i = 0;
        while (!fin.eof()) {
            fin >> day >> month;
            if ((day!=olday)&&(month!=olmonth)){
                i++;
            }
            else{
                olday = day;
                olmonth = month;
            }
            mass[i].day = day;
            mass[i].month = month;
            mass[i].datacode = day + 100*month;
            CntOfR[month]++;
            fin >> buf;
            fin >> mass[i].temp[buf];
            fin.close();
            }
        return 0;
        }
        dynl = n;
        QSort();
    }
};
int main() {
	return 0;
}

