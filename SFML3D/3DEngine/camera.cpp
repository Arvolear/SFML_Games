#include "camera.hpp"

using namespace std;
using namespace fvl;

Camera::Camera(const vec3 &cameraPos, const vec3 &cameraDirection, const vec3 &cameraUp, double windowWidth, double windowHeight)
{
    speed = 10;

    sensitivityX = 60 / windowWidth;
    sensitivityY = (60 / (windowWidth / windowHeight)) / windowHeight;

    Pos = cameraPos;
    Direction = cameraDirection;
    Up = cameraUp;

    Right = toOrt(vectorMul(Up, Direction));

    Speed = vec3(speed, speed, speed);

    prevx = windowWidth / 2.0;
    prevy = windowHeight / 2.0;

    width = windowWidth;
    height = windowHeight;
}

void Camera::calculateRotation(double posx, double posy)
{
    double xoffset = posx - prevx; 
    double yoffset = posy - prevy; 

    xoffset *= sensitivityX;
    yoffset *= sensitivityY;

    Direction = tovec3(matrixMul(rotate(camView, -xoffset, toOrt(Up)), tovec4(Direction)));
        
    Right = toOrt(vectorMul(Up, Direction));
        
    Direction = tovec3(matrixMul(rotate(camView, -yoffset, toOrt(Right)), tovec4(Direction)));
        
    Direction = toOrt(Direction);

    //Mouse::setPosition(Vector2i(int(window.getSize().x / 2), int(window.getSize().y / 2)), window);
    
    camView = lookAt(Pos, add(Pos, Direction), Up);

    prevx = width / 2.0;
    prevy = height / 2.0;
}
        
void Camera::calculatePosition(char direction)
{
    if (direction == 'w')
    {
        Pos = add(Pos, mul(Speed, Direction));
    }
            
    if (direction == 's')
    {
        Pos = sub(Pos, mul(Speed, Direction));
    }

    if (direction == 'a')
    {
        Pos = add(Pos, mul(Speed, Right));
    }
            
    if (direction == 'd')
    {
        Pos = sub(Pos, mul(Speed, Right));
    }
    
    if (direction == 'e')
    {
        Pos = sub(Pos, mul(Speed, Up));
    }
    
    if (direction == 'q')
    {
        Pos = add(Pos, mul(Speed, Up));
    }
    
    camView = lookAt(Pos, add(Pos, Direction), Up);
}

vec3 Camera::getPosition()
{
    return Pos;
}

vec3 Camera::getDirection()
{
    return Direction;
}

mat4 Camera::update(mat4 &view)
{
    view = camView;

    mat4 tmp;

    camView = tmp;

    return view;
}

Camera::~Camera(){}
