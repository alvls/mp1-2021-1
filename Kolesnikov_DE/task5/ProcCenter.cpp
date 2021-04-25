#include "ProcCenter.h"
using namespace std;
bool ProcCenter::Read_From_File(string path)
{
    string line;
    ifstream in(path);
    if (in.is_open())
    {
        int buf;
        int i = 0;
        int PrPayrollN = -1;
        //in >> buf;
        //cout << buf << endl;
        getline(in, line);
        istringstream fin(line);
        fin >> buf;
        PersDt = new Data [buf];
        while (getline(in, line))
        {
            istringstream fin(line);
            fin >> PersDt[i].PayrollN;
            fin >> PersDt[i].name;
            fin >> PersDt[i].password;
            fin >> PersDt[i].surname;
            fin >> PersDt[i].middlename;
            fin >> PersDt[i].sum;
            fin >> buf;
            PersDt[i].CrStatus = buf;
            if(buf == 1){
                fin >> PersDt[i].CrInf.day;
                fin >> PersDt[i].CrInf.month;
                fin >> PersDt[i].CrInf.year;
                fin >> PersDt[i].CrInf.Months;
                fin >> PersDt[i].CrInf.MPayment;
                fin >> PersDt[i].CrInf.RMonths;
                fin >> PersDt[i].CrInf.Sum;
            }
            i++;
        }
        DataCnt = i;
    }
    in.close();
    return 0;
}
