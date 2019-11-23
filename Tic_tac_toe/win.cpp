#include "win.h"

using namespace std;
using namespace sf;

Win::Win(){};

void Win::load(int who_win)
{
    background.texture.loadFromFile("./images/win_back.png");
    background.sprite.setTexture(background.texture);
    background.x = 0;
    background.y = 0;
    background.sprite.setPosition(Vector2f(background.x, background.y));

    elements.clear();
    elements.resize(3);

    elements[0].texture.loadFromFile("./images/win_bound.png");
    elements[0].sprite.setTexture(elements[0].texture);
    elements[0].sprite.setOrigin(300, 400);
    elements[0].x = 960;
    elements[0].y = 540;
    elements[0].sprite.setPosition(Vector2f(elements[0].x, elements[0].y));

    elements[1].texture.loadFromFile("./images/win_restart.png");
    elements[1].sprite.setTexture(elements[1].texture);
    elements[1].sprite.setOrigin(200, 100);
    elements[1].x = 960;
    elements[1].y = 590;
    elements[1].sprite.setPosition(Vector2f(elements[1].x, elements[1].y));

    elements[2].texture.loadFromFile("./images/win_new_game.png");
    elements[2].sprite.setTexture(elements[2].texture);
    elements[2].sprite.setOrigin(200, 100);
    elements[2].x = 960;
    elements[2].y = 815;
    elements[2].sprite.setPosition(Vector2f(elements[2].x, elements[2].y));

    srand(time(0));

    if (who_win == 1)
    {
        texting.s = "Crosses win!";
        texting.c = Color(235, 28, 36);

        texting.x = 745;
        texting.y = 240;
    }
    if (who_win == 2)
    {
        texting.s = "Circles win!";
        texting.c = Color(0, 128, 0);
    
        texting.x = 765;
        texting.y = 240;
    }
    if (who_win == 3)
    {
        texting.s = "It's a draw!";
        texting.c = Color(24, 130, 250);
        texting.x = 755;
        texting.y = 240;
    }

    if (texting.text.getString() != texting.s)
    {
        texting.font.loadFromFile("./fonts/Vertigo.ttf");
        texting.text.setFont(texting.font);
        texting.chsize = 144;

        texting.text.setPosition(Vector2f(texting.x, texting.y));
        texting.text.setString(texting.s);
        texting.text.setCharacterSize(texting.chsize);
        texting.text.setColor(texting.c);
    }
}

int Win::click(RenderWindow &tictactoe)
{
    Vector2i pixelpos = Mouse::getPosition(tictactoe);
    Vector2f pos = tictactoe.mapPixelToCoords(pixelpos);

    for (int i = 1; i < 3; i++)
    {
        if (elements[i].sprite.getGlobalBounds().contains(pos.x, pos.y))
        {
            return i;
        }
    }

    if (elements[0].sprite.getGlobalBounds().contains(pos.x, pos.y))
    {
        return 0;
    }

    return -1;
}

void Win::draw(RenderWindow &tictactoe)
{
    tictactoe.draw(background.sprite);
   
    for (int i = 0; i < 3; i++)
    {
        tictactoe.draw(elements[i].sprite);
    }
    
    tictactoe.draw(texting.text);
}

Win::~Win(){};
