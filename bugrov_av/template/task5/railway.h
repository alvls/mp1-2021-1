#pragma once
enum class trainType
{
	firm, speed, swallow
};
enum class wagonType
{
	up_c, down_c, up_r, down_r, sleep
};
//----------------------------------------------------------
class userdata
{
	string surname;//+
	string name;//+
	string patronymic;//+
	trainType Ttype;//
	wagonType Wtype;//� �������� ������
	int date;//+
	int tnumber;//����� �����a+
	int wnumber;//����� �����a+
	int sitnumber;//����� �������
	friend class cashbox;
	friend class railway;
	friend void setwtype(const int pointer, userdata& data);
	friend ostream& operator<<(ostream& place, const userdata& u);
public:
	userdata() :surname(""), name(""), patronymic(""), Ttype(trainType::swallow), Wtype(wagonType::up_r), date(0), tnumber(0), wnumber(0), sitnumber(1)
	{

	}
	userdata(const userdata& origin) :surname(origin.surname), name(origin.name), patronymic(origin.patronymic), Ttype(origin.Ttype), Wtype(origin.Wtype), date(origin.date), tnumber(origin.tnumber), wnumber(origin.wnumber), sitnumber(origin.sitnumber)
	{

	}
};
//----------------------------------------------------------
class train
{
protected:
	const int COUPE = 18;
	const int RESERVED = 27;
	friend class railway;
};
class firm : public train
{
	const int SLEEPING = 18;
	int up_coupe[6];//����
	int down_coupe[6];
	int up_reserved[4];//����������� ������
	int down_reserved[4];
	int sleeping[2];//�������� ������
	enum places
	{
		c_first = 0, c_last = 5, r_first, r_last = 9, s_first, s_last = 11
	};
	friend ostream& operator<<(ostream& place, const cashbox& c);
	friend istream& operator>>(istream& place, cashbox& c);
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
		c_first = 0, c_last = 3, r_first, r_last = 11
	};
	int up_coupe[4];//����
	int down_coupe[4];
	int up_reserved[8];//����������� ������
	int down_reserved[8];
	friend ostream& operator<<(ostream& place, const cashbox& c);
	friend istream& operator>>(istream& place, cashbox& c);
public:
	speed();
	speed& operator=(const speed& s);
	speed(const speed& s);
	friend class railway;
};
class swallow
{
	int wagon[8] = { 100,100, 100, 100, 100, 100, 100, 100 };
	friend ostream& operator<<(ostream& place, const cashbox& c);
	friend istream& operator>>(istream& place, cashbox& c);
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
class railway
{
	swallow swtrain[3];
	speed strain;
	firm ftrain;
	friend ostream& operator<<(ostream& place, const cashbox& c);
	friend istream& operator>>(istream& place, cashbox& c);
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