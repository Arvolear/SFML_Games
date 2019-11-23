#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <FVL/fvl.hpp>

#include <iostream>
#include <vector>

using namespace std;
using namespace fvl;

class Camera
{
    private:
        mat4 camView;

        double width;
        double height;

        double prevx;
        double prevy;

        double sensitivityX;
        double sensitivityY;

        double speed;

        vec3 Speed;

        vec3 Pos;
        vec3 Direction;
        vec3 Up;
        vec3 Right;

    public:
        Camera(const vec3 &cameraPos, const vec3 &cameraDirection, const vec3 &cameraUp, double windowWidth, double windowHeight);

        void calculateRotation(double posx, double posy);
        
        void calculatePosition(char direction);

        vec3 getPosition();

        vec3 getDirection();

        mat4 update(mat4 &view); 

        ~Camera();
};


#endif
