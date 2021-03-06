﻿#include "Player.h"
#include "Song.h"

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

void main()
{
	setlocale(LC_ALL, "ru");
	Player a;
	Player b;
	Song temp;
	a.AddSong("Имя1", "Автор текста1", "Композитор1", "Исполнитель1", "Альбом1", "Дата Релиза1");
	a.AddSong("Имя2", "Автор текста1", "Композитор2", "Исполнитель2", "Альбом2", "Дата Релиза2");
	a.AddSong("Имя3", "Автор текста2", "Композитор2", "Исполнитель3", "Альбом3", "Дата Релиза3");
	a.AddSong("Имя4", "Автор текста4", "Композитор4", "Исполнитель1", "Альбом3", "Дата Релиза3");
	cout << "Песенник до изменений:" << endl;
	a.PrintInConsole();
	cout << "Текущее число песен = " << a.GetCountSongs() << endl;
	cout << "\n";
	cout << "Изменим название песни имя1 на Армагеддон" << endl;
	a.ChangeSongData(a.FindSong("Имя1", "Исполнитель1"), "name", "Армагеддон");
	cout << "Песня c именем1 после изменений:" << endl;
	temp = a.FindSong("Армагеддон", "Исполнитель1");
	temp.PrintSong();
	cout << "\n";
	cout << "Все песни Исполнителя 1:" << endl;
	vector<Song> songsByExecutor= a.GetSongsByExecutor("Исполнитель1");
	for (size_t i = 0; i < songsByExecutor.size(); i++)
	{
		songsByExecutor[i].PrintSong();
		cout << "\n";
	}
	cout << "Удалим песню с именем \"Имя3\", но перед этим запишем наши данные в файл" << endl;
	a.PrintInFile();
	a.DeleteSong(a.FindSong("Имя3", "Исполнитель3"));
	cout << "Песенник после удаления песни:" << endl;
	a.PrintInConsole();
	cout << "Текущее число песен = " << a.GetCountSongs() << endl;
	cout << "Текущее число песен в файле = " << a.GetCountSongsInFile() << endl;
	cout << "Создадим еще один песенник с песнями из файла" << endl;
	cout << "Песенник с данными из файла:" << endl;
	b.GetFromFile();
	b.PrintInConsole(); 
	system("pause");

}