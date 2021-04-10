#include "Credit.h"
bool Credit::Authorize(ProcCenter& pers,int _PayrollN,string _password)
{
    if((_PayrollN == pers.PayrollN)&&(_password == pers.password)){
        AuthPayroll = pers.PayrollN;
        return true;
    }
    else{return false;}
}
