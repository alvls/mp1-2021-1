#pragma once
#include <string>
#include "ProcCenter.h"
using namespace std;
class Credit
{
    private:
        int CrDates[5] = {1,2,3,5,15};
        int SumRan[4] = {1,5,10,30}; 
        int CrPerc[25]={10,12,14,16,18,8,10,12,14,16,
            6,8,10,12,14,7,8,9,10,12};
        int AuthPayroll;    
    public:  
        Credit()
        {AuthPayroll = 0;}
        Credit(ProcCenter& pers)
        {AuthPayroll = pers.PayrollN;}
        bool Authorize(ProcCenter& pers,int _PayrollN,string _password);
};

