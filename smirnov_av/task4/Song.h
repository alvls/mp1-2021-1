#pragma once
#include <iostream>
#include <string.h>
#include <string>

using namespace std;

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
	friend ostream& operator<<(ostream& os, const Song& song);
	friend istream& operator>>(istream& in, Song& song);
};

