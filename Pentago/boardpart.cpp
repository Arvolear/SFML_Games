#include "boardpart.hpp"

bool cmp(UniversalElement* one, UniversalElement *two)
{
    if (round(one->y) != round(two->y))
    {
        return round(one->y) < round(two->y);
    }

    if (round(one->y) == round(two->y))
    {
        return round(one->x) < round(two->x);
    }

    return false;
}

double clamp(double left, double right, double value)
{
    return value > right ? right : value < left ? left : value;
}

BoardPart::BoardPart(int lines, int rows)
{
    width = rows;
    height = lines;

    isChoosen = false;
    canChangeSprites = true;

    backPart = new UniversalElement();

    balls.resize(lines);

    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            balls[i].push_back(new UniversalElement());
        }
    }
}

void BoardPart::setup(int centerX, int centerY)
{
    this->centerX = centerX;
    this->centerY = centerY;

    backPart->texture.loadFromFile("./Textures/boardpart_small.png");
    backPart->sprite.setTexture(backPart->texture, true);
    backPart->x = centerX;
    backPart->y = centerY;
    backPart->w = backPart->texture.getSize().x;
    backPart->h = backPart->texture.getSize().y;    
    backPart->orx = backPart->w / 2.0;
    backPart->ory = backPart->h / 2.0;
    backPart->rot = 0.0;

    double X = centerX - 153;
    double Y = centerY - 153;

    for (int i = 0; i < balls.size(); i++)
    {
        for (int j = 0; j < balls[i].size(); j++)
        {
            balls[i][j]->texture.loadFromFile("Textures/ball0.png");
            balls[i][j]->sprite.setTexture(balls[i][j]->texture, true);
            balls[i][j]->x = X + j * 153; //143 
            balls[i][j]->y = Y + i * 153;
            balls[i][j]->w = balls[i][j]->texture.getSize().x;
            balls[i][j]->h = balls[i][j]->texture.getSize().y;
            balls[i][j]->orx = balls[i][j]->w / 2.0;
            balls[i][j]->ory = balls[i][j]->h / 2.0;
            balls[i][j]->rot = 0.0;
        }
    }
}

void BoardPart::setDot(int line, int row, int whosTurn)
{
    if (canChangeSprites)
    {
        balls[line][row]->texture.loadFromFile("Textures/ball" + to_string(whosTurn) + ".png");
        balls[line][row]->sprite.setTexture(balls[line][row]->texture, true);
    }
    
    /*if (whosTurn == 0)
    {
        balls[line][row]->texture.loadFromFile("Textures/grid_green.png");
        balls[line][row]->sprite.setTexture(balls[line][row]->texture, true);
    }*/
}

void BoardPart::choose()
{
    isChoosen = true;

    backPart->texture.loadFromFile("./Textures/boardpart_small_choosen.png");
    backPart->sprite.setTexture(backPart->texture, true);
}

void BoardPart::unChoose()
{
    isChoosen = false;

    backPart->texture.loadFromFile("./Textures/boardpart_small.png");
    backPart->sprite.setTexture(backPart->texture, true);
}

