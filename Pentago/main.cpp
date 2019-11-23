/* 
 * By Artem Chistyakov 
 */

#include <iostream>

#include "backend.hpp"
#include "bot.hpp"
#include "boardpart.hpp"
#include "winscreen.hpp"
#include "frontend.hpp"
#include "menu.hpp"

using namespace std;

int main()
{
    Menu* M = new Menu();

    M->play();

    delete M;

    return 0;
}
