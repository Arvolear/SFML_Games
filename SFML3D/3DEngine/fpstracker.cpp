#include "fpstracker.hpp"

using namespace std;
using namespace sf;

FPSTracker::FPSTracker(double width, double height)
{
    FPS = 0;
    stop = false;

    FPSText.font.loadFromFile("./fonts/digital-7.ttf");
    
    FPSText.x = 10;
    FPSText.y = -5;
    FPSText.chsize = height / 13;

    FPSText.c = Color::Yellow;
}

void FPSTracker::stopCounter()
{
    stop = true;
}

void FPSTracker::addFPS()
{
    FPS++;
}

void FPSTracker::count(int time)
{
    while (!stop)
    {
        this_thread::sleep_for(chrono::milliseconds(time));

        FPSText.s = to_string(FPS);

        FPS = 0;
    }
}

void FPSTracker::show(RenderWindow &scene)
{  
    if (FPSText.text.getString() != FPSText.s)
    {
        FPSText.text.setFont(FPSText.font);
        FPSText.text.setPosition(Vector2f(FPSText.x, FPSText.y));
        FPSText.text.setCharacterSize(FPSText.chsize);
        FPSText.text.setColor(FPSText.c);
        FPSText.text.setString(FPSText.s);
    }

    scene.draw(FPSText.text);
}

FPSTracker::~FPSTracker(){}
