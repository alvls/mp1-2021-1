
#include "all.h"

OneCard::OneCard()
{
    fullname.name = "�";
    fullname.surname = "�";
    fullname.patronymic = "�";
    cardID = 0;
    PINcode = 0;
    money = 0;
    locked = false;
}

istream& operator>> (istream& in, OneCard& information)
{
    in >> information.fullname.surname >> information.fullname.name >> information.fullname.patronymic >> information.cardID >> information.PINcode >> information.money >> information.locked;
    return in;
}

ostream& operator<< (ostream& out, const OneCard& information)
{
    out << information.fullname.surname << " " << information.fullname.name << " " << information.fullname.patronymic << " " << information.cardID << " " << information.PINcode << " " << information.money << " " << information.locked;
    return out;
}
