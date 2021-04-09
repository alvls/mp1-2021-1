
#include "all.h"

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

istream& operator>> (istream& in, OneCard CharactOfPers)
{
    in >> CharactOfPers.fullname.name;
    in >> CharactOfPers.fullname.surname;
    in >> CharactOfPers.fullname.patronymic;
    in >> CharactOfPers.cardID;
    in >> CharactOfPers.PINcode;
    in >> CharactOfPers.money;
    in >> CharactOfPers.locked;
    return in;
}