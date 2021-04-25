#include "Credit.h"

//annuity payment
//month payment = S*(P+P/((1+P)^N-1)) S = sum,P = percent/100,N = number of months
Credit::Credit(ProcCenter* _data): AuthPersNumb(-1)
{
    data = _data;
}
void Credit::Get_Current_Date(int* day,int* month,int* year)
{
    time_t t = std::time(0);   // get time now
    tm* now = std::localtime(&t);
    *year = now->tm_year + 1900; 
    *month = now->tm_mon + 1;
    *day = now->tm_mday;
}
void Credit::Calc_Credit_Debt(){
    int day;
    int month;
    int year;
    Get_Current_Date(&day,&month,&year);
    int range = (year*12+month)-
    (data->PersDt[AuthPersNumb].CrInf.year*12+ 
    data->PersDt[AuthPersNumb].CrInf.month);
    if(day < data->PersDt[AuthPersNumb].CrInf.day){
        range--;
    }
    data->PersDt[AuthPersNumb].CrInf.DMonths += range - 
    (data->PersDt[AuthPersNumb].CrInf.Months-
    data->PersDt[AuthPersNumb].CrInf.RMonths);
}
void Credit::Clear_Credit()
{ 
    data->PersDt[AuthPersNumb].CrStatus = false;
    data->PersDt[AuthPersNumb].CrInf.MPayment  = 0;
    data->PersDt[AuthPersNumb].CrInf.DMonths= 0;
    data->PersDt[AuthPersNumb].CrInf.RMonths  = 0;
    data->PersDt[AuthPersNumb].CrInf.day  = 0;
    data->PersDt[AuthPersNumb].CrInf.month  = 0;
    data->PersDt[AuthPersNumb].CrInf.year  = 0;
    data->PersDt[AuthPersNumb].CrInf.Months= 0;
    data->PersDt[AuthPersNumb].CrInf.Sum = 0;

}
bool Credit::Authorize(int _PayrollN,string _password) 
{
    for(int i = 0;i < data->DataCnt;i++)
    {
        if(data->PersDt[i].PayrollN == _PayrollN){
            AuthPersNumb = i;
            CheckAvCredits = false;
            Calc_Credit_Debt();
            return true;
        }
    }
    return false;
            
}
vector<int> Credit::Av_Credit_Info()
{   
    if(AuthPersNumb == -1){throw No_Person_Authorize;}
    CheckAvCredits = true;
    int Mnth_Sum = (data->PersDt[AuthPersNumb].sum)/6;
    vector <int> avcredits;
    if (Mnth_Sum == 0){
        return avcredits;
    };
    int Cnt_Of_Dates = sizeof(CrDates)/(sizeof(int));
    int Cnt_Of_Credits = sizeof(CrPerc)/(sizeof(int));
    int Cnt_Of_Sum_Ran = Cnt_Of_Credits/Cnt_Of_Dates;
    double perc;
    CreditPers = new int [Cnt_Of_Credits];
    for (int i = 0; i < Cnt_Of_Credits;i++)
    {
        perc = CrPerc[i] / 100/12;
        int nmonths = CrDates[i % Cnt_Of_Dates]*12;
        int Calc_Sum = Mnth_Sum/(perc + (perc)/(pow((1 + perc),nmonths)) - 1);
        if(Calc_Sum >= SumRan[i/Cnt_Of_Sum_Ran]){
            avcredits.push_back(SumRan[i/Cnt_Of_Sum_Ran]);
            if(Calc_Sum >= SumRan[i/Cnt_Of_Sum_Ran + 1]){
                avcredits.push_back(SumRan[i/Cnt_Of_Sum_Ran +1]);
                CreditPers[i] = SumRan[i/Cnt_Of_Sum_Ran +1];
            }
            else{
                avcredits.push_back(Calc_Sum);
                CreditPers[i] = Calc_Sum;
            }
            avcredits.push_back(CrPerc[i]);
            avcredits.push_back(nmonths);
        }
        else{
            CreditPers[i] = 0;
        }
    }
    return avcredits;
}
bool Credit::Is_Av_Credit(int n,int sum)
{
    
    if(AuthPersNumb == -1){throw No_Person_Authorize;}
    if(CheckAvCredits == false){throw No_Check_Av_Cr;}
    int Cnt_Of_Dates = sizeof(CrDates)/(sizeof(int));
    int Cnt_Of_Credits = sizeof(CrPerc)/(sizeof(int));
    int Cnt_Of_Sum_Ran = Cnt_Of_Credits/Cnt_Of_Dates;
    int k = 0;
    for(int i = 0;  i < Cnt_Of_Credits; i ++){
        if(CreditPers[i] > 0){
            if(k == n){
                if((sum >= SumRan[i/Cnt_Of_Sum_Ran]) && (sum <= CreditPers[i]))
                    return true;
            }
            else
                k++;
        }
    }
    return false;
}
bool Credit::Get_Credit(int n,int sum)
{
    
    if(AuthPersNumb == -1){throw No_Person_Authorize;}
    if(CheckAvCredits == false){throw No_Check_Av_Cr;}
    if(data->PersDt[AuthPersNumb].CrStatus){throw Already_Have_Credit;}
    int Cnt_Of_Dates = sizeof(CrDates)/(sizeof(int));
    int Cnt_Of_Credits = sizeof(CrPerc)/(sizeof(int));
    int Cnt_Of_Sum_Ran = Cnt_Of_Credits/Cnt_Of_Dates;
    int k = 0;
    for(int i = 0; i < Cnt_Of_Credits; i ++){
        if(CreditPers[i] > 0){
            if(k == n){
                if((sum >= SumRan[i/Cnt_Of_Sum_Ran]) && (sum <= CreditPers[i])){
                    int day,month,year;
                    int months = (CrDates[i % Cnt_Of_Dates]*12); 
                    int perc = CrPerc[i]/1200;
                    data->PersDt[AuthPersNumb].CrStatus = true;
                    data->PersDt[AuthPersNumb].CrInf.Sum = sum;
                    data->PersDt[AuthPersNumb].CrInf.RMonths = months;
                    data->PersDt[AuthPersNumb].CrInf.Months = months;
                    data->PersDt[AuthPersNumb].CrInf.MPayment =
                        (sum *(perc + perc/(pow((1+perc),months)-1)));
                    Get_Current_Date(&day,&month,&year);
                    data->PersDt[AuthPersNumb].CrInf.day = day;
                    data->PersDt[AuthPersNumb].CrInf.month = month;
                    data->PersDt[AuthPersNumb].CrInf.year = year;
                    data->PersDt[AuthPersNumb].CrInf.DMonths = 0;
                    return true;
                }
            }
            else
                k++;
        }
    }
    return false;
}
bool Credit::Pay_Credit()
{
    if(AuthPersNumb == -1){throw No_Person_Authorize;}
    Calc_Credit_Debt();
    if(data->PersDt[AuthPersNumb].CrStatus){
        if(data->PersDt[AuthPersNumb].sum - (data->PersDt[AuthPersNumb].CrInf.DMonths * 
                data->PersDt[AuthPersNumb].CrInf.MPayment)>0){
            data->PersDt[AuthPersNumb].sum -= (data->PersDt[AuthPersNumb].CrInf.DMonths * 
                data->PersDt[AuthPersNumb].CrInf.MPayment);
            data->PersDt[AuthPersNumb].CrInf.RMonths-=
                data->PersDt[AuthPersNumb].CrInf.DMonths;
            if(data->PersDt[AuthPersNumb].CrInf.RMonths == 0){
                Clear_Credit();
            }
                data->PersDt[AuthPersNumb].CrInf.DMonths = 0;
        }
        else 
            throw Not_Enough_Cash;

    }
    throw No_Active_Cr;
}
bool Credit::Pay_Credit_Early()
{
    if(AuthPersNumb == -1){throw No_Person_Authorize;}
    Calc_Credit_Debt();
    if(data->PersDt[AuthPersNumb].CrStatus){
        if(data->PersDt[AuthPersNumb].sum - (data->PersDt[AuthPersNumb].CrInf.RMonths * 
                data->PersDt[AuthPersNumb].CrInf.MPayment)>0){
            data->PersDt[AuthPersNumb].sum -= (data->PersDt[AuthPersNumb].CrInf.RMonths * 
            data->PersDt[AuthPersNumb].CrInf.MPayment);
            Clear_Credit();
            }
            throw Not_Enough_Cash;
    }
    throw No_Active_Cr;
}
vector<int> Credit::Credit_Status(){
    if(AuthPersNumb == -1){throw No_Person_Authorize;}
    if(data->PersDt[AuthPersNumb].CrStatus){
        vector <int> CrInf;
        CrInf.push_back(data->PersDt[AuthPersNumb].CrInf.day);
        CrInf.push_back(data->PersDt[AuthPersNumb].CrInf.month);
        CrInf.push_back(data->PersDt[AuthPersNumb].CrInf.year);
        CrInf.push_back(data->PersDt[AuthPersNumb].CrInf.Months);
        CrInf.push_back(data->PersDt[AuthPersNumb].CrInf.DMonths);
        CrInf.push_back(data->PersDt[AuthPersNumb].CrInf.MPayment);
        CrInf.push_back(data->PersDt[AuthPersNumb].CrInf.RMonths);
        CrInf.push_back(data->PersDt[AuthPersNumb].CrInf.Sum);
        return CrInf;
    }
    throw No_Active_Cr;
}
