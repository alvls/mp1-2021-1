#include "main.h"
#include <iostream>
#include <vector>
int main()
{
    ProcCenter a("Data.txt");
    Credit b(&a);
    cout << b.Authorize(1231,"0932") << endl;
    cout << b.Authorize(1231,"8765") << endl;
    vector <int> CrInfo;
    CrInfo = b.Av_Credit_Info();
    cout << CrInfo.size() << endl;
    //Show Credit Info
    for (int i = 0; i < CrInfo.size(); i+=4)
    {
        cout << CrInfo[i] << endl;
        cout << CrInfo[i+1] << endl;
        cout << CrInfo[i+2] << endl;
        cout << CrInfo[i+3] << endl;
        cout << endl;
    }
    b.Get_Credit(3,120);
    vector <int> CrSt;
    CrSt = b.Credit_Status();
    cout << "Credit Status" << endl;
    for(int i = 0;i < CrSt.size();i++)
    {
        cout << CrSt[i] << endl;
    }
    b.Calc_Credit_Debt_TEST(6,12,2022);
    CrSt = b.Credit_Status();
    for(int i = 0;i < CrSt.size();i++)
    {
        cout << CrSt[i] << endl;
    }
    b.Pay_Credit();
    CrSt = b.Credit_Status();
    for (int i = 0; i < CrSt.size(); i++)
    {
        cout << CrSt[i] << endl;
    }
    return 0;
}
