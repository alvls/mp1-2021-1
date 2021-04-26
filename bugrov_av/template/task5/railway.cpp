#include "all.h"
bool railway::check(userdata& inf)//тут я вычитаю места
{////////////////////////////////////////////сделать присвоение номера вагона
	int j = 0;
	switch (inf.Ttype)
	{
	case trainType::firm:
		switch (inf.Wtype)
		{
		case wagonType::down_c:
			for (int i = ftrain.c_first; i < ftrain.c_last; i++)
				if (ftrain.down_coupe[i])
				{
					ftrain.down_coupe[i]--;
					inf.wnumber = i;
					return true;
				}
			return false;
			break;
		case wagonType::down_r:
			for (int i = ftrain.r_first; i < ftrain.r_last; i++)
				if (ftrain.down_reserved[i])
				{
					ftrain.down_reserved[i]--;
					inf.wnumber = i;
					return true;
				}
			return false;
			break;
		case wagonType::up_c:
			for (int i = ftrain.c_first; i < ftrain.c_last; i++)
				if (ftrain.up_coupe[i])
				{
					ftrain.up_coupe[i]--;
					inf.wnumber = i;
					return true;
				}
			return false;
			break;
		case wagonType::up_r:
			for (int i = ftrain.r_first; i < ftrain.r_last; i++)
				if (ftrain.up_reserved[i])
				{
					ftrain.up_reserved[i]--;
					inf.wnumber = i;
					return true;
				}
			return false;
			break;
		case wagonType::sleep:
			for (int i = ftrain.s_first; i < ftrain.s_last; i++)
				if (ftrain.sleeping[i])
				{
					ftrain.sleeping[i]--;
					inf.wnumber = i;
					return true;
				}
			return false;
		}
		break;
	case trainType::speed:
		switch (inf.Wtype)
		{
		case wagonType::down_c:
			for (int i = strain.c_first; i < strain.c_last; i++)
				if (strain.down_coupe[i])
				{
					strain.down_coupe[i]--;
					inf.wnumber = i;
					return true;
				}
			return false;
			break;
		case wagonType::down_r:
			for (int i = strain.r_first; i < strain.r_last; i++)
				if (strain.down_reserved[i])
				{
					strain.down_reserved[i]--;
					inf.wnumber = i;
					return true;
				}
			return false;
			break;
		case wagonType::up_c:
			for (int i = strain.c_first; i < strain.c_last; i++)
				if (strain.up_coupe[i])
				{
					strain.up_coupe[i]--;
					inf.wnumber = i;
					return true;
				}
			return false;
			break;
		case wagonType::up_r:
			for (int i = strain.r_first; i < strain.r_last; i++)
				if (strain.up_reserved[i])
				{
					strain.up_reserved[i]--;
					inf.wnumber = i;
					return true;
				}
			return false;
			break;
		}
		break;
	case trainType::swallow:
		for (int i = 0; i < 8; i++)
			if (swtrain[inf.tnumber].wagon[i])
			{
				swtrain[j].wagon[i]--;
				inf.tnumber = i;
				return true;
			}
		return false;
	}
}
speed::speed()
{
	for (int i = 0; i < 4; i++)
		up_coupe[i] = down_coupe[i] = COUPE;
	for (int i = 0; i < 8; i++)
		up_reserved[i] = down_reserved[i] = RESERVED;
}
speed& speed:: operator=(const speed& s)
{
	if (&s == this)
		return *this;
	for (int i = 0; i < 4; i++)
		up_coupe[i] = s.up_coupe[i];
	for (int i = 0; i < 4; i++)
		down_coupe[i] = s.down_coupe[i];
	for (int i = 0; i < 8; i++)
		up_reserved[i] = s.up_reserved[i];
	for (int i = 0; i < 8; i++)
		down_reserved[i] = s.down_reserved[i];
	return *this;
}
speed::speed(const speed& s)
{
	for (int i = 0; i < 4; i++)
		up_coupe[i] = s.up_coupe[i];
	for (int i = 0; i < 4; i++)
		down_coupe[i] = s.down_coupe[i];
	for (int i = 0; i < 8; i++)
		up_reserved[i] = s.up_reserved[i];
	for (int i = 0; i < 8; i++)
		down_reserved[i] = s.down_reserved[i];
}
swallow& swallow::operator=(const swallow& s)
{
	if (&s == this)
		return *this;
	for (int i = 0; i < 8; i++)
		wagon[i] = s.wagon[i];
	return *this;
}
firm::firm()
{
	for (int i = 0; i < 6; i++)
		up_coupe[i] = down_coupe[i] = COUPE;
	for (int i = 0; i < 4; i++)
		up_reserved[i] = down_reserved[i] = RESERVED;
	for (int i = 0; i < 2; i++)
		sleeping[i] = SLEEPING;
}
firm& firm:: operator=(const firm& f)
{
	if (&f == this)
		return *this;
	for (int i = 0; i < 6; i++)
		up_coupe[i] = f.up_coupe[i];
	for (int i = 0; i < 6; i++)
		down_coupe[i] = f.down_coupe[i];
	for (int i = 0; i < 4; i++)
		up_reserved[i] = f.up_reserved[i];
	for (int i = 0; i < 4; i++)
		down_reserved[i] = f.down_reserved[i];
	for (int i = 0; i < 2; i++)
		sleeping[i] = f.sleeping[i];
	return *this;
}
firm::firm(const firm& f)
{
	for (int i = 0; i < 6; i++)
		up_coupe[i] = f.up_coupe[i];
	for (int i = 0; i < 6; i++)
		down_coupe[i] = f.down_coupe[i];
	for (int i = 0; i < 4; i++)
		up_reserved[i] = f.up_reserved[i];
	for (int i = 0; i < 4; i++)
		down_reserved[i] = f.down_reserved[i];
	for (int i = 0; i < 2; i++)
		sleeping[i] = f.sleeping[i];
}