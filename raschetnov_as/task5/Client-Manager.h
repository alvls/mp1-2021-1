
#include <vector>

class Client
{
  std::string name;
  std::string lastname;
  std::string patronymic;
  int carnumber;
  int seatnumber;
public:
  Client(std::string _name, std::string _lastname, std::string _patronymic, int _carnumber, int _seatnumber):name(_name), lastname(_lastname), patronymic(_patronymic), carnumber(_carnumber), seatnumber(_seatnumber){};
  std::string getName();
  std::string getLastName();
  std::string getPatronymic();
  int getCarNumber();
  int getSeatNumber();
};

class Manager
{
  std::vector<Client> clients;
public:
  int informationOutput(std::string path, std::string carnumber);
  void createClient(std::string _name, std::string _lastname, std::string _patronymic, int _carnumber, int _seatnumber);
  void loadClientsList(std::string path);
  void showClients();
  int getSize();
  void clientBaseUpdate(std::string path);
  void showFreeSeats(std::string path);
  void bookSeat(std::string path, std::string car, int _seatnumber);
  void formTicket(std:: string _date, std::string _name, std::string _lastname, std::string _patronymic, int direction, int train);
};

class Ticket
{
  std::string date;
  std::string trainNumber;
  std::string name;
  std::string lastname;
  std::string patronymic;
  std::string departureStation;
  std::string arrivalStation;
public:
  Ticket(std::string _date, std::string _trainNumber, std::string _name, std::string _lastname, std::string _patronymic, std::string _departureStation, std::string _arrivalStaion):
    date(_date), trainNumber(_trainNumber), name(_name), lastname(_lastname), patronymic(_patronymic), departureStation(_departureStation), arrivalStation(_arrivalStaion) {};
};
