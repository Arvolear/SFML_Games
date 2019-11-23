#include "logic.h"
#include "win.h"
#include "graphics.h"
#include "settings.h"

using namespace std;

int main()
{
    Settings *S = new Settings();    

    S->start();
    
    delete S;
    return 0;
}
