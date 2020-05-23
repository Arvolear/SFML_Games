#include "logic.h"
#include "win.h"
#include "graphics.h"

#include <cmath>

using namespace std;
using namespace sf;

Graphics::Graphics(){}

void Graphics::load()
{
    background.x = 0;
    background.y = 0;
    background.w = 1920;
    background.h = 1080;
    background.color = Color(210, 200, 170);
    background.back.setPosition(Vector2f(background.x, background.y));
    background.back.setSize(Vector2f(background.w, background.h));
    background.back.setFillColor(background.color);

    pair < int, int > s;

    s = board->size();

    int correction = 25;

    int w = 960 - (s.first / 2 * 50);
    int h = 540 - (s.second / 2 * 50);

    if (s.first % 2 == 0)
        w += correction;
    if (s.second % 2 == 0)
        h += correction;

    cells.clear();
    cells.resize(s.second);

    for (int i = 0; i < s.second; i++)
    {
        cells[i].resize(s.first);
    }

    for (int i = 0; i < s.second; i++)
    {
        for (int j = 0; j < s.first; j++)
        {
            cells[i][j].texture.loadFromFile("./images/cell.png");
            cells[i][j].sprite.setTexture(cells[i][j].texture);
            cells[i][j].scale = 1;
            cells[i][j].sprite.setOrigin(25, 25);
            cells[i][j].x = w + 50 * j;
            cells[i][j].y = h + 50 * i;
        }
    }

    decor.clear();
    decor.resize(9);

    decor[0].texture.loadFromFile("./images/grid.png");
    decor[0].sprite.setTexture(decor[0].texture);
    decor[0].x = 200;
    decor[0].y = 0;
    
    decor[1].texture.loadFromFile("./images/grid_arrow.png");
    decor[1].sprite.setTexture(decor[1].texture);
    decor[1].x = 220;
    decor[1].y = 3;
    
    decor[2].texture.loadFromFile("./images/grid_restart.png");
    decor[2].sprite.setTexture(decor[2].texture);
    decor[2].x = 450;
    decor[2].y = 12;
    
    decor[3].texture.loadFromFile("./images/grid_new_game.png");
    decor[3].sprite.setTexture(decor[3].texture);
    decor[3].x = 800;
    decor[3].y = 12;
    
    decor[4].texture.loadFromFile("./images/grid_undo.png");
    decor[4].sprite.setTexture(decor[4].texture);
    decor[4].x = 1150;
    decor[4].y = 12;
    
    decor[5].texture.loadFromFile("./images/grid_redo.png");
    decor[5].sprite.setTexture(decor[5].texture);
    decor[5].x = 1150;
    decor[5].y = 82;
    
    decor[6].texture.loadFromFile("./images/grid_center.png");
    decor[6].sprite.setTexture(decor[6].texture);
    decor[6].x = 1350;
    decor[6].y = 12;
    
    decor[7].texture.loadFromFile("./images/grid_last.png");
    decor[7].sprite.setTexture(decor[7].texture);
    decor[7].x = 1350;
    decor[7].y = 82;
    
    decor[8].texture.loadFromFile("./images/grid_cross.png");
    decor[8].sprite.setTexture(decor[8].texture);
    decor[8].x = 1550;
    decor[8].y = 0;
}

void Graphics::clean()
{
    who_win = 0;
    cells.clear();
    decor.clear();
    
    while (!undo.empty())
    {
        undo.pop();
    }
    
    while (!redo.empty())
    {
        redo.pop();
    }
    
    while (!lastcross.empty())
    {
        lastcross.pop();
    }
    
    while (!lastcircle.empty())
    {
        lastcircle.pop();
    }
}

void Graphics::restart()
{
    who_win = 0;
    board->newgame();

    while (!undo.empty())
    {
        undo.pop();
    }
    
    while (!redo.empty())
    {
        redo.pop();
    }
    
    while (!lastcross.empty())
    {
        lastcross.pop();
    }
    
    while (!lastcircle.empty())
    {
        lastcircle.pop();
    }

    load();
}

