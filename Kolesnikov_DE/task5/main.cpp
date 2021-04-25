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
    b.Credit_Status();
    return 0;
}
