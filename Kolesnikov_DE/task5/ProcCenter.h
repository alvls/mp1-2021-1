#include <string>
using namespace std;
class ProcCenter
{
    private:
        int PayrollN;
        string password;
        string name;
        string surname;
        string middlename;
        int sum;
        //CrInfo
        int time;
        int SumCr;
        int percent;
        bool isCredit;
        friend class Credit;
        void operator=(const ProcCenter&);
    public:
        ProcCenter(int _PayrollN = 0,string _password = "null",int _sum = 0,string _name = "null",
                string _middlename = "null",string _surname = "null")
        {
            PayrollN = _PayrollN;
            password = _password;
            name = _name;
            surname = _surname;
            middlename = _middlename;
            sum = _sum;
            isCredit = false;
        }
        void Set_Person(int _PayrollN,string _password)
        {
            PayrollN = _PayrollN;
            password = _password;
        }
        void Set_name(string _name)
        {
            name = _name;
        }
        void Set_surname(int _PayrollN,string _surname)
        {
            surname = _surname;
        }
        void Set_middlename(int _PayrollN,string _middlename)
        {
            middlename = _middlename;
        }
        void Set_sum(int _PayrollN,int _sum)
        {
            sum = _sum;
        }
};
