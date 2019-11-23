#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <chrono>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

struct UniversalElement
{
    Texture texture;
    Sprite sprite;

    double x, y;
    double w, h;
    double orx, ory;

    double rot;
    double dotAngle;
};

class BoardPart
{
    private:
        int centerX, centerY;
        int width, height;
        bool isChoosen;
        bool canChangeSprites;

        UniversalElement *backPart;

        vector < vector < UniversalElement* > > balls;

    public:
        BoardPart(int lines, int rows);

        void setup(int centerX, int centerY);

        void setDot(int line, int row, int whosTurn);

        void choose();
        void unChoose();

        void rotate(int angle, int part);

        void draw(RenderWindow &pentago);

        Sprite getPartSprite();
        Sprite getBallSprite(int line, int row);
        pair < int, int > getSize();
        bool getIsChoosen();
        bool getCanChangeSprites();

        ~BoardPart();
};