void Graphics::un()
{
    if (!undo.empty())
    {
        redo.push({undo.top().coordi, undo.top().coordj, board->whatcell(undo.top().coordi + 1, undo.top().coordj + 1)});

        board->unsign(undo.top().coordi + 1, undo.top().coordj + 1);

        cells[undo.top().coordi][undo.top().coordj].texture.loadFromFile("./images/cell.png");
        cells[undo.top().coordi][undo.top().coordj].sprite.setTexture(cells[undo.top().coordi][undo.top().coordj].texture);

        undo.pop();

        int t = board->turn();

        if (t == 1)
        {
            lastcross.pop();

            decor[8].texture.loadFromFile("./images/grid_cross.png");
            decor[8].sprite.setTexture(decor[8].texture);
        }

        if (t == 2)
        {
            lastcircle.pop();

            decor[8].texture.loadFromFile("./images/grid_circle.png");
            decor[8].sprite.setTexture(decor[8].texture);
        }
    }
}

void Graphics::re()
{
    if (!redo.empty())
    {
        undo.push({redo.top().coordi, redo.top().coordj});
        
        lastcross.push({redo.top().coordi, redo.top().coordj});
        lastcircle.push({redo.top().coordi, redo.top().coordj});

        if (redo.top().xoro == 1)
        {
            board->sign(redo.top().coordi + 1, redo.top().coordj + 1);

            cells[redo.top().coordi][redo.top().coordj].texture.loadFromFile("./images/cross.png");
            cells[redo.top().coordi][redo.top().coordj].sprite.setTexture(cells[redo.top().coordi][redo.top().coordj].texture);
           
        }
        
        if (redo.top().xoro == 2)
        {
            board->sign(redo.top().coordi + 1, redo.top().coordj + 1);

            cells[redo.top().coordi][redo.top().coordj].texture.loadFromFile("./images/circle.png");
            cells[redo.top().coordi][redo.top().coordj].sprite.setTexture(cells[redo.top().coordi][redo.top().coordj].texture);

        }
        
        int t = board->turn();

        if (t == 1)
        {
            lastcross.pop();

            decor[8].texture.loadFromFile("./images/grid_cross.png");
            decor[8].sprite.setTexture(decor[8].texture);
        }

        if (t == 2)
        {
            lastcircle.pop();

            decor[8].texture.loadFromFile("./images/grid_circle.png");
            decor[8].sprite.setTexture(decor[8].texture);
        }

        redo.pop();
    }
}

void Graphics::zoomin()
{
    pair < int, int > s;

    s = board->size();
    
    double min_dis = 999999999;
    int centerx;
    int centery;
    int centeri;
    int centerj;

    for (int i = 0; i < s.second; i++)
    {
        for (int j = 0; j < s.first; j++)
        {
            double d = sqrt((cells[i][j].x - 960) * (cells[i][j].x - 960) + (cells[i][j].y - 540) * (cells[i][j].y - 540));

            if (d < min_dis)
            {
                min_dis = d;
                centeri = i;
                centerj = j;
                centery = cells[i][j].y;
                centerx = cells[i][j].x;
            }
        }
    }

    //cout << centerx << ' ' << centery << endl;

    for (int i = 0; i < s.second; i++)
    {
        for (int j = 0; j < s.first; j++)
        {
            if (cells[i][j].scale < 10 && cells[i][j].scale >= 1)
            {
                cells[i][j].scale += 1;
            }

            if (cells[i][j].scale < 1)
            {
                cells[i][j].scale *= 2;
            }


            int w = centerx - (centerj * 50 * cells[i][j].scale);
            int h = centery - (centeri * 50 * cells[i][j].scale);

            cells[i][j].x = w + 50 * j * cells[i][j].scale;
            cells[i][j].y = h + 50 * i * cells[i][j].scale;
        }
    }
}

void Graphics::zoomout()
{
    pair < int, int > s;

    s = board->size();
    
    double min_dis = 999999999;
    int centerx;
    int centery;
    int centeri;
    int centerj;

    for (int i = 0; i < s.second; i++)
    {
        for (int j = 0; j < s.first; j++)
        {
            double d = sqrt((cells[i][j].x - 960) * (cells[i][j].x - 960) + (cells[i][j].y - 540) * (cells[i][j].y - 540));

            if (d < min_dis)
            {
                min_dis = d;
                centeri = i;
                centerj = j;
                centery = cells[i][j].y;
                centerx = cells[i][j].x;
            }
        }
    }

    //cout << centerx << ' ' << centery << endl;

    for (int i = 0; i < s.second; i++)
    {
        for (int j = 0; j < s.first; j++)
        {
            if (cells[i][j].scale > 1)
            {
                cells[i][j].scale -= 1;
            }
            
            if (cells[i][j].scale == 1)
            {
                cells[i][j].scale /= 2;
            }

            int w = centerx - (centerj * 50 * cells[i][j].scale);
            int h = centery - (centeri * 50 * cells[i][j].scale);

            cells[i][j].x = w + 50 * j * cells[i][j].scale;
            cells[i][j].y = h + 50 * i * cells[i][j].scale;
            
        }
    }
}

