#pragma once
#include "Song.h"
#include <vector>
#include <fstream>

using namespace std;

class Player
{
private:
	vector <Song> songList;
public:
	Player()
	{
		songList.resize(0);
	}
	Player(int count)
	{
		songList.resize(count);
	}
	~Player()
	{

	}

	void AddSong(string _name = "unknown", string _poet = "unknown", string _composer = "unknown", string _executor = "unknown", string _album = "unknown", string _releaseDate = "unknown");
	Song FindSong(string _name, string _executor);
	int FindIndSong(string _name, string _executor);
	vector<Song> GetSongsByPoet(string _poet);
	vector<Song> GetSongsByComposer(string _composer);
	vector<Song> GetSongsByExecutor(string _executor);
	void ChangeSongData(Song& changingSong, string component, string value); //component - тип изменения name/poet/executor...
	//удаляет песню с указанным индексом
	void DeleteSong(int index);
	//удаляет указанную песню
	void DeleteSong(Song& _song);
	void PrintInConsole();
	void PrintInFile();
	void GetFromFile();
	int GetCountSongs();
	int GetCountSongsInFile(); //большое название у функции, но как сократить, не теряя смысла, не знаю
	

};

