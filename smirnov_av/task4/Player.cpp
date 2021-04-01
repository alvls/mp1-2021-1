#include "Player.h"

using namespace std;

void Player::DeleteSong(Song& _song)
{
	int index = FindIndSong(_song.GetName(),_song.GetExecutor());
	DeleteSong(index);
}

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
	if (fout.is_open())
	{
		for (int i = 0; i < songList.size(); i++)
		{
			fout << songList[i];
		}
	}
	else
		throw string("ќшибка открыти¤ файла!");
	fout.close();
}

void Player::GetFromFile()
{
	
	ifstream fin;
	string nameFile = "Songs.txt";
	fin.open(nameFile);
	int size = this->GetCountSongsInFile();
	if (fin.is_open())
	{
		Song temp;
		while (fin.eof()) //вместо этого можно использовать !size и убрать проверку на size == 0 ниже
		{
			if (size == 0) //из-за того, что печатаю пустую строку через endl, чтобы раздел¤ть песни в файле, getline считывало \n, и eof не наступало, из-за чего создавалс¤ лишний объект
				break;
			fin >> temp;
			songList.push_back(temp);
			size--;
		}
		fin.close();
	}
	else
		throw string("ќшибка открыти¤ файла!");
	
}

int Player::GetCountSongs()
{
    return songList.size();
}

int Player::GetCountSongsInFile()
{
	ifstream fin;
	string nameFile = "Songs.txt";
	fin.open(nameFile);
	int result = 0;
	string temp;
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			getline(fin, temp);
			if (temp == "Ќазвание: ")
				result++;
		}
	}
	else
		throw string("ќшибка открыти¤ файла!");
	return result;
}

void Player::AddSong(string _name, string _poet, string _composer, string _executor, string _album, string _releaseDate)
{
	Song temp(_name,_poet, _composer,_executor,_album,_releaseDate);
	if (songList.empty())
	{
		songList.push_back(temp);
		return;
	}	
	for (int i = 0; i < songList.size(); i++)
	{
		if (_name < songList[i].GetName())
		{
			vector<Song>::const_iterator j = songList.begin(); //const, чтобы нельз¤ было изменить какие-то данные через *j
			advance(j, i);
			songList.insert(j, temp);
			return;
		}
	}
	songList.push_back(temp);
}

Song Player::FindSong(string _name, string _executor)
{
	return songList[this->FindIndSong(_name, _executor)];
}

int Player::FindIndSong(string _name, string _executor)
{
	for (int i = 0; i < songList.size(); i++)
	{
		if (songList[i].GetName() == _name && songList[i].GetExecutor() == _executor)
			return i;
	}
	throw string("ѕесн¤ не найдена!");
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

void Player::ChangeSongData(Song& changingSong, string component, string newValue)
{
	int index = FindIndSong(changingSong.GetName(),changingSong.GetExecutor());
	if (component == "name")
	{
		songList[index].SetName(newValue);
		return;
	}
	else if (component == "poet")
	{
		songList[index].SetPoet(newValue);
		return;
	}
	else if (component == "composer")
	{
		songList[index].SetComposer(newValue);
		return;
	}
	else if (component == "executor")
	{
		songList[index].SetExecutor(newValue);
		return;
	}
	else if (component == "album")
	{
		songList[index].SetAlbum(newValue);
		return;
	}
	else if (component == "releaseDate")
	{
		songList[index].SetReleaseDate(newValue);
		return;
	}
	else
	{
		throw string("ќшибка выбора составл¤ющей песни");
	}
}

void Player::DeleteSong(int index)
{
	songList.erase(songList.begin() + index);
}

