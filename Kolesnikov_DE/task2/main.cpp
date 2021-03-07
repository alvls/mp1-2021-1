#include <iostream>
using namespace std;
class Dynamic_Mass
{
    private:
        double* mass;
        int len;
    public:
    Dynamic_Mass(int n)
    {
        mass =  new double [n];
        for(int i = 0;i++;i < n){
            *(mass + i) = 0;
        }
        len = n;
    }
    ~Dynamic_Mass()
    {
        delete[](mass);
    }
    double& operator[](int ind)
    {   
        //if((ind > len-1) ||ind < 0){}
        return *(mass + ind);  
    }
    Dynamic_Mass& operator=(Dynamic_Mass& massT)
    {
        //if(massT.len != len){};
        for(int i = 0;i < len;i++){
            *(mass + i) = *(massT.mass + i);  
        }
        return *this;
    }
    int IsOrdered()
    {   
        for(int i = 1;i < len;i++){
            if(*(mass + i) > *(mass + i-1)){
                return 0;
            }
        }
        return 1;
    }
    int Get_Lenght()
    {
        return len;
    }
    double Get_Min()
    {
        double t = *mass;
        for(int i = 1;i++;i < len){
            cout <<*(mass + i); 
            if(*(mass + i) < t)
                t = *(mass + i);
        }
        return t;
    }
    int Cr_OddMass()
    {
        double *massOdd;
        int Oddlen = len/2;
        massOdd =  new double [Oddlen];
        if (!massOdd){return -1;}
        for(int i = 0;i < len;i++){
            *(massOdd + i) = *(mass + i + 1);        
        }
        double* t = mass;
        mass = massOdd;
        delete[](t);
        return 0;
    }
};


int main()
{
    Dynamic_Mass a(5);
    a[4] = 4;
    Dynamic_Mass b(5);
    b = a;
    cout << a[4] << endl;
    cout << a.Get_Lenght();
    cout << a.Get_Min();
}
