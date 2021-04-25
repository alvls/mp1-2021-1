#include "all.h"
bool railway::check(userdata inf)//тут я вычитаю места
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
					return true;
				}
			return false;
			break;
		case wagonType::down_r:
			for (int i = ftrain.r_first; i < ftrain.r_last; i++)
				if (ftrain.down_reserved[i])
				{
					ftrain.down_reserved[i]--;
					return true;
				}
			return false;
			break;
		case wagonType::up_c:
			for (int i = ftrain.c_first; i < ftrain.c_last; i++)
				if (ftrain.up_coupe[i])
				{
					ftrain.up_coupe[i]--;
					return true;
				}
			return false;
			break;
		case wagonType::up_r:
			for (int i = ftrain.r_first; i < ftrain.r_last; i++)
				if (ftrain.up_reserved[i])
				{
					ftrain.up_reserved[i]--;
					return true;
				}
			return false;
			break;
		case wagonType::sleep:
			for (int i = ftrain.s_first; i < ftrain.s_last; i++)
				if (ftrain.sleeping[i])
				{
					ftrain.sleeping[i]--;
					return true;
				}
			return false;
		default:
			break;
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
					return true;
				}
			return false;
			break;
		case wagonType::down_r:
			for (int i = strain.r_first; i < strain.r_last; i++)
				if (strain.down_reserved[i])
				{
					strain.down_reserved[i]--;
					return true;
				}
			return false;
			break;
		case wagonType::up_c:
			for (int i = strain.c_first; i < strain.c_last; i++)
				if (strain.up_coupe[i])
				{
					strain.up_coupe[i]--;
					return true;
				}
			return false;
			break;
		case wagonType::up_r:
			for (int i = strain.r_first; i < strain.r_last; i++)
				if (strain.up_reserved[i])
				{
					strain.up_reserved[i]--;
					return true;
				}
			return false;
			break;
		default:
			break;
		}
		break;
	case trainType::swallow:
		switch (inf.Wtype)
		{
		case wagonType::up_c:
			j = 0;
			goto met_default;
			break;
		case wagonType::down_c:
			j = 1;
			goto met_default;
			break;
		case wagonType::up_r:
			j = 2;
			goto met_default;
			break;
		default:
		met_default:			for (int i = 0; i < 8; i++)
			if (swtrain[j].wagon[i])
			{
				swtrain[j].wagon[i]--;
				return true;
			}
		return false;
		break;
		}
		break;
	default:
		break;
	}
}