#pragma once
enum class trainType
{
	firm, speed, swallow
};
enum class wagonType
{
	up_c, down_c, up_r, down_r, sleep
};
class train
{
protected:
	const int COUPE = 18;
	const int RESERVED = 27;
};
class firm : public train
{
	const int SLEEPING = 18;
	int up_coupe[6];//купе
	int down_coupe[6];
	int up_reserved[4];//плацкартные вагоны
	int down_reserved[4];
	int sleeping[2];//спальные вагоны
	enum places
	{
		c_first = 1, c_last = 6, r_first, r_last = 10, s_first, s_last = 12
	};
public:
	firm();
	firm& operator=(const firm& f);
	firm(const firm& f);
	friend class railway;
};
class speed : public train
{
	enum places
	{
		c_first = 1, c_last = 4, r_first, r_last = 12
	};
	int up_coupe[4];//купе
	int down_coupe[4];
	int up_reserved[8];//плацкартные вагоны
	int down_reserved[8];
public:
	speed();
	speed& operator=(const speed& s);
	speed(const speed& s);
	friend class railway;
};
class swallow
{
	int wagon[8] = { 100,100, 100, 100, 100, 100, 100, 100 };
public:
	swallow()
	{
		for (int i = 0; i < 8; i++)
			wagon[i] = 100;
	}
	swallow(const swallow& s)
	{
		for (int i = 0; i < 8; i++)
			wagon[i] = s.wagon[i];
	}
	swallow& operator=(const swallow& s);
	friend class railway;
};
class userdata
{
	string surname;//+
	string name;//+
	string patronymic;//+
	trainType Ttype;//
	wagonType Wtype;//У ласточки первые три доли указывают на то, в какое время она идёт
	int date;//+
	int tnumber;//номер поездa+
	int wnumber;//номер вагонa-
	friend class cashbox;
	friend class railway;
	friend void setwtype(const int pointer, userdata& data);
public:
	userdata() :surname(""), name(""), patronymic(""), Ttype(trainType::swallow), Wtype(wagonType::up_r), date(0), tnumber(0), wnumber(0)
	{

	}
	userdata(const userdata& origin) :surname(origin.surname), name(origin.name), patronymic(origin.patronymic), Ttype(origin.Ttype), Wtype(origin.Wtype), date(origin.date), tnumber(origin.tnumber), wnumber(origin.wnumber)
	{

	}
};
class railway
{
	swallow swtrain[3];
	speed strain;
	firm ftrain;
public:
	railway(const railway& r)
	{
		for (int i = 0; i < 3; i++)
			swtrain[i] = r.swtrain[i];
		strain = r.strain;
		ftrain = r.ftrain;
	}
	railway()
	{
		swallow _news;
		for (int i = 0; i < 3; i++)
			swtrain[i] = _news;
		speed _newspeed;
		strain = _newspeed;
		firm _ftrain;
		ftrain = _ftrain;
	}
	bool check(userdata& inf);
	friend class cashbox;
};
