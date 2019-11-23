#include "backend.hpp"
#include "bot.hpp"
#include "boardpart.hpp"
#include "winscreen.hpp"
#include "frontend.hpp"

Frontend::Frontend(int type, int whoGoesFirst)
{
    gameType = type;
    whoWins = 0;
    hideWinScreen = false;
    hideWinScreenHelper = true;

    boardParts = 4; 

    rotation = nullptr;
    winScreen = nullptr;
}

void Frontend::setup()
{
    backend = new Backend();
    bot = new Bot(2, backend->getAmountToWin()); //black

    board.resize(2);
    
    back = new UniversalElement();
    back->texture.loadFromFile("./Textures/back.png");
    back->sprite.setTexture(back->texture, true);
    back->x = 100;
    back->y = 90;
    back->w = back->texture.getSize().x;
    back->h = back->texture.getSize().y;    
    back->orx = back->w / 2.0;
    back->ory = back->h / 2.0;
    back->rot = 0.0;

    turnLeft = new UniversalElement();
    turnLeft->texture.loadFromFile("./Textures/turn_left.png");
    turnLeft->sprite.setTexture(turnLeft->texture, true);
    turnLeft->x = 120;
    turnLeft->y = 730;
    turnLeft->w = turnLeft->texture.getSize().x;
    turnLeft->h = turnLeft->texture.getSize().y;    
    turnLeft->orx = turnLeft->w / 2.0;
    turnLeft->ory = turnLeft->h / 2.0;
    turnLeft->rot = 0.0;
    
    turnRight = new UniversalElement();
    turnRight->texture.loadFromFile("./Textures/turn_right.png");
    turnRight->sprite.setTexture(turnRight->texture, true);
    turnRight->x = 1345;
    turnRight->y = 730;
    turnRight->w = turnRight->texture.getSize().x;
    turnRight->h = turnRight->texture.getSize().y;    
    turnRight->orx = turnRight->w / 2.0;
    turnRight->ory = turnRight->h / 2.0;
    turnRight->rot = 0.0;

    ballTurn = new UniversalElement();
    ballTurn->texture.loadFromFile("./Textures/ball0.png");
    ballTurn->sprite.setTexture(ballTurn->texture, true);
    ballTurn->x = 730;
    ballTurn->y = 100;
    ballTurn->w = ballTurn->texture.getSize().x;
    ballTurn->h = ballTurn->texture.getSize().y;    
    ballTurn->orx = ballTurn->w / 2.0;
    ballTurn->ory = ballTurn->h / 2.0;
    ballTurn->rot = 0.0;


    boardBack = new UniversalElement();
    boardBack->texture.loadFromFile("./Textures/board_back.png");
    boardBack->sprite.setTexture(boardBack->texture, true);
    boardBack->x = 730;
    boardBack->y = 730;
    boardBack->w = boardBack->texture.getSize().x;
    boardBack->h = boardBack->texture.getSize().y;    
    boardBack->orx = boardBack->w / 2.0;
    boardBack->ory = boardBack->h / 2.0;
    boardBack->rot = 0.0;

    for (int i = 0; i < boardParts / 2; i++)
    {
        for (int j = 0; j < boardParts / 2; j++)
        {
            board[i].push_back(new BoardPart(3, 3));

            board[i][j]->setup(500 + j * 460, 500 + i * 460);
        }
    }
}

void Frontend::pickBall(RenderWindow &pentago)
{
    Vector2i pixelpos = Mouse::getPosition(pentago);
    Vector2f pos = pentago.mapPixelToCoords(pixelpos);

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            if (!board[i][j]->getCanChangeSprites())
            {
                return;
            }
        }
    }

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            pair < int, int > ballsAmount = board[i][j]->getSize();

            for (int k = 0; k < ballsAmount.first; k++)
            {
                for (int l = 0; l < ballsAmount.second; l++)
                {
                    Sprite localBall = board[i][j]->getBallSprite(k, l);

                    if (localBall.getGlobalBounds().contains(pos.x, pos.y))
                    {
                        backend->setDot(k + i * 3, l + j * 3);
                        updateFront();
                        show(pentago);
                        
                        //backend->draw();
                    }
                }
            }
        }
    }   

    return;
}

