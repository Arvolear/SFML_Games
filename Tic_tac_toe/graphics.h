#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <vector>
#include <stack>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Graphics
{
    private:
        Logic *board;

        Win *winblock;

        int who_win = 0;

        struct a
        {
            double mx = 0;
            double my = 0;
            double _mx = 0;
            double _my = 0;
        };

        struct b
        {
            RectangleShape back;
            Color color;
            int w, h;
            int x, y;
        };

        struct c
        {
            Texture texture;
            Sprite sprite;
            double scale;
            double x, y;
        };

        struct d
        {
            bool mouseclick = false;
            Texture texture;
            Sprite sprite;
            int x, y;
        };

        struct u
        {
            int coordi, coordj;
        };

        struct r
        {
            int coordi, coordj;
            int xoro;
        };

        a act;
        
        b background;
        
        vector < vector < c > > cells;
        vector < d > decor;
        
        stack < u > undo;
        stack < r > redo;

        stack < u > lastcross;
        stack < u > lastcircle;

    public:

        Graphics();

        void load();

        void clean();

        void restart();

        void un();

        void re();

        void zoomin();

        void zoomout();

        void centerize();

        void lastone();

        int button(RenderWindow &tictactoe);

        void action(RenderWindow &tictactoe);
        
        void stop(RenderWindow &tictactoe);

        void start(RenderWindow &tictactoe, int width, int height, int amtowin);

        void show(RenderWindow &tictactoe);

        ~Graphics();
};

#endif
