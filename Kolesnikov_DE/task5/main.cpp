#include "main.h"
int main()
{
    ProcCenter a("Data.txt");
    Credit b(&a);
    b.Authorize(1231,"0932");
    b.Authorize(1231,"8765");
    return 0;
}
