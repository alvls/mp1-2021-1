
#include "all.h"

ostream& operator<< (ostream& out, const Name& inform)
{
    out << inform.surname << " " << inform.name;
    return out;
}

OneCard::OneCard()
{
    fullname.name = "Ô";
    fullname.surname = "È";
    fullname.patronymic = "Î";
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
    out << information.fullname.surname << " " << information.fullname.name << " " << information.fullname.patronymic << " " << information.cardID << " " << information.PINcode << " " << information.money << " " << information.locked << "\n";
    return out;
}
