#include "main.h"
#include <iostream>
int main()
{
    ProcCenter a("Data.txt");
    Credit b(&a);
    cout << b.Authorize(1231,"0932") << endl;
    cout << b.Authorize(1231,"8765") << endl;
    return 0;
}
