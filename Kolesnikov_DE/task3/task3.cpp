#include <fstream>
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
        int store;
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
            return "0";
        }
        int Len_Dict()
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
            mass[store+1].word = wd;
            mass[store+1].tword = twd;
            store++;
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
        string To_File()
        {
            ofstream fout;
            fout.open("Dict.txt");
            if(!fout){return "0";}
            for(int i = 0;i < store;i++){
                fout << mass[i].word << ' ' << mass[i].tword << endl;
            }
            fout.close();
            return "Dict.txt";
        }
        int Read_Fr_File(string path)
        {
            string buf;
            ifstream fin(path);
            if(!fin){return -1;}
            else{
                delete [] mass;
                int nlen = 0;
                while(getline(fin, buf)){
                    nlen++;
                }
                len = nlen;
                store = nlen;
                mass = new Dictationary [len];
                for(int i = 0;!fin.eof();i++){
                    if(i % 2 == 0){fin >> mass[i/2].word;}  
                    else{fin >> mass[i/2].tword;}
                return 0;
                }
            }
            
        } 
};
