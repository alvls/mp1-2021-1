#include "ProcCenter.h"
bool ProcCenter::Read_From_File(string path)
{
    ifstream fin;
    fin.open(path);
    if(!fin){return false;}
    int i = 0;
    int buf;
    int PrPayrollN;
    fin >> buf;
    PersDt = new Data [buf];
    while(!fin.eof())
    {
        fin >> buf;
        if(buf == PrPayrollN){break;}
        PersDt[i].PayrollN = buf;
        PrPayrollN = buf;
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
           fin >> PersDt[i].CrInf.DMonths;
           fin >> PersDt[i].CrInf.Months;
           fin >> PersDt[i].CrInf.MPayment;
           fin >> PersDt[i].CrInf.RMonths;
           fin >> PersDt[i].CrInf.Sum;
        }
        i++;
    }
    DataCnt = i;
    return true;
    fin.close();
}