void Graphics::centerize()
{
    pair < int, int > s = board->size();

    double cx = 960 - s.first * 50 * cells[0][0].scale / 2;
    double cy = 540 - s.second * 50 * cells[0][0].scale / 2;

    for (int i = 0; i < s.first; i++)
    {
        for (int j = 0; j < s.second; j++)
        {
            cells[i][j].x = cx + 50 * j * cells[i][j].scale;
            cells[i][j].y = cy + 50 * i * cells[i][j].scale;
        }
    }
}

void Graphics::lastone()
{
    pair < int, int > s = board->size();

    int coordi = -1;
    int coordj = -1;
    int coordx = -1;
    int coordy = -1;

    int t = board->turn();

    if (!lastcross.empty() && t == 1)
    {
        coordi = lastcross.top().coordi;
        coordj = lastcross.top().coordj;
        
        cells[coordi][coordj].x = 960;
        cells[coordi][coordj].y = 540;

        coordx = cells[coordi][coordj].x;
        coordy = cells[coordi][coordj].y;
    }
    
    if (!lastcircle.empty() && t == 2)
    {
        coordi = lastcircle.top().coordi;
        coordj = lastcircle.top().coordj;
        
        cells[coordi][coordj].x = 960;
        cells[coordi][coordj].y = 540;

        coordx = cells[coordi][coordj].x;
        coordy = cells[coordi][coordj].y;
    }

    if (coordi != -1)
    {
        for (int i = 0; i < s.second; i++)
        {
            for (int j = 0; j < s.first; j++)
            {
                int w = coordx - (coordj * 50 * cells[i][j].scale);
                int h = coordy - (coordi * 50 * cells[i][j].scale);

                cells[i][j].x = w + 50 * j * cells[i][j].scale;
                cells[i][j].y = h + 50 * i * cells[i][j].scale;
            }
        }
    }
}

int Graphics::button(RenderWindow &tictactoe)
{
    Vector2i pixelpos = Mouse::getPosition(tictactoe);
    Vector2f pos = tictactoe.mapPixelToCoords(pixelpos);

    if (decor[1].sprite.getGlobalBounds().contains(pos.x, pos.y))
    {
        clean();
        return 2;
    }
    if (decor[2].sprite.getGlobalBounds().contains(pos.x, pos.y))
    {
        restart();
        return 1;
    }
    if (decor[3].sprite.getGlobalBounds().contains(pos.x, pos.y))
    {
        clean();
        return 2;
    }
    if (decor[4].sprite.getGlobalBounds().contains(pos.x, pos.y))
    {
        un();
        return 1;
    }
    if (decor[5].sprite.getGlobalBounds().contains(pos.x, pos.y))
    {
        re();
        return 1;
    }
    if (decor[6].sprite.getGlobalBounds().contains(pos.x, pos.y))
    {
        centerize();
        return 1;
    }
    if (decor[7].sprite.getGlobalBounds().contains(pos.x, pos.y))
    {
        lastone();
        return 1;
    }

    return 0;
}

void Graphics::action(RenderWindow &tictactoe)
{
    Vector2i pixelpos = Mouse::getPosition(tictactoe);
    Vector2f pos = tictactoe.mapPixelToCoords(pixelpos);

    if (act.mx == 0 && act.my == 0)
    {
        act.mx = pos.x;
        act.my = pos.y;
    }

    if (act._mx != 0 && act._my != 0)
    {
        double rx = pos.x - act._mx;
        double ry = pos.y - act._my;

        //cout << rx << ' ' << ry << endl;

        if (rx > 1 || ry > 1 || rx < -1 || ry < -1)
        {
            pair < int, int > s;

            s = board->size();

            for (int i = 0; i < s.second; i++)
            {
                for (int j = 0; j < s.first; j++)
                {
                    cells[i][j].x += rx;
                    cells[i][j].y += ry;
                }
            }
        }
    }

    act._mx = pos.x;
    act._my = pos.y;
}

