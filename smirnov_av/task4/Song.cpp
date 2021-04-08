#include "Song.h"

void Song::SetName(string _name)
{
	name = _name;
}

void Song::SetPoet(string _poet)
{
	poet = _poet;
}

void Song::SetComposer(string _composer)
{
	composer = _composer;
}

void Song::SetExecutor(string _executor)
{
	executor = _executor;
}

void Song::SetAlbum(string _album)
{
	album = _album;
}

void Song::SetReleaseDate(string _releaseDate)
{
	releaseDate = _releaseDate;
}

string Song::GetName()
{
	return name;
}

string Song::GetPoet()
{
	return poet;
}

string Song::GetComposer()
{
	return composer;
}

string Song::GetExecutor()
{
	return executor;
}

string Song::GetAlbum()
{
	return album;
}

string Song::GetReleaseDate()
{
	return releaseDate;
}

void Song::PrintSong()
{
	cout << "Название: "<< name << endl;
	cout << "Автор текста: " << poet << endl;
	cout << "Композитор: " << composer << endl;
	cout << "Исполнитель: " << executor << endl;
	cout << "Альбом: " << album << endl;
	cout << "Дата выхода: " << releaseDate << endl;
}

ostream& operator<<(ostream& os, const Song& song)
{
	os << "Название: " << endl;
	os <<song.name << endl;
	os << "Автор текста: " << endl;
	os << song.poet << endl;
	os << "Композитор: " << endl;
	os << song.composer << endl;
	os << "Исполнитель: " << endl;
	os << song.executor << endl;
	os << "Альбом: " << endl;
	os << song.album << endl;
	os << "Дата выхода: " << endl;
	os << song.releaseDate << endl;
	os << " " << endl;
	return os;
}

istream& operator>>(istream& in, Song& song)
{
	string temp;
	for (int i = 0; i < 12; i++)
	{
		getline(in, temp);
		switch (i)
		{
		case 1:
			song.name = temp;
			break;
		case 3:
			song.poet = temp;
			break;
		case 5:
			song.composer = temp;
			break;
		case 7:
			song.executor = temp;
			break;
		case 9:
			song.album = temp;
			break;
		case 11:
			song.releaseDate = temp;
			break;
		}
	}
	getline(in, temp);
	return in;
}

