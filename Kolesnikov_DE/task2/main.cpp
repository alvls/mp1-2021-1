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
        for(int i = 0;i < n;i++){
            mass[i] = 0;
        }
        len = n;
    }
    ~Dynamic_Mass()
    {
        delete[] mass;
    }
    double& operator[](int ind)
    {   
        return mass[ind];  
    }
    Dynamic_Mass& operator=(const Dynamic_Mass& massT)
    {
        len = massT.len;
        delete [] mass;
        mass =  new double [len];
        for(int i = 0;i < len;i++){
            mass[i] = massT.mass[i];
        }
        return *this;
    }
    bool Is_Ordered()
    {   
        for(int i = 1;i < len;i++){
            if(mass[i] < mass[i-1]){
                return false;
            }
        }
        return true;
    }
    int Get_Length()
    {
        return len;
    }
    double Get_Min()
    {
        double t = *mass;
        for(int i = 1;i < len;i++){
            if(mass[i] < t){t = mass[i];}
        }
        return t;
    }
    double* Cr_OddMass()
    {
        double *massOdd;
        int Oddlen = len/2;
        massOdd =  new double [Oddlen];
        for(int i = 0;i < len;i++){
            massOdd[i] = mass[i+1];        
        }
        return massOdd;
    }
};


int main()
{
    Dynamic_Mass a(5);
    a[1] = 4;
    Dynamic_Mass b(5);
    b = a;
    cout << a[1] << endl;
    cout << a.Get_Length() <<endl;
    cout << a.Get_Min() << endl;
    double *c;
    c = a.Cr_OddMass();
    cout << c[0]<<endl;
    cout << a[1] <<endl;
}
