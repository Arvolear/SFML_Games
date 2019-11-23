#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include <ctime>
#include <algorithm>

#include <FVL/fvl.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace fvl;
using namespace sf;

class Graphics
{
    private:
        int width;
        int height;

        int amountOfBulbs;
        int amountOfMatter;

        bool keys[1024];
        bool underFocuse;

        double fov;

        Camera *camera;
        ZBuffer *zBuffer;
        FPSTracker *FPS;
        Generate *generator;
       
        vector < Stuff::LightsObject > preLights;
        vector < Stuff::Object > preMatter;

        vector < Stuff::DirectLights > directLights;
        vector < Stuff::LightsObject > lights;
        vector < Stuff::Object > matter;

        mat4 view;
        mat4 projection;
        void preinitLights();
        void preinitMatter();

        void initDirectLights();
        void initLights(int &counter);
        void initMatter(int &counter);
        inline void cameraTrigger(RenderWindow &scene);

        vec3 calculateDirLight(Stuff::DirectLights &directLights, int &i, Stuff::Object &Object, vec3 &viewDirection);

        vec3 calculatePointLight(Stuff::LightsObject &lightsObject, int &i, Stuff::Object &Object, vec3 &viewDirection);
                
        void calculateIllumination(Stuff::Object &Object, vec3 &viewDirection);

        inline void shineTrace(Stuff::LightsObject &lightsObject);

        void magicTransform(Stuff::Object &Object);

    public:
        Graphics();

        void start();

        ~Graphics();
};

#endif
