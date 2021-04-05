#include <string.h>
using namespace std;
#define NumOfInPers;
class ProcCenter
{
    private:
        struct Person
        {
            int PayrollN;
            string password;
            string name;
            string surname;
            string middlename;
            int sum;
            //CrInfo
            int time;
            int sumcr;
        }
        int n;
        Person* mass;
        friend class Credit;
        void operator=(const ProcessingCenter&);
        int SearchPers(int _PayrollN)
        {
            for(int i = 0;i < n;i++)
            {
                if(mass[i].PayrollN = _PayrollN)
                    return i
            }
            return -1;
        }
    public:
        ProcCenter()
        {
            mass = new Person[NumOfInPers];
            n = 0;
        }
        ProcCenter(int _PayrollN,string _password,string _name,string _middlename,
                int _sum)
        {
            mass[0].PayrollN = _PayrollN;
            mass[0].password = _password;
            mass[0].name = _name;
            mass[0].surname = _surname;
            mass[0].middlename = _middlename;
            mass[0].sum = _sum;
            n = 1;
        }
        void Set_Person(int _PayrollN,string _password)
        {
            mass[n].PayrollN = _PayrollN;
            mass[n].password = _password;
            n++;
        }
        void Set_Name(int _PayrollN,string _name)
        {
            int ind = SearchP(_PayrollN);
            if(ind != -1){
                mass[ind].name = _name;
                return 0;
            }
            else
                return 1;
        }
        int Set_MiddleName(int _PayrollN,string _middlename);
        {
            int ind = SearchP(_PayrollN);
            if(ind != -1){
                mass[ind].middlename = _middlename;
                return 0;
            }
            else 
                return 1;
        }
        int Set_Surname(int _PayrollN,string _surname);
        {
            int ind = SearchP(_PayrollN);
            if(ind != -1){
                mass[ind].surname = _surname;
                return 0;
            }
            else 
                return 1;
        }
        int Set_Sum(int _PayrollN,int _sum);
        {
            int ind = SearchP(_PayrollN);
            if(ind != -1){
                mass[ind].sum = _sum;
                return 0;
            }
            else 
                return 1;
        }
};
class Credit
{
    private:
        int CrDates[5] = {1,2,3,5,15};
        int SumRan[4] = {1,5,10,30};
        int CrPerc[25]={10,12,14,16,18,8,10,12,14,16,
            6,8,10,12,14,7,8,9,10,12}
        int AuthPayroll;
    public:
        Credit()
        {
            AuthPayroll = 0;
        }
        Credit(ProcCenter& pers)
        {
            Authpayroll = pers.PayrollN;
        }
        bool Authorize(ProcCenter& pers,int _PayrollN,int _password;)
        {
            if((_Payroll == pers.PayrollN)&&(_password == pers.password)){
                Authpayroll = pers.PayrollN;
                return true;
            }
            else{return false;}
        }

