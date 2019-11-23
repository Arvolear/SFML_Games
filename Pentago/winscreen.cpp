#include "boardpart.hpp"
#include "winscreen.hpp"

WinScreen::WinScreen(){}

void WinScreen::setup(int whoWins)
{
    winSign = new WinSign();
    winSign->font.loadFromFile("./Fonts/FreeMonoBold.ttf");
    winSign->text.setFont(winSign->font);
    winSign->chsize = 120;
    winSign->color1 = Color(240, 240, 240);
    winSign->color2 = Color(203, 24, 24);
                
    winSignDupl = new WinSign();
    
    winSignDupl->font.loadFromFile("./Fonts/FreeMonoBold.ttf");
    winSignDupl->text.setFont(winSignDupl->font);
    winSignDupl->chsize = 120;
    winSignDupl->color1 = Color(240, 240, 240);
    winSignDupl->color2 = Color(203, 24, 24);

    switch (whoWins)
    {
        case 4:
            {
                winSign->x1 = 507;
                winSign->y1 = 230;
                winSign->x2 = 511;
                winSign->y2 = 234;

                winSignDupl->x1 = 565;
                winSignDupl->y1 = 345;
                winSignDupl->x2 = 569;
                winSignDupl->y2 = 349;

                winSign->sign = "It's a";
                winSignDupl->sign = "draw!";

                break;
            }

        case 3:
            {
                winSign->x1 = 415;
                winSign->y1 = 260;
                winSign->x2 = 419;
                winSign->y2 = 264;

                winSign->sign = "CPU wins!";
                break;
            }

        default:
            {
                winSign->x1 = 445;
                winSign->y1 = 230;
                winSign->x2 = 449;
                winSign->y2 = 234;

                winSignDupl->x1 = 570;
                winSignDupl->y1 = 345;
                winSignDupl->x2 = 574;
                winSignDupl->y2 = 349;

                winSign->sign = "Player " + to_string(whoWins);
                winSignDupl->sign = "wins!";

                break;
            }
    } 

    //winSign->text

    UniversalElement *background = new UniversalElement();
    background->texture.loadFromFile("./Textures/background.png");
    background->sprite.setTexture(background->texture, true);
    background->x = 733;
    background->y = 730;
    background->w = background->texture.getSize().x;
    background->h = background->texture.getSize().y;    
    background->orx = background->w / 2.0;
    background->ory = background->h / 2.0;
    background->rot = 0.0;
    elements.push_back(background);

    UniversalElement *winBack = new UniversalElement();
    winBack->texture.loadFromFile("./Textures/win_back.png");
    winBack->sprite.setTexture(winBack->texture, true);
    winBack->x = 733;
    winBack->y = 730;
    winBack->w = winBack->texture.getSize().x;
    winBack->h = winBack->texture.getSize().y;    
    winBack->orx = winBack->w / 2.0;
    winBack->ory = winBack->h / 2.0;
    winBack->rot = 0.0;
    elements.push_back(winBack);

    UniversalElement *restart = new UniversalElement();
    restart->texture.loadFromFile("./Textures/restart.png");
    restart->sprite.setTexture(restart->texture, true);
    restart->x = 738;
    restart->y = 800;
    restart->w = restart->texture.getSize().x;
    restart->h = restart->texture.getSize().y;    
    restart->orx = restart->w / 2.0;
    restart->ory = restart->h / 2.0;
    restart->rot = 0.0;
    elements.push_back(restart);
}

int WinScreen::click(RenderWindow &pentago)
{
    Vector2i pixelpos = Mouse::getPosition(pentago);
    Vector2f pos = pentago.mapPixelToCoords(pixelpos);

    if (elements[2]->sprite.getGlobalBounds().contains(pos.x, pos.y))
    {
        return 1;
    }

    if (elements[1]->sprite.getGlobalBounds().contains(pos.x, pos.y))
    {
        return 0;
    }

    return -1;
}

void WinScreen::show(RenderWindow &pentago)
{
    for (int i = 0; i < elements.size(); i++)
    {
        elements[i]->sprite.setPosition(Vector2f(elements[i]->x, elements[i]->y));
        elements[i]->sprite.setOrigin(Vector2f(elements[i]->orx, elements[i]->ory));

        pentago.draw(elements[i]->sprite);
    }

    winSign->text.setPosition(Vector2f(winSign->x1, winSign->y1));
    winSign->text.setCharacterSize(winSign->chsize);
    winSign->text.setColor(winSign->color1);
    winSign->text.setString(winSign->sign);

    pentago.draw(winSign->text);

    winSign->text.setPosition(Vector2f(winSign->x2, winSign->y2));
    winSign->text.setColor(winSign->color2);

    pentago.draw(winSign->text);

    winSignDupl->text.setPosition(Vector2f(winSignDupl->x1, winSignDupl->y1));
    winSignDupl->text.setCharacterSize(winSignDupl->chsize);
    winSignDupl->text.setColor(winSignDupl->color1);
    winSignDupl->text.setString(winSignDupl->sign);

    pentago.draw(winSignDupl->text);

    winSignDupl->text.setPosition(Vector2f(winSignDupl->x2, winSignDupl->y2));
    winSignDupl->text.setColor(winSignDupl->color2);

    pentago.draw(winSignDupl->text);
}

WinScreen::~WinScreen()
{
    for (int i = 0; i < elements.size(); i++)
    {
        delete elements[i];
    }
}
