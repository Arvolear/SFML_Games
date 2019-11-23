#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <thread>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf; 

class Menu
{
    private:
        int curWinSizeIndex;

        int choosenMode;
        int whoGoesFirst;

        Frontend *front;

        UniversalElement *menuBack;
        UniversalElement *PVPMode;
        UniversalElement *PVCMode;
        UniversalElement *resize;

    public:
        Menu();

        void resizeWindow(RenderWindow &pentago, bool mouse);
        void setup();
        void start(RenderWindow &pentago);
        void chooseType(RenderWindow &pentago);
        void play();

        void show(RenderWindow &pentago);

        ~Menu();
};
