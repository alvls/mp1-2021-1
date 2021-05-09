#define _CRT_SECURE_NO_WARNINGS
int directionChoice();
std::string dateChoice();
int showAvailableTrains(std::string date);
int getTime();
std::string carChoice(int& carnumber, int train, int direction, std::string date);
void carInforamtion(int train, int direction, std::string date);
int seatChoice(int carCounter);
void showLastochka0929();
void showLastochka1331();
void showLastochka1755();
void showFirmennii1514();
void showSkorii1824();
std::string getDate1();
void getFullName(std::string* FullName);
int formPrice(int train, int car);