void Graphics::stop(RenderWindow &tictactoe)
{
    Vector2i pixelpos = Mouse::getPosition(tictactoe);
    Vector2f pos = tictactoe.mapPixelToCoords(pixelpos);
                
            
    pair < int, int > s;

    s = board->size();

    if (pos.x + 5 >= act.mx && pos.x - 5 <= act.mx && pos.y + 5 >= act.my && pos.y - 5 <= act.my)
    {
        for (int i = 0; i < s.second; i++)
        {
            for (int j = 0; j < s.first; j++)
            {
                if (cells[i][j].sprite.getGlobalBounds().contains(act.mx, act.my) && !decor[0].sprite.getGlobalBounds().contains(pos.x, pos.y))
                {
                    int t = board->turn();

                    if (board->sign(i + 1, j + 1))
                    {
                        board->sign(i + 1, j + 1);
                        undo.push({i, j});
                        
                        while (!redo.empty())
                        {
                            redo.pop();
                        }

                        if (t == 1)
                        {
                            lastcross.push({i, j});

                            cells[i][j].texture.loadFromFile("./images/cross.png");

                            cells[i][j].sprite.setTexture(cells[i][j].texture);
                            
                            decor[8].texture.loadFromFile("./images/grid_circle.png");
                            decor[8].sprite.setTexture(decor[8].texture);
                        }

                        if (t == 2)
                        {
                            lastcircle.push({i, j});

                            cells[i][j].texture.loadFromFile("./images/circle.png");

                            cells[i][j].sprite.setTexture(cells[i][j].texture);
                            
                            decor[8].texture.loadFromFile("./images/grid_cross.png");
                            decor[8].sprite.setTexture(decor[8].texture);
                    
                        }
                    }

                 //   board->display();

                    who_win = board->iswin(i + 1, j + 1);

                    if (who_win >= 1)
                    {
                        winblock->load(who_win);
                    }
    
                    break;
                }
            }
        }
    }

    act.mx = 0;
    act.my = 0;
    act._mx = 0;
    act._my = 0;
}

void Graphics::start(RenderWindow &tictactoe, int width, int height, int amtowin)
{
    board = new Logic(width, height, amtowin);

    winblock = new Win();

    load();

    while (tictactoe.isOpen())
    {
        Event event;

        while (tictactoe.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                tictactoe.close();
                return;
            }

            if (Mouse::isButtonPressed(Mouse::Left))
            {
                if (!who_win)
                {
                    int m = 0;
                    if (event.type == Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == Mouse::Left)
                        {
                            m = button(tictactoe);
                        }
                    }

                    if (m == 2)
                        return;

                    if (!m)
                    {
                        action(tictactoe);
                    }
                }
                else
                {
                    int ans = 0;
                    if (event.type == Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == Mouse::Left)
                        {
                            ans = winblock->click(tictactoe);
                        }
                    }

                    if (ans == 1)
                    {
                        restart();
                    }
                    if (ans == 2)
                    {
                        clean();
                        return;
                    }
                }
            }

            if (!Mouse::isButtonPressed(Mouse::Left))
            {
                if (!who_win)
                {
                    stop(tictactoe);
                }
            }

            if (event.type == Event::KeyPressed)
            {
                //cout << event.key.code << endl;
                
                if (event.key.code == 2)
                {
                    centerize();
                }
                
                if (event.key.code == 11)
                {
                    lastone();
                }

                if (event.key.code == 13)
                {
                    clean();
                    return;
                }

                if (event.key.code == 17)
                {
                    restart();
                }
                
                if (!who_win)
                {
                    if (event.key.code == 24)
                    {
                        re();
                    }
    
                    if (event.key.code == 20)
                    {
                        un();
                    }

                    if (event.key.code == 73)
                    {
                        zoomin();
                    }

                    if (event.key.code == 74)
                    {
                        zoomout();
                    }
                }
            }
        }

        show(tictactoe);
    }
}

void Graphics::show(RenderWindow &tictactoe)
{
    tictactoe.clear();
   
    tictactoe.draw(background.back);

    pair < int, int > s;

    s = board->size();

    for (int i = 0; i < s.second; i++)
    {
        for (int j = 0; j < s.first; j++)
        {
            cells[i][j].sprite.setPosition(Vector2f(cells[i][j].x, cells[i][j].y));
            cells[i][j].sprite.setScale(cells[i][j].scale, cells[i][j].scale);

            tictactoe.draw(cells[i][j].sprite);
            
        }
    }

    for (int i = 0; i < 9; i++)
    {
        decor[i].sprite.setPosition(Vector2f(decor[i].x, decor[i].y));
        tictactoe.draw(decor[i].sprite);
    }

    if (who_win)
    {
        winblock->draw(tictactoe);
    }

    tictactoe.display();
}

Graphics::~Graphics()
{
    delete board;
    delete winblock;
}

