#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Settings
{
    private:
        Graphics *graphics;

        bool isstart = true;
        int zoom = 1;

        int width = 3;
        int height = 3;
        int amtowin = 3;

        struct b
        {
            RectangleShape back;
            Color color;
            int w, h;
            int x, y;
        };

        struct d
        {
            bool choosen = false;
            bool mouseclick = false;

            Font font;
            Text tinside;
            Text toutside;
            string sin = "3";
            string sout = "";
            int chsize;
            int tinx, tiny;
            int toutx, touty;
            Color inc;
            Color outc;

            Texture texture;
            Sprite sprite;
            int x, y;
        };

        b background; 
        vector < d > decor;

    public:

        Settings();

        void load();

        void pick(RenderWindow &tictactoe);

        void writing(int code);

        void start();

        void winsize(RenderWindow &tictactoe);

        void show(RenderWindow &tictactoe);

        ~Settings();
};

#endif