void BoardPart::rotate(int angle, int part)
{
    if (!canChangeSprites)
    {
        return;
    }

    canChangeSprites = false;

    for (int i = 0; i < balls.size(); i++)
    {
        for (int j = 0; j < balls[i].size(); j++)
        {
            double r = sqrt((balls[i][j]->x - backPart->x) * (balls[i][j]->x - backPart->x) + (balls[i][j]->y - backPart->y) * (balls[i][j]->y - backPart->y));
            double px = backPart->x + r;
            double py = backPart->y;

            double l = sqrt((balls[i][j]->x - px) * (balls[i][j]->x - px) + (balls[i][j]->y - py) * (balls[i][j]->y - py));

            double dotAngle = 0;
            balls[i][j]->dotAngle = 0;

            if (round(r) != 0 && round(l) != 0)
            {
                balls[i][j]->dotAngle = acos(clamp(-1, 1, -1 * ((l * l) / (2 * r * r)) + 1));
            }
        }
    }

    double offsetX = 0, offsetY = 0;

    switch (part)
    {
        case 1:
            {
                offsetX = -115;
                offsetY = -115;
                break;
            }

        case 2:
            {
                offsetX = 115;
                offsetY = -115;
                break;
            }

        case 3:
            {
                offsetX = -115;
                offsetY = 115;
                break;
            }

        case 4:
            {
                offsetX = 115;
                offsetY = 115;
                break;
            }
    }

    double angleSpeed = 0.5;
    double localAngle = 0;

    double offsetXSpeed = offsetX / (abs(angle) / angleSpeed) * 2;
    double offsetYSpeed = offsetY / (abs(angle) / angleSpeed) * 2;
    bool changed = false;

    while (true)
    {
        if ((angle >= 0 && localAngle > angle) || (angle < 0 && localAngle < angle))
        {
            break;
        }

        if (!changed && ((angle >= 0 && localAngle > angle / 2.0) || (angle < 0 && localAngle < angle / 2.0)))
        {
            offsetXSpeed *= -1;        
            offsetYSpeed *= -1;        

            changed = true;
        }

        this_thread::sleep_for(chrono::milliseconds(6));

        double radAngle = localAngle * 3.14159265 / 180.0;

        backPart->rot = localAngle;
        backPart->x += offsetXSpeed;
        backPart->y += offsetYSpeed;

        for (int i = 0; i < balls.size(); i++)
        {
            for (int j = 0; j < balls[i].size(); j++)
            { 
                balls[i][j]->x += offsetXSpeed;
                balls[i][j]->y += offsetYSpeed;

                double r = sqrt((balls[i][j]->x - backPart->x) * (balls[i][j]->x - backPart->x) + (balls[i][j]->y - backPart->y) * (balls[i][j]->y - backPart->y));

                if (i > 1)
                {
                    balls[i][j]->x = (backPart->x + (cos(radAngle + balls[i][j]->dotAngle)) * r);
                    balls[i][j]->y = (backPart->y + (sin(radAngle + balls[i][j]->dotAngle)) * r);
                }
                else
                {
                    balls[i][j]->x = (backPart->x + (cos(radAngle - balls[i][j]->dotAngle)) * r);
                    balls[i][j]->y = (backPart->y + (sin(radAngle - balls[i][j]->dotAngle)) * r);
                }
            }
        }

        if (angle >= 0)
        {
            localAngle += angleSpeed;
        }
        else
        {
            localAngle -= angleSpeed;
        }
    }

    vector < UniversalElement* > tmp;

    for (int i = 0; i < balls.size(); i++)
    {
        for (int j = 0; j < balls[i].size(); j++)
        {
            round(balls[i][j]->x);
            round(balls[i][j]->y);

            tmp.push_back(balls[i][j]);
        }
    }

    sort(tmp.begin(), tmp.end(), cmp);

    backPart->x = centerX;
    backPart->y = centerY;
    
    double X = centerX - 153;
    double Y = centerY - 153;

    for (int i = 0; i < balls.size(); i++)
    {
        for (int j = 0; j < balls[i].size(); j++)
        {
            balls[i][j] = tmp[i * 3 + j];
            
            balls[i][j]->x = X + j * 153;
            balls[i][j]->y = Y + i * 153;
        }
    }

    this_thread::sleep_for(chrono::milliseconds(200));
    canChangeSprites = true; 
}

void BoardPart::draw(RenderWindow &pentago)
{
    backPart->sprite.setPosition(Vector2f(backPart->x, backPart->y));
    backPart->sprite.setOrigin(Vector2f(backPart->orx, backPart->ory));
    backPart->sprite.setRotation(backPart->rot);

    pentago.draw(backPart->sprite);

    for (int i = 0; i < balls.size(); i++)
    {
        for (int j = 0; j < balls[i].size(); j++)
        {
            balls[i][j]->sprite.setPosition(Vector2f(balls[i][j]->x, balls[i][j]->y));
            balls[i][j]->sprite.setOrigin(Vector2f(balls[i][j]->orx, balls[i][j]->ory));
            balls[i][j]->sprite.setRotation(balls[i][j]->rot);

            pentago.draw(balls[i][j]->sprite);
        }
    }
}

Sprite BoardPart::getPartSprite()
{
    return backPart->sprite;
}

Sprite BoardPart::getBallSprite(int line, int row)
{
    return balls[line][row]->sprite;
}

pair < int, int > BoardPart::getSize()
{
    return {width, height};
}

bool BoardPart::getIsChoosen()
{
    return isChoosen;
}

bool BoardPart::getCanChangeSprites()
{
    return canChangeSprites;
}

BoardPart::~BoardPart()
{
    delete backPart;

    for (int i = 0; i < balls.size(); i++)
    {
        for (int j = 0; j < balls[i].size(); j++)
        {
            delete balls[i][j];
        }
    }
}
