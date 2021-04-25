#pragma once
#include <string>
#include <cmath>
#include "ProcCenter.h"
#include <vector>
#include <ctime>
#include <iostream>
//annuity payment
//month payment = S*(P+P/((1+P)^N-1)) S = sum,P = percent/100,N = number of months             
using namespace std;
enum Errors{
    No_Person_Authorize,
    No_Check_Av_Cr,
    No_Active_Cr,
    Already_Have_Credit,
    Not_Enough_Cash
};
class Credit
{
    private:
        const int CrDates[5] = {1,2,3,5,15};
        const int SumRan[4] = {100,500,1000,30000}; 
        const double CrPerc[15]={14,12,10,8,6,16,14,12,10,8,
            18,16,14,12,10};

        ProcCenter*  data;
        int AuthPersNumb;
        int* CreditPers;
        bool CheckAvCredits;
        void Get_Current_Date(int* day,int* month,int* year);
        void Clear_Credit();
        void Calc_Credit_Debt();
        Credit() = default;
    public:  
        ~Credit(){delete [] CreditPers;}
        Credit(ProcCenter* _data);
        bool Authorize(int _PayrollN,string _password);
        vector<int>  Av_Credit_Info();
        bool Is_Av_Credit(int n,int sum);
        bool Get_Credit(int n,int sum);
        vector <int> Credit_Status();
        bool Pay_Credit();
        bool Pay_Credit_Early();
};


