#ifndef WIN_H
#define WIN_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Win
{
    private:

        struct b
        {
            Texture texture;
            Sprite sprite;
            int x, y;
        };

        struct e
        {
            Texture texture;
            Sprite sprite;
            int x, y;
        };

        struct t
        {
            Font font;
            Text text;
            int chsize;
            int x, y;
            string s = "";
            Color c;
        };

        b background;

        vector < e > elements;

        t texting;

    public:

        Win();

        void load(int who_win);

        int click(RenderWindow &tictactoe);

        void draw(RenderWindow &tictactoe);

        ~Win();
};

#endif
