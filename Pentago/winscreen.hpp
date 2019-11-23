#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <thread>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf; 

struct WinSign
{
    Text text;
    Font font;

    int x1, y1;
    int x2, y2;

    int chsize;
    Color color1;
    Color color2;
    string sign;
};

class WinScreen
{
    private:
        WinSign *winSign;
        WinSign *winSignDupl;

        vector < UniversalElement* > elements;

    public:
        WinScreen();

        void setup(int whoWins);

        int click(RenderWindow &pentago);

        void show(RenderWindow &pentago);

        ~WinScreen();
};