void Frontend::pickPart(RenderWindow &pentago)
{
    Vector2i pixelpos = Mouse::getPosition(pentago);
    Vector2f pos = pentago.mapPixelToCoords(pixelpos);

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            bool notChoose = board[i][j]->getIsChoosen();

            board[i][j]->unChoose();

            Sprite localPart = board[i][j]->getPartSprite();

            if (localPart.getGlobalBounds().contains(pos.x, pos.y))
            {
                if (!notChoose)
                {
                    board[i][j]->choose();
                }
            }
        }
    }
}

bool Frontend::onClick(RenderWindow &pentago)
{
    Vector2i pixelpos = Mouse::getPosition(pentago);
    Vector2f pos = pentago.mapPixelToCoords(pixelpos);
    
    if (back->sprite.getGlobalBounds().contains(pos.x, pos.y))
    {
        return true;
    }

    if (turnLeft->sprite.getGlobalBounds().contains(pos.x, pos.y))
    {
        rotateChoosenPart(71);
    }
    
    if (turnRight->sprite.getGlobalBounds().contains(pos.x, pos.y))
    {
        rotateChoosenPart(72);
    }

    return false; 
}

void Frontend::rotateChoosenPart(int code)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            if (board[i][j]->getIsChoosen())
            {
                board[i][j]->unChoose();

                switch (code)
                {
                    case 71: //counterclockwise
                        {
                            if (rotation)
                            {
                                if (rotation->joinable())
                                {
                                    rotation->join();
                                }
                            }

                            delete rotation;
                            rotation = new thread(&BoardPart::rotate, board[i][j], -90, 1 + i * 2 + j);

                            backend->rotate(i * 2 + j + 1, -1);
                            break;
                        }

                    case 72: //clockwise
                        {
                            if (rotation)
                            {
                                if (rotation->joinable())
                                {
                                    rotation->join();
                                }
                            }

                            delete rotation;
                            rotation = new thread(&BoardPart::rotate, board[i][j], 90, 1 + i * 2 + j);

                            backend->rotate(i * 2 + j + 1, 1);
                            break;
                        }
                }

                //backend->draw();
            }
        }
    }
}

void Frontend::cpuTurn(RenderWindow &pentago)
{
    if (!whoWins && backend->getWhosTurn() == 2) //black
    {
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                if (!board[i][j]->getCanChangeSprites())
                {
                    return;
                }
            }
        }

        Answer ans = bot->getMove(backend->getBoard());

        //cout << "ANS " << ans.ansLine << ' ' << ans.ansRow << ' ' << ans.ansPart << ' ' << ans.ansAngle << endl;

        if (ans.ansLine != -1)
        {
            backend->setDot(ans.ansLine, ans.ansRow);
            updateFront();
            updateTurn();
            show(pentago);

            this_thread::sleep_for(chrono::milliseconds(300));

            if (ans.ansAngle != 0)
            {
                board[(ans.ansPart - 1) / 2][(ans.ansPart - 1) % 2]->choose();

                if (ans.ansAngle == -1)
                {
                    rotateChoosenPart(71);
                }

                if (ans.ansAngle == 1)
                {
                    rotateChoosenPart(72);
                }
            }
        }
    }
}

