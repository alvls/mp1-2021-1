//Разработать классы Железнодорожная касса и Горьковская железная дорога.
//Класс Железнодорожная касса должен имитировать работу кассы по продаже билетов на поезда Нижний Новгород – Москва.
//Считать, что продажа билетов проводится на поезда в пределах 30 дней от текущей даты.
//Считать, что по маршруту Нижний Новгород – Москва курсирует три скоростных поезда «Ласточка», один фирменный и один скорый поезд в сутки в каждом направлении.
//Все вагоны в поездах «Ласточка» однотипны и содержат по 100 сидячих мест.
///В фирменном и скором поездах вагоны трех типов : 
///плацкартные(27 верхних, 27 нижних мест),
///купейные(18 верхних, 18 нижних мест), 
///СВ(18 нижних мест).
//Число вагонов в поездах «Ласточка» – 8. 
///В фирменном поезде
/// - 2 вагона СВ, 
/// - 6 купейных вагонов, 
/// - 4 плацкартных вагона.
///В скором поезде – 4 купейных вагона, 8 плацкартных вагонов.
//Поезда идентифицируются номерами(десять номеров из диапазона от 1 до 100), 
///вагоны – номерами(целые числа от 1 до 12), 
/// места – номерами(целые числа от 1 до максимума для данного типа вагона).
//Информация о всех поездах и всех проданных билетах хранится в классе Горьковская железная дорога.
//Для каждого поезда, каждого типа вагона и каждого типа места установлена стоимость билета.
//Считать, что все поезда не делают промежуточных остановок по маршруту.
//Класс Железнодорожная касса должен предоставлять следующие операции : 
//1) принять данные покупателя : дату, поезд, тип вагона(если есть выбор), количество билетов каждого возможного вида(если есть выбор), ФИО пассажиров 
//2) проверить наличие свободных мест по запросу покупателя(при невозможности выдать все билеты в одном вагоне, считать заказ невыполнимым), 
//3) зарезервировать места,
//4) рассчитать общую стоимость билет//ов, 
//5) отменить заказ билетов, 
//6) сформировать билеты(каждый билет включает : дату, номер поезда, номер вагона, номер места, ФИО пассажира, станция отправления, станция прибытия).
///Класс Горьковская железная дорога должен использоваться для поддержки работы класса Железнодорожная касса и может быть разработан в минимально - необходимом варианте.
///		            ДОПОЛНИТЕЛЬНО ПО ЗАДАЧЕ
/// Поезда едут туда и обратно в Москву
/// Считается, что я моделирую работу автомата и поэтому мне нужно, чтобы он всегда работал? yes
/// Как зарезервировать места для некоторого числа объектов в векторе?
/// Лучше принимать от человека данные в виде массива (потому что придётся разделять по разным билетам)
/// Нужно взаимодействие со свободными местами организовать через железную дорогу (т.е. функция check получает информацию от railway)
/// При выдаче билетов нужно ещё указывать места, лучше просто от 1 до max, поэтому ещё нужно вычитать из max число оставшихся
#include "all.h"
//enum class trainType
//{
//	firm, speed, swallow
//};
//enum class wagonType
//{
//	up_c, down_c, up_r, down_r, sleep
//};
//class wagon
//{
//public:
//	wagon& operator=(wagon& v);
//protected:
//	const int COUPE = 18;
//	const int RESERVED = 27;
//};
////int ffo()
////{
////	wagonType c = wagonType::sleep;
////	int a = static_cast<int>(c);
////}
//class firm : public wagon
//{
//	const int SLEEPING = 18;
//	int up_coupe[6];//купе
//	int down_coupe[6];
//	int up_reserved[4];//плацкартные вагоны
//	int down_reserved[4];
//	int sleeping[2];//спальные вагоны
//	enum places
//	{
//		c_first = 1, c_last = 6, r_first, r_last = 10, s_first, s_last = 12
//	};
//public:
//	firm()
//	{
//		for (int i = 0; i < 6; i++)
//			up_coupe[i] = down_coupe[i] = COUPE;
//		for (int i = 0; i < 4; i++)
//			up_reserved[i] = down_reserved[i] = RESERVED;
//		for (int i = 0; i < 2; i++)
//			sleeping[i] = SLEEPING;
//	}
//	firm& operator=(firm& f)
//	{
//		for (int i = 0; i < 6; i++)
//			up_coupe[i] = f.up_coupe[i];
//		for (int i = 0; i < 6; i++)
//			down_coupe[i] = f.down_coupe[i];
//		for (int i = 0; i < 4; i++)
//			up_reserved[i] = f.up_reserved[i];
//		for (int i = 0; i < 4; i++)
//			down_reserved[i] = f.down_reserved[i];
//		for (int i = 0; i < 2; i++)
//			sleeping[i] = SLEEPING;
//	}
//	friend class railway;
//};
//class speed: public wagon
//{
//	enum places
//	{
//		c_first = 1, c_last = 4, r_first, r_last = 12
//	};
//	int up_coupe[4];//купе
//	int down_coupe[4];
//	int up_reserved[8];//плацкартные вагоны
//	int down_reserved[8];
//public:
//	speed()
//	{
//		for (int i = 0; i < 4; i++)
//			up_coupe[i] = down_coupe[i] = COUPE;
//		for (int i = 0; i < 8; i++)
//			up_reserved[i] = down_reserved[i] = RESERVED;
//	}
//	speed& operator=(speed& s)
//	{
//		for (int i = 0; i < 4; i++)
//			up_coupe[i] = s.up_coupe[i];
//		for (int i = 0; i < 4; i++)
//			down_coupe[i] = s.down_coupe[i];
//		for (int i = 0; i < 8; i++)
//			up_reserved[i] = s.up_reserved[i];
//		for (int i = 0; i < 8; i++)
//			down_reserved[i] = s.down_reserved[i];
//	}
//	friend class railway;
//};
//class swallow
//{
//	int wagon[8] = { 100,100, 100, 100, 100, 100, 100, 100 };
//	swallow()
//	{
//		for (int i = 0; i < 8; i++)
//			wagon[i] = 100;
//	}// Реализовать конструктор копирования
//	friend class railway;
//};
//class userdata
//{
//	string surname;
//	string name;
//	string patronymic;
//	trainType Ttype;//
//	wagonType Wtype;//У ласточки первые три доли указывают на то, в какое время она идёт
//	int date[2];
//	char number;//номер поезда
//	friend class cashbox;
//	friend class railway;
//public:
//};
//class railway
//{
//	swallow swtrain[3];
//	speed strain;
//	firm ftrain;
//public:
//	railway(railway& r)
//	{
//		for (int i = 0; i < 3; i++)
//			swtrain[i] = r.swtrain[i];
//		strain = r.strain;
//		ftrain = r.ftrain;
//	}
//	railway()
//	{
//
//	}
//	bool check(userdata inf);
//	friend class cashbox;
//};
//bool railway::check(userdata inf)//тут я вычитаю места
//{
//	switch (inf.Ttype)
//	{
//	case trainType::firm:
//		switch (inf.Wtype)
//		{
//		case wagonType::down_c:
//			for (int i = ftrain.c_first; i < ftrain.c_last; i++)
//				if (ftrain.down_coupe[i])
//				{
//					ftrain.down_coupe[i]--;
//					return true;
//				}
//				return false;
//			break;
//		case wagonType::down_r:
//			for (int i = ftrain.r_first; i < ftrain.r_last; i++)
//				if (ftrain.down_reserved[i])
//				{
//					ftrain.down_reserved[i]--;
//					return true;
//				}
//			return false;
//			break;
//		case wagonType::up_c:
//			for (int i = ftrain.c_first; i < ftrain.c_last; i++)
//				if (ftrain.up_coupe[i])
//				{
//					ftrain.up_coupe[i]--;
//					return true;
//				}
//			return false;
//			break;
//		case wagonType::up_r:
//			for (int i = ftrain.r_first; i < ftrain.r_last; i++)
//				if (ftrain.up_reserved[i])
//				{
//					ftrain.up_reserved[i]--;
//					return true;
//				}					
//			return false;
//			break;
//		case wagonType::sleep:
//			for (int i = ftrain.s_first; i < ftrain.s_last; i++)
//				if (ftrain.sleeping[i])
//				{
//					ftrain.sleeping[i]--;
//					return true;
//				}
//		default:
//			break;
//		}
//		break;
//	case trainType::speed:
//		switch (inf.Wtype)
//		{
//		case wagonType::down_c:
//			for (int i = strain.c_first; i < strain.c_last; i++)
//				if (strain.down_coupe[i])
//				{
//					strain.down_coupe[i]--;
//					return true;
//				}
//			return false;
//			break;
//		case wagonType::down_r:
//			for (int i = strain.r_first; i < strain.r_last; i++)
//				if (strain.down_reserved[i])
//				{
//					strain.down_reserved[i]--;
//					return true;
//				}
//			return false;
//			break;
//		case wagonType::up_c:
//			for (int i = strain.c_first; i < strain.c_last; i++)
//				if (strain.up_coupe[i])
//				{
//					strain.up_coupe[i]--;
//					return true;
//				}
//			return false;
//			break;
//		case wagonType::up_r:
//			for (int i = strain.r_first; i < strain.r_last; i++)
//				if (strain.up_reserved[i])
//				{
//					strain.up_reserved[i]--;
//					return true;
//				}
//			else
//				return false;
//			break;
//		default:
//			break;
//		}
//		break;
//	case trainType::swallow:
//		int j = 0;
//		switch (inf.Wtype)
//		{
//		case wagonType::up_c:
//			j = 0;
//			goto met_default;
//			break;
//		case wagonType::down_c:
//			j = 1;
//			goto met_default;
//			break;
//		case wagonType::up_r:
//			j = 2;
//			goto met_default;
//			break;
//		default:
//met_default:			for (int i = 0; i < 8; i++)
//				if (swtrain[j].wagon[i])
//				{
//					swtrain[j].wagon[i]--;
//					return true;
//				}
//			return false;
//			break;
//		}
//		break;
//	default:
//		break;
//	}
//}
//class cashbox
//{
//	//едут в Мск: 1 - фирменный; 3 - скорый; 5,7,9 - ласточка
//	//едут в НН: 2 - фирменный; 4 - скорый; 6,8,10 - ласточка
//	vector<railway> toNN, toMsk;
//	userdata SetData();//получает данные о пользователе
//					   //проверяет, можно ли вычесть из количества билетов, чтобы оно не стало отрицательным
//	/// меняет также число свободных билетов.
//	void GetTicket(userdata inf);//сформировать билет
//public:
//	void SetPlace();//полная обработка действий с билетами
//	cashbox()
//	{
//		railway tmp_rail;
//		for (int i = 0; i < 30; i++)/////сдесь нужно считывать из файла
//		{
//			toNN.push_back(tmp_rail);
//			toMsk.push_back(tmp_rail);
//		}
//	}
//};
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
void menu()
{
	cashbox box;
	while (1)
		box.SetPlace();
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	menu();
}