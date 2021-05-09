#include "all.h"
bool railway::check(userdata& inf)//��� � ������� �����
{///////////////////////////////////////////��, � ���� � �������������� ��������������, �� ���������� ����� ���� � �� �� � ����� ������� �� �������
	switch (inf.Ttype)
	{
	case trainType::firm:
		switch (inf.Wtype)
		{
		case wagonType::down_c:
			for (int i = ftrain.c_first; i <= ftrain.c_last; i++)
				if (ftrain.down_coupe[i])
				{
					ftrain.down_coupe[i]--;
					inf.sitnumber = -ftrain.down_coupe[i] + ftrain.COUPE;
					inf.wnumber = i + 1;
					return true;
				}
			return false;
			break;
		case wagonType::down_r:
			for (int i = ftrain.r_first; i <= ftrain.r_last; i++)
				if (ftrain.down_reserved[i])
				{
					ftrain.down_reserved[i]--;
					inf.sitnumber = -ftrain.down_reserved[i] + ftrain.RESERVED;
					inf.wnumber = i + 1;
					return true;
				}
			return false;
			break;
		case wagonType::up_c:
			for (int i = ftrain.c_first; i <= ftrain.c_last; i++)
				if (ftrain.up_coupe[i])
				{
					ftrain.up_coupe[i]--;
					inf.sitnumber = -ftrain.up_coupe[i] + ftrain.COUPE;
					inf.wnumber = i + 1;
					return true;
				}
			return false;
			break;
		case wagonType::up_r:
			for (int i = ftrain.r_first; i <= ftrain.r_last; i++)
				if (ftrain.up_reserved[i])
				{
					ftrain.up_reserved[i]--;
					inf.sitnumber = -ftrain.up_reserved[i] + ftrain.RESERVED;
					inf.wnumber = i + 1;
					return true;
				}
			return false;
			break;
		case wagonType::sleep:
			for (int i = ftrain.s_first; i <= ftrain.s_last; i++)
				if (ftrain.sleeping[i])
				{
					ftrain.sleeping[i]--;
					inf.sitnumber = -ftrain.sleeping[i] + ftrain.SLEEPING;
					inf.wnumber = i + 1;
					return true;
				}
			return false;
		}
		break;
	case trainType::speed:
		switch (inf.Wtype)
		{
		case wagonType::down_c:
			for (int i = strain.c_first; i <= strain.c_last; i++)
				if (strain.down_coupe[i])
				{
					strain.down_coupe[i]--;
					inf.sitnumber = -strain.down_coupe[i] + strain.COUPE;
					inf.wnumber = i + 1;
					return true;
				}
			return false;
			break;
		case wagonType::down_r:
			for (int i = strain.r_first; i <= strain.r_last; i++)
				if (strain.down_reserved[i])
				{
					strain.down_reserved[i]--;
					inf.sitnumber = -strain.down_reserved[i] + strain.RESERVED;
					inf.wnumber = i + 1;
					return true;
				}
			return false;
			break;
		case wagonType::up_c:
			for (int i = strain.c_first; i <= strain.c_last; i++)
				if (strain.up_coupe[i])
				{
					strain.up_coupe[i]--;
					inf.sitnumber = -strain.up_coupe[i] + strain.COUPE;
					inf.wnumber = i + 1;
					return true;
				}
			return false;
			break;
		case wagonType::up_r:
			for (int i = strain.r_first; i <= strain.r_last; i++)
				if (strain.up_reserved[i])
				{
					strain.up_reserved[i]--;
					inf.sitnumber = -strain.up_reserved[i] + strain.RESERVED;
					inf.wnumber = i + 1;
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
				int j = 0;
				switch (inf.tnumber)
				{
				case 5:case 6:
					j = 0;
					break;
				case 7: case 8:
					j = 1;
					break;
				case 9:case 10:
					j = 2;
					break;
				}
				swtrain[j].wagon[i]--;
				inf.sitnumber = 100 - swtrain[j].wagon[i];
				inf.tnumber = i + 1;
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
ostream& operator<<(ostream& place, const userdata& u)
{
	place << "����: " << u.date << "-� ����\n";
	place << "�����������:\n";
	if (u.tnumber % 2)
	{
		place << "������ ��������. ���������� ������\n";
		place << "��������:\n������. ������� ������\n";
	}
	else
	{
		place << "������. ������� ������\n";
		place << "��������:\n������ ��������. ���������� ������\n";
	}
	place << "��� ���������:\n";
	place << u.surname << "\n";
	place << u.name << "\n";
	place << u.patronymic << "\n";
	switch (u.Ttype)
	{
	case trainType::firm:
		place << "��������� �����\n";
		switch (u.Wtype)
		{
		case wagonType::down_c:
			place << "����. ������ �����\n";
			break;
		case wagonType::down_r:
			place << "��������. ������ �����\n";
			break;
		case wagonType::sleep:
			place << "�������� �����\n";
			break;
		case wagonType::up_c:
			place << "����. ������� �����\n";
			break;
		case wagonType::up_r:
			place << "��������. ������� �����\n";
			break;
		}
		break;
	case trainType::speed:
		place << "������ �����\n";
		switch (u.Wtype)
		{
		case wagonType::down_c:
			place << "����. ������ �����\n";
			break;
		case wagonType::down_r:
			place << "��������. ������ �����\n";
			break;
		case wagonType::up_c:
			place << "����. ������� �����\n";
			break;
		case wagonType::up_r:
			place << "��������. ������� �����\n";
			break;
		}
		break;
	case trainType::swallow:
		place << "����� \"��������\"\n";
		break;
	}
	place << "� ������: " << u.tnumber << "\n";
	place << "� ������: " << u.wnumber << "\n";
	place << "� �����: " << u.sitnumber << "\n";
	return place;
}