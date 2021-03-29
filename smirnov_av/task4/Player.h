#pragma once
#include "Song.h"
#include <vector>
#include <fstream>
/*Разработать класс Песенник.
Класс должен хранить информацию о песенных композициях. Каждая песня описывается следующими данными: название, поэт (автор стихов), композитор (автор музыки),
исполнитель, название альбома (если входит в какой-то альбом), дата выпуска (день, месяц, год).
Песни хранятся упорядоченно по названию. Данные вводятся на русском языке.
Класс должен содержать необходимые служебные методы.
Класс должен предоставлять следующие операции: 1) добавить песню, 2) изменить данные выбранной песни, 3) найти песню по названию и исполнителю,
4) выдать все песни заданного поэта, 5) выдать все песни заданного композитора, 6) выдать все песни заданного исполнителя, 7) узнать текущее число песен,
8) удалить песню, 9) сохранить песенник в файл, 10) считать песенник из файла.
*/
using namespace std;
class Player
{
private:
	vector <Song> songList;
public:
	void AddSong(string _name = "unknown", string _poet = "unknown", string _composer = "unknown", string _executor = "unknown", string _album = "unknown", string _releaseDate = "unknown");
	int FindSong(string _name, string _executor);
	vector<Song> GetSongsByPoet(string _poet);
	vector<Song> GetSongsByComposer(string _composer);
	vector<Song> GetSongsByExecutor(string _executor);
	void ChangeSongData(int index,string component, string value); //component - тип изменения name/poet/executor...
	void DeleteSong(int index);
	void PrintInConsole();
	void PrintInFile();
	void GetFromFile();
	int GetCountSongs();

};

