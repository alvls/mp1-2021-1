include <fstream>
using namespace std;
class Dict
{
    public:
        struct Dictationary
        {
            string *word;
            string *tword;
        }
        int k;
    private:
        Dict()
        {
            k = 0;
            mass = new Dictationary [100];
        }
        ~Dict()
        {
            for(int i = 0;i < k;i++){
                delete [] mass[i].word;
                delete [] mass[i].tword;
                delete [] mass;
            }
        }
        Dict(char *wd)
        {
            k = 1;
            mass = new Dictationary [100];
            mass[0].word = new string [strlen(wd)];
        }
        string Get_Tr(string wd)
        {
            for(int i = 0;i < k;k++){
                if (mass[i].word == wd){
                    return mass[i].tword;
                }
            }
            return -1
        }
        int Len_Dict()
        {
            return k;
        }
        int Is_There()
       {
            for(int i = 0;i < k;i++){
                if (mass[i].word == wd){return 0;}
            }
            return -1;
                
        }
        int Set_Word(string w,string tw)
        {
            if(k+1==max){return -1}
            mass[k+1] = new string[stren(w)];
            mass[k+1] = new string[stren(tw)];
            k++;
        }
        string Ch_Tr(string twd)
        {
            for(int i = 0;i < k;k++){
                if (mass[i].word == wd){
                    delete [] mass[i].tword;
                    mass[i].tword = new string[strlen(twd)];
                    return -1;
                }
            }
            return -1;
        }
        string To_File()
        {
            ofstream fout;
            fout.open("Dict.txt");
            fout << Dictationary << endl;
            for(int i = 0;i < k;i++){
                fout << mass[i].word<<mass[i].tword<<endl;
            }
            fout.close();
            return Dict.txt;
        }
        int ReadFrFile(string path)
        {
            string buf;
            string tbuf;
            ifstream fin(path);
            if(!fin.is_open()){return -1;};
            for(int i = 0;i < k;i++){
                delete [] mass[i].word;
                delete [] mass[i].tword;
                delete [] mass;
            }
            mass = new Dict [100];
            fin >> buf>>tbuf; //read op
        } 

};