void Frontend::play(RenderWindow &pentago)
{
    clock.restart();

    setup();

    while (true)
    {
        Event event;

        while (pentago.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                pentago.close();
                return;
            }

            if (event.type == Event::KeyPressed)
            {
                //cout << "code " << event.key.code << endl;

                if (event.key.code == Keyboard::Escape)
                {
                    return;
                }
                
                /*if (event.key.code == Keyboard::Space)
                {
                    if (gameType && !whoWins)
                    {
                        cpuTurn(pentago);
                    }
                }*/
            }

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    if (whoWins && winScreen && !hideWinScreen)
                    {
                        int choice = winScreen->click(pentago);

                        if (choice == 1)
                        {
                            return;        
                        }
                        else
                        {
                            hideWinScreen = true;
                        }
                    }
                    else
                    {
                        if (onClick(pentago))
                        {
                            return;
                        }

                        if (!hideWinScreen)
                        {
                            if (!backend->getIsDotSet())
                            {
                                pickBall(pentago);
                            }
                            else
                            {
                                pickPart(pentago);
                            }
                        }
                    }
                }
            }
        }

        if (gameType && !whoWins)
        {
            cpuTurn(pentago);
        }

        whoWins = backend->isWin();

        if (gameType && whoWins == 2)
        {
            whoWins = 3;
        }

        updateFront();
        updateTurn();

        if (whoWins && !winScreen)
        {
            winScreen = new WinScreen();
            winScreen->setup(whoWins);

            clock.restart();
        }

        if (hideWinScreen && hideWinScreenHelper)
        {
            hideWinScreenHelper = false;
            clock.restart();
        }

        show(pentago);
    }
}

void Frontend::updateTurn()
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            if (!board[i][j]->getCanChangeSprites())
            {
                return;
            }
        }
    }

    int whosTurn = backend->getWhosTurn();

    ballTurn->texture.loadFromFile("./Textures/ball" + to_string(whosTurn) + ".png");
    ballTurn->sprite.setTexture(ballTurn->texture, true);
}

void Frontend::updateFront()
{
    pair < int, int > backendSize = backend->getSize();

    for (int i = 0; i < backendSize.first; i++)
    {
        for (int j = 0; j < backendSize.second; j++)
        {
            int ball = backend->getBall(i, j);

            board[i / 3][j / 3]->setDot(i % 3, j % 3, ball); 
        }
    }
}

void Frontend::show(RenderWindow &pentago)
{
    pentago.clear(Color(30, 30, 30));

    boardBack->sprite.setPosition(Vector2f(boardBack->x, boardBack->y));
    boardBack->sprite.setOrigin(Vector2f(boardBack->orx, boardBack->ory));
    pentago.draw(boardBack->sprite);

    back->sprite.setPosition(Vector2f(back->x, back->y));
    back->sprite.setOrigin(Vector2f(back->orx, back->ory));
    pentago.draw(back->sprite);

    turnLeft->sprite.setPosition(Vector2f(turnLeft->x, turnLeft->y));
    turnLeft->sprite.setOrigin(Vector2f(turnLeft->orx, turnLeft->ory));
    pentago.draw(turnLeft->sprite);

    turnRight->sprite.setPosition(Vector2f(turnRight->x, turnRight->y));
    turnRight->sprite.setOrigin(Vector2f(turnRight->orx, turnRight->ory));
    pentago.draw(turnRight->sprite);

    ballTurn->sprite.setPosition(Vector2f(ballTurn->x, ballTurn->y));
    ballTurn->sprite.setOrigin(Vector2f(ballTurn->orx, ballTurn->ory));
    pentago.draw(ballTurn->sprite);

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            board[i][j]->draw(pentago);
        }
    }

    if (whoWins && ((!hideWinScreen && clock.getElapsedTime().asMilliseconds() >= 1150) || (hideWinScreen && clock.getElapsedTime().asMilliseconds() >= 4000)))
    {
        hideWinScreen = false;
        hideWinScreenHelper = true;
        winScreen->show(pentago);
    }

    pentago.display();
}

Frontend::~Frontend()
{
    delete backend;
    delete bot;

    delete boardBack;

    if (rotation)
    {
        if (rotation->joinable())
        {
            rotation->join();
            delete rotation;
        }
    }

    delete back;
    delete turnLeft;
    delete turnRight;
    delete ballTurn;

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            delete board[i][j];
        }
    }

    if (winScreen)
    {
        delete winScreen;
    }
}
