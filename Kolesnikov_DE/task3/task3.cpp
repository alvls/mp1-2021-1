#include <fstream>
#include <locale.h>
#include <sstream>
#include <string>
#include <iostream>
#define NUM_OF_TRL 5
#define DEFAULT_DICT_SIZE 20
using namespace std;
class Dict
{
    private:
        struct Dictationary
        {
            string word;
            string* tword;
            int n;
        };
        int len;
        int store = 0;
        Dictationary *mass;
        
        void operator=( const Dict& ) {}
        void operator+( const Dict& ) {}
        void operator-( const Dict& ) {}
    public:
        Dict() : len(DEFAULT_DICT_SIZE)
        {
            mass = new Dictationary [DEFAULT_DICT_SIZE];
            for(int i = 0;i < len;i++){
                mass[i].tword = new string [NUM_OF_TRL];
            }
        }
        Dict(int _len) : len(_len)
        {
            mass = new Dictationary [len];
            for(int i = 0;i < len;i++){
                mass[i].tword = new string [5];
            }
        }
        Dict(const Dict& other) : len(other.len),store(other.store)
        {
            delete [] mass;
            Dictationary* mass = new Dictationary [len];
            for(int i = 0;i < len;i++)
            {
                mass[i].word = other.mass[i].word;
                mass[i].n = other.mass[i].n; 
                for(int k = 0;k < mass[i].n;k++){
                    mass[i].tword[k] = other.mass[i].tword[k];
                }
            }
        }
        ~Dict()
        {
           for(int i = 0;i < len;i++)
            {
                delete [] mass[i].tword;
            }
            delete [] mass;
        }
        string Get_Tr(string wd,int num = 1)
        {
            num--;
            for(int i = 0;i < store;i++){
                if (mass[i].word == wd){
                    if(num > mass[i].n){return "";}
                    return mass[i].tword[num];
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
        int Ch_Tr(string wd,string twd,int num = 1)
        {
             for(int i = 0;i < store;i++){
                if (mass[i].word == wd)
                {
                    if (num > mass[i].n){return -1;}
                    mass[i].tword[num - 1] = twd;
                    return 0;
                }
            }
            mass[store].word = wd;
            mass[store].tword[0] = twd;
            mass[store].n = 1;
            store++;
            return 0;
        }
        int Set_Word(string wd,string twd)
        {
            if(store == (len-1)){return -1;}
             for(int i = 0;i < store;i++){
                if (mass[i].word == wd){
                    mass[i].tword[mass[i].n++] = twd;
                    return 0;
                }
            }
            mass[store].word = wd;
            mass[store].tword[0] = twd;
            mass[store].n = 1;
            store++;
            return 0;
        }
        int Add_Tr(string wd,string twd)
        {
            for(int i = 0;i < store;i++){
                if (mass[i].word == wd){
                    mass[i].tword[mass[i].n++] = twd;
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
                fout << mass[i].word << " - ";
                 for(int k = 0;k < mass[i].n;k++){
                    fout <<" "<< mass[i].tword[k];
                }
                fout << endl;
            }
            fout.close();
            return 0;
        }
        int From_File(string path)
        {
            string buf;
            ifstream fin;
            fin.open(path);
            if(!fin){return -1;}
            else{
                delete [] mass;
                mass = new Dictationary [DEFAULT_DICT_SIZE];
                int i = 0;
                while (!fin.eof()){
                    fin >> mass[i].word>>buf>>mass[i].tword[0];
                    i++;
                }
                fin.close();
                store = len = i-1;
                }
            return 0;
        }
};
int main(){
    setlocale(LC_ALL, "Russian");
try{
    Dict a(20);
    cout << a.Set_Word("Moscow","Рим") << endl;
    cout << a.Set_Word("Moscow","Город") << endl;
    cout << a.Add_Tr("Moscow","Столица") << endl;
    cout << a.Get_Tr("work") << endl;
    cout << a.Set_Word("Constantinople","Рим") << endl;
    cout << a.To_File("Dict.txt") << endl;
    cout << a.From_File("Dict.txt") << endl;
    a.Ch_Tr("Moscow","Москва",3);
    cout << a.Get_Tr("Moscow",3) << endl;
    if(a.Get_Tr("Moscow",4) == ""){
        cout << "ERROOR NO TRANSLATE WITH THIS NUMBER"<< endl;
    }
    cout << a.Get_Len() << endl;
    return 0;
}
catch(const bad_alloc& e){
    cout << "Memory overflow" << endl;
    return 1;
}
}
