#include <fstream>
#include <locale.h>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;
class Dict
{
    private:
        struct Dictationary
        {
            string word;
            string tword;
        };
        int len;
        int store = 0;
        Dictationary *mass;
    public:
        Dict(): len(100)
        {
            mass = new Dictationary [100];
        }
        Dict(int _len) : len(_len)
        {
            mass = new Dictationary [len];
        }
        Dict(const Dict& other) : len(other.len),store(other.store)
        {
            delete [] mass;
            Dictationary* mass = new Dictationary [len];
            for(int i = 0;i < len;i++)
            {
                mass[i].word = other.mass[i].word;
                mass[i].tword = other.mass[i].tword;
            }
        }
        ~Dict()
        {
            delete [] mass;
        }
        string Get_Tr(string wd)
        {
            for(int i = 0;i < store;i++){
                if (mass[i].word == wd){
                    return mass[i].tword;
                }
            }
            return "1";
        }
        int Get_Len()
        {
            return store;
        }
        int Is_There(string wd)
        {
            for(int i = 0;i < store;i++){
                if (mass[i].word == wd){return 0;}
            }
            return 1;
                
        }
        int Set_Word(string wd,string twd)
        {
            if(store+1 == len){return -1;}
            mass[store].word = wd;
            mass[store].tword = twd;
            store++;
            return 0;
        }
        int Ch_Tr(string wd,string twd)
        {
            for(int i = 0;i < store;store++){
                if (mass[i].word == wd){
                    mass[i].tword = twd;
                    return 0;
                }
            }
            return 1;
        }
        int To_File(string path)
        {
            ofstream fout;
            fout.open(path);
            if(!fout){return -1;}
            for(int i = 0;i < store;i++){
                fout << mass[i].word << " - " << mass[i].tword << endl;
            }
            fout.close();
            return 0;
        }
        int From_File(string path)
        {
            string buf;
            string tempbuf;
            ifstream fin;
            char c;
            fin.open(path);
            if(!fin){return -1;}
            else{
                delete [] mass;
                mass = new Dictationary [len];
                int i = 0;
                while (!fin.eof()){
                    fin >> mass[i].word>>buf>>mass[i].tword;
                    i++;
                }
                fin.close();
                store = len = i;
                }
            return 0;
        }
};
int main(){
    setlocale(LC_ALL, "Russian");
try{
     Dict a(20);
    cout << a.Set_Word("Moscow","Рим") << endl;
    cout << a.Get_Tr("work") << endl;
    cout << a.Set_Word("Constantinople","Рим") << endl;
    cout << a.To_File("Dict.txt") << endl;
    cout << a.From_File("Dict.txt") << endl;
    cout << a.Get_Tr("Moscow") << endl;
    cout << a.Get_Len() << endl;
    return 0;
}
catch(const bad_alloc& e){
    cout << "Memory overflow" << endl;
    return 1;
}
}
