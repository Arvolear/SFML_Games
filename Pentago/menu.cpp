#include "backend.hpp"
#include "bot.hpp"
#include "boardpart.hpp"
#include "winscreen.hpp"
#include "frontend.hpp"
#include "menu.hpp"

Menu::Menu()
{
    curWinSizeIndex = 0;
    front = nullptr;
    choosenMode = -1; // 0 - pvp, 1 - pvc
    whoGoesFirst = 0; // 0 - player, 1 - cpu
}
        
void Menu::resizeWindow(RenderWindow &pentago, bool mouse)
{
    if (mouse)
    {
        Vector2i pixelpos = Mouse::getPosition(pentago);
        Vector2f pos = pentago.mapPixelToCoords(pixelpos);

        if (!resize->sprite.getGlobalBounds().contains(pos.x, pos.y))
        {
            return;
        }
    }

    curWinSizeIndex = (curWinSizeIndex + 1) % 3;

    switch (curWinSizeIndex)
    {
        case 0:
            {
                pentago.setSize(Vector2u(682, 680));
                break;
            }
        
        case 1:
            {
                pentago.setSize(Vector2u(1003, 1000));
                break;
            }
        
        case 2:
            {
                pentago.setSize(Vector2u(1465, 1460));
                break;
            }
    
    }
}

void Menu::setup()
{
    menuBack = new UniversalElement();

    menuBack->texture.loadFromFile("./Textures/menu_back.png");
    menuBack->sprite.setTexture(menuBack->texture, true);
    menuBack->x = 732;
    menuBack->y = 730;
    menuBack->w = menuBack->texture.getSize().x;
    menuBack->h = menuBack->texture.getSize().y;    
    menuBack->orx = menuBack->w / 2.0;
    menuBack->ory = menuBack->h / 2.0;
    menuBack->rot = 0.0; 
    
    PVPMode = new UniversalElement();

    PVPMode->texture.loadFromFile("./Textures/pvp.png");
    PVPMode->sprite.setTexture(PVPMode->texture, true);
    PVPMode->x = 366;
    PVPMode->y = 730;
    PVPMode->w = PVPMode->texture.getSize().x;
    PVPMode->h = PVPMode->texture.getSize().y;    
    PVPMode->orx = PVPMode->w / 2.0;
    PVPMode->ory = PVPMode->h / 2.0;
    PVPMode->rot = 0.0; 
    
    PVCMode = new UniversalElement();

    PVCMode->texture.loadFromFile("./Textures/pvc.png");
    PVCMode->sprite.setTexture(PVCMode->texture, true);
    PVCMode->x = 1099;
    PVCMode->y = 730;
    PVCMode->w = PVCMode->texture.getSize().x;
    PVCMode->h = PVCMode->texture.getSize().y;    
    PVCMode->orx = PVCMode->w / 2.0;
    PVCMode->ory = PVCMode->h / 2.0;
    PVCMode->rot = 0.0; 

    resize = new UniversalElement();

    resize->texture.loadFromFile("./Textures/resize.png");
    resize->sprite.setTexture(resize->texture, true);
    resize->x = 732;
    resize->y = 1410;
    resize->w = resize->texture.getSize().x;
    resize->h = resize->texture.getSize().y;    
    resize->orx = resize->w / 2.0;
    resize->ory = resize->h / 2.0;
    resize->rot = 0.0; 
}
        
void Menu::chooseType(RenderWindow &pentago)
{
    Vector2i pixelpos = Mouse::getPosition(pentago);
    Vector2f pos = pentago.mapPixelToCoords(pixelpos);
    
    PVPMode->texture.loadFromFile("./Textures/pvp.png");
    PVPMode->sprite.setTexture(PVPMode->texture, true);

    PVCMode->texture.loadFromFile("./Textures/pvc.png");
    PVCMode->sprite.setTexture(PVCMode->texture, true);

    if (PVPMode->sprite.getGlobalBounds().contains(pos.x, pos.y))
    {
        if (choosenMode == 0)
        {
            choosenMode = -1;
            PVPMode->texture.loadFromFile("./Textures/pvp.png");
            PVPMode->sprite.setTexture(PVPMode->texture, true);

            return;
        }
        
        choosenMode = 0;
        PVPMode->texture.loadFromFile("./Textures/pvp_choosen.png");
        PVPMode->sprite.setTexture(PVPMode->texture, true);

        return;
    }
    
    if (PVCMode->sprite.getGlobalBounds().contains(pos.x, pos.y))
    {
        if (choosenMode == 1)
        {
            choosenMode = -1;
            PVCMode->texture.loadFromFile("./Textures/pvc.png");
            PVCMode->sprite.setTexture(PVCMode->texture, true);

            return;
        }
        
        choosenMode = 1;
        PVCMode->texture.loadFromFile("./Textures/pvc_choosen.png");
        PVCMode->sprite.setTexture(PVCMode->texture, true);

        return;
    }

    choosenMode = -1;
}

void Menu::start(RenderWindow &pentago)
{
    if (choosenMode == -1)
    {
        return;
    }

    if (front)
    {
        delete front;
    }

    front = new Frontend(choosenMode, whoGoesFirst);
    front->play(pentago);
}

void Menu::play()
{
    RenderWindow pentago(VideoMode(1465, 1460), "Pentago the game", 4);

    pentago.setPosition(Vector2i(200, 100));
    
    resizeWindow(pentago, false);
    pentago.setFramerateLimit(30);

    setup();

    while (pentago.isOpen())
    {
        Event event;

        while (pentago.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                pentago.close();
            }
            
            if (event.type == Event::KeyPressed)
            {
                //cout << event.key.code << endl;

                if (event.key.code == Keyboard::Escape)
                {
                    return;
                }
                
                if (event.key.code == Keyboard::Return)
                {
                    start(pentago);
                }
               
                if (event.key.code == 17)
                {
                    resizeWindow(pentago, false);
                }
            }
            
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    chooseType(pentago);
                    resizeWindow(pentago, true);
                }
            }
        }

        show(pentago);
    }
}

void Menu::show(RenderWindow &pentago)
{
    pentago.clear(Color(30, 30, 30));
    
    menuBack->sprite.setPosition(Vector2f(menuBack->x, menuBack->y));
    menuBack->sprite.setOrigin(Vector2f(menuBack->orx, menuBack->ory));

    PVPMode->sprite.setPosition(Vector2f(PVPMode->x, PVPMode->y));
    PVPMode->sprite.setOrigin(Vector2f(PVPMode->orx, PVPMode->ory));
    
    PVCMode->sprite.setPosition(Vector2f(PVCMode->x, PVCMode->y));
    PVCMode->sprite.setOrigin(Vector2f(PVCMode->orx, PVCMode->ory));
    
    resize->sprite.setPosition(Vector2f(resize->x, resize->y));
    resize->sprite.setOrigin(Vector2f(resize->orx, resize->ory));

    pentago.draw(menuBack->sprite);
    pentago.draw(PVPMode->sprite);
    pentago.draw(PVCMode->sprite);
    pentago.draw(resize->sprite);

    pentago.display();
}

Menu::~Menu()
{
    delete menuBack;
    delete PVPMode;
    delete PVCMode;
    delete resize;

    if (front)
    {
        delete front;
    }
}
