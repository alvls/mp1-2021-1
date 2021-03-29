#pragma once
#include <iostream>
#include <string.h>
using namespace std;
/*Разработать класс Песенник.
Класс должен хранить информацию о песенных композициях. Каждая песня описывается следующими данными: название, поэт (автор стихов), композитор (автор музыки),
исполнитель, название альбома (если входит в какой-то альбом), дата выпуска (день, месяц, год).
Песни хранятся упорядоченно по названию. Данные вводятся на русском языке.
Класс должен содержать необходимые служебные методы.
Класс должен предоставлять следующие операции: 1) добавить песню, 2) изменить данные выбранной песни, 3) найти песню по названию и исполнителю,
4) выдать все песни заданного поэта, 5) выдать все песни заданного композитора, 6) выдать все песни заданного исполнителя, 7) узнать текущее число песен,
8) удалить песню, 9) сохранить песенник в файл, 10) считать песенник из файла.
*/
class Song
{
private:
	string name; // имя
	string poet; // автор текста
	string composer; //композитор
	string executor; // исполнитель
	string album; //альбом
	string releaseDate; //дата выхода
public:
	Song(string _name = "unknown", string _poet = "unknown", string _composer = "unknown", string _executor = "unknown", string _album = "unknown", string _releaseDate = "unknown") :
		name(_name), poet(_poet), composer(_composer), executor(_executor), album(_album), releaseDate(_releaseDate)
	{

	}
	//setters 
	void SetName(string _name);
	void SetPoet(string _poet);
	void SetComposer(string _composer);
	void SetExecutor(string _executor);
	void SetAlbum(string _album);
	void SetReleaseDate(string _releaseDate);

	//getters
	string GetName();
	string GetPoet();
	string GetComposer();
	string GetExecutor();
	string GetAlbum();
	string GetReleaseDate();

	//functions
	void PrintSong();
};

