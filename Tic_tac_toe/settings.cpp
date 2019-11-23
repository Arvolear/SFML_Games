#include "logic.h"
#include "win.h"
#include "graphics.h"
#include "settings.h"

using namespace std;
using namespace sf;

Settings::Settings(){}

void Settings::load()
{
    background.x = 0;
    background.y = 0;
    background.w = 1920;
    background.h = 1080;
    background.color = Color(210, 200, 170);
    background.back.setPosition(Vector2f(background.x, background.y));
    background.back.setSize(Vector2f(background.w, background.h));
    background.back.setFillColor(background.color);

    decor.resize(4);
    
    for (int i = 0; i < 3; i++)
    {
        decor[i].font.loadFromFile("./fonts/Vertigo.ttf");
        decor[i].tinside.setFont(decor[i].font);
        decor[i].toutside.setFont(decor[i].font);
        decor[i].chsize = 80;
        decor[i].tinside.setCharacterSize(decor[i].chsize);
        decor[i].toutside.setCharacterSize(decor[i].chsize);
        decor[i].tinx = 370 + 550 * i;
        decor[i].tiny = 495;
        decor[i].toutx = 330 + 550 * i;
        decor[i].touty = 340;
        decor[i].inc = Color(0, 128, 0);
        decor[i].outc = Color(24, 130, 250);
        decor[i].tinside.setPosition(Vector2f(decor[i].tinx, decor[i].tiny));
        decor[i].toutside.setPosition(Vector2f(decor[i].toutx, decor[i].touty));
        decor[i].tinside.setColor(decor[i].inc);
        decor[i].toutside.setColor(decor[i].outc);

        decor[i].tinside.setString(decor[i].sin);



        decor[i].texture.loadFromFile("./images/set.png");
        decor[i].sprite.setTexture(decor[i].texture);
        decor[i].sprite.setOrigin(200, 100);
        decor[i].x = 400 + 550 * i;
        decor[i].y = 540;
    }

    decor[0].sout = "Width:\n";
    decor[1].sout = "Height:\n";
    decor[2].sout = "Length:\n";

    decor[0].toutside.setString(decor[0].sout);
    decor[1].toutside.setString(decor[1].sout);
    decor[2].toutside.setString(decor[2].sout);

    decor[3].font.loadFromFile("./fonts/Vertigo.ttf");
    decor[3].toutside.setFont(decor[3].font);
    decor[3].sout = "Choose ingame settings!";
    decor[3].chsize = 150;
    decor[3].toutx = 520;
    decor[3].touty = 70;
    decor[3].outc = Color(24, 130, 250);
    decor[3].toutside.setString(decor[3].sout);
    decor[3].toutside.setCharacterSize(decor[3].chsize);
    decor[3].toutside.setPosition(Vector2f(decor[3].toutx, decor[3].touty));
    decor[3].toutside.setColor(decor[3].outc);

    decor[3].texture.loadFromFile("./images/start.png");
    decor[3].sprite.setTexture(decor[3].texture);
    decor[3].sprite.setOrigin(200, 100);
    decor[3].x = 950;
    decor[3].y = 860;
}

void Settings::pick(RenderWindow &tictactoe)
{
    Vector2i pixelpos = Mouse::getPosition(tictactoe);
    Vector2f pos = tictactoe.mapPixelToCoords(pixelpos);

    if (decor[3].sprite.getGlobalBounds().contains(pos.x, pos.y) && isstart == true)
    {
    
        graphics = new Graphics();
        graphics->start(tictactoe, width, height, amtowin);
        
        delete graphics;
        return;
    }
            
    for (int i = 0; i < 3; i++)
    {
        decor[i].choosen = false;
    }

    for (int i = 0; i < 3; i++)
    {
        if (decor[i].sprite.getGlobalBounds().contains(Vector2f(pos.x, pos.y)))
        {
            decor[i].choosen = true;

            for (int j = 0; j < 3; j++)
            {
                if (j != i)
                {
                    decor[j].choosen = false;
                }
            }
        }

        if (decor[i].choosen == true)
        {
            decor[i].texture.loadFromFile("./images/set_picked.png");
            decor[i].sprite.setTexture(decor[i].texture);
        }
        else
        {
            decor[i].texture.loadFromFile("./images/set.png");
            decor[i].sprite.setTexture(decor[i].texture);
        }
    }
}

