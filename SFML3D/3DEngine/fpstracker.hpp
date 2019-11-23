#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class FPSTracker
{
    private:
        bool stop;
        int FPS;

        struct T
        {
            Text text;
            Font font;

            int x, y;
            int chsize;

            Color c;

            string s = "";
        };

        T FPSText;

    public:
        FPSTracker(double width, double height);
        
        void stopCounter();

        void addFPS();

        void count(int time);

        void show(RenderWindow &scene);

        ~FPSTracker();
};
