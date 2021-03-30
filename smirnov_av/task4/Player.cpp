#include "Player.h"
using namespace std;

void Player::PrintInConsole()
{
	for (int i = 0; i < songList.size(); i++)
	{
		songList[i].PrintSong();
		cout << endl;
	}
}

void Player::PrintInFile()
{
	ofstream fout;
	string nameFile = "Songs.txt";
	fout.open(nameFile);
	for (int i = 0; i < songList.size(); i++)
	{
		fout << songList[i];
	}
	fout.close();
}

void Player::GetFromFile()
{

}

int Player::GetCountSongs()
{
    return songList.size();
}

void Player::AddSong(string _name, string _poet, string _composer, string _executor, string _album, string _releaseDate)
{
	Song temp(_name,_poet, _composer,_executor,_album,_releaseDate);
	if (songList.size() == 0)
	{
		songList.push_back(temp);
		return;
	}	
	for (int i = 0; i < songList.size(); i++)
	{
		if (_name > songList[i].GetName())
		{
			vector<Song>::const_iterator j = songList.begin(); //const, чтобы нельз€ было изменить какие-то данные
			advance(j, i);
			songList.insert(j, temp);
			return;
		}
	}
	songList.push_back(temp);
}

int Player::FindSong(string _name, string _executor)
{
	for (int i = 0; i < songList.size(); i++)
	{
		if (songList[i].GetName() == _name && songList[i].GetExecutor() == _executor)
			return i;
	}
    return -1;
}

vector<Song> Player::GetSongsByPoet(string _poet)
{
	vector <Song> result;
	for (int i = 0; i < songList.size(); i++)
	{
		if (songList[i].GetPoet() == _poet)
			result.push_back(songList[i]);
	}
	return result;
}

vector<Song> Player::GetSongsByComposer(string _composer)
{
	vector <Song> result;
	for (int i = 0; i < songList.size(); i++)
	{
		if (songList[i].GetComposer() == _composer)
			result.push_back(songList[i]);
	}
	return result;
}

vector<Song> Player::GetSongsByExecutor(string _executor)
{
	vector <Song> result;
	for (int i = 0; i < songList.size(); i++)
	{
		if (songList[i].GetExecutor() == _executor)
			result.push_back(songList[i]);
	}
	return result;
}

void Player::ChangeSongData(int index, string component, string value)
{
	if (component == "name")
	{
		songList[index].SetName(value);
		return;
	}
	else if (component == "poet")
	{
		songList[index].SetPoet(value);
		return;
	}
	else if (component == "composer")
	{
		songList[index].SetComposer(value);
		return;
	}
	else if (component == "executor")
	{
		songList[index].SetExecutor(value);
		return;
	}
	else if (component == "album")
	{
		songList[index].SetAlbum(value);
		return;
	}
	else if (component == "releaseDate")
	{
		songList[index].SetReleaseDate(value);
		return;
	}
	else
	{
		throw "ќшибка выбора составл€ющей песни";
	}
}

void Player::DeleteSong(int index)
{
	songList.erase(songList.begin() + index);
}