void Settings::writing(int code)
{
    for (int i = 0; i < 3; i++)
    {
        if (decor[i].choosen == true)
        {
            if (code == 59)
            {
                if (!decor[i].sin.empty())
                {
                    decor[i].sin.pop_back();
                }
            }
            else
            {
                int chnum = code + 22;
                decor[i].sin += char(chnum);
            }
            
            decor[i].tinside.setString(decor[i].sin);
        }

        int true_number = 0;
        int power = 1;

        for (int j = decor[i].sin.length() - 1; j >= 0; j--)
        {
            true_number += int(decor[i].sin[j] - '0') * power;
            power *= 10;
        }

        if (true_number > 99)
        {
            true_number = 99;
            decor[i].sin = "99";
            decor[i].tinside.setString(decor[i].sin);
        }

        if (i == 0)
        {
            width = true_number;
        }
        else if (i == 1)
        {
            height = true_number;
        }
        else if (i == 2)
        {
           amtowin = true_number; 
        }

        Color c;
    
        if ((height * width >= amtowin * 2 - 1 && (height >= amtowin || width >= amtowin)) && !decor[i].sin.empty())
        {
            isstart = true;
            c = Color(0, 128, 0);
        }
        else
        {
            isstart = false;
            c = Color(235, 28, 36);
        }

        for (int i = 0; i < 3; i++)
        {
            decor[i].inc = c;
            decor[i].tinside.setColor(decor[i].inc);
        }
    }
}

void Settings::winsize(RenderWindow &tictactoe)
{
    if (zoom == -3)
    {
        tictactoe.setSize(Vector2u(720, 480)); 
    }
    if (zoom == -2)
    {
        tictactoe.setSize(Vector2u(1066, 600)); 
    }
    if (zoom == -1)
    {
        tictactoe.setSize(Vector2u(1366, 768)); 
    }
    if (zoom == 0)
    {
        tictactoe.setSize(Vector2u(1600, 900)); 
    }
    if (zoom == 1)
    {
        tictactoe.setSize(Vector2u(1920, 1080)); 
    }
    if (zoom == 2)
    {
        tictactoe.setSize(Vector2u(2560, 1440)); 
    }
    if (zoom == 3)
    {
        tictactoe.setSize(Vector2u(3000, 1688)); 
    }
}

void Settings::start()
{
    RenderWindow tictactoe(VideoMode(1920, 1080), "Tic-Tac-Toe", 4);

    tictactoe.setFramerateLimit(60);

    load();

    while(tictactoe.isOpen())
    {
        Event event;
        while (tictactoe.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                tictactoe.close();
                return;
            }

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    pick(tictactoe);
                }
            }

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code >= 26 && event.key.code <= 35 || event.key.code == 59)
                {
                    writing(event.key.code);
                }

                if (event.key.code == 18)
                {
                    if (isstart)
                    {
                        graphics = new Graphics();
                        graphics->start(tictactoe, width, height, amtowin);

                        delete graphics;
                    }
                }

                if (event.key.code == 46)
                {
                    if (zoom > -3)
                    {
                        zoom--;
                        
                        winsize(tictactoe);
                    }
                }

                if (event.key.code == 47)
                {
                    if (zoom < 3)
                    {
                        zoom++;

                        winsize(tictactoe);
                    }
                }
            }
        }

        show(tictactoe);
    }
}

void Settings::show(RenderWindow &tictactoe)
{
    tictactoe.clear();

    tictactoe.draw(background.back);

    for (int i = 0; i < 3; i++)
    {
        decor[i].sprite.setPosition(Vector2f(decor[i].x, decor[i].y));

        tictactoe.draw(decor[i].sprite);
        
        tictactoe.draw(decor[i].toutside);
        tictactoe.draw(decor[i].tinside);

    }

    tictactoe.draw(decor[3].toutside);
    
    decor[3].sprite.setPosition(Vector2f(decor[3].x, decor[3].y));
    
    if (isstart == true)
    {
        tictactoe.draw(decor[3].sprite);
    }

    tictactoe.display();
}

Settings::~Settings(){}
