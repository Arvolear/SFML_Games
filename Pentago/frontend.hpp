#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <thread>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf; 

class Frontend
{
    private:
        int gameType;
        int boardParts;
        int whoWins;
        bool hideWinScreen;
        bool hideWinScreenHelper;

        Backend* backend;
        Bot *bot;
      
        UniversalElement *back;
        UniversalElement *turnLeft;
        UniversalElement *turnRight;
        UniversalElement *ballTurn;

        UniversalElement *boardBack;
        vector < vector < BoardPart* > > board;
                            
        thread *rotation;

        Clock clock;
        WinScreen *winScreen;

        void setup();

        bool onClick(RenderWindow &pentago);
        void pickBall(RenderWindow &pentago);
        void pickPart(RenderWindow &pentago);
        void rotateChoosenPart(int code);
        
        void cpuTurn(RenderWindow &pentago);

        void updateFront();
        void updateTurn();

        void show(RenderWindow &pentago);

    public:
        Frontend(int type, int whoGoesFirst);

        void play(RenderWindow &pentago);        

        ~Frontend();
};
