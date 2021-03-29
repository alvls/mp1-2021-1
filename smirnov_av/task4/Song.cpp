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



