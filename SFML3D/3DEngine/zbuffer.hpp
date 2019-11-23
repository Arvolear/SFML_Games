#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <ctime>
#include <algorithm>

#include <FVL/fvl.hpp>
#include <SFML/Graphics.hpp>

#include "stuff.hpp"

using namespace std;
using namespace sf;
using namespace fvl;

class ZBuffer
{
    
    private:
        void matterRasterUp(Image &frameBuffer, vector < vector < double > > &depthBuffer, double x1, double y1, double z1, double r1, double g1, double b1, double x2, double y2, double z2, double r2, double g2, double b2, double x3, double y3, double z3, double r3, double g3, double b3);
        
        void matterRasterDown(Image &frameBuffer, vector < vector < double > > &depthBuffer, double x1, double y1, double z1, double r1, double g1, double b1, double x2, double y2, double z2, double r2, double g2, double b2, double x3, double y3, double z3, double r3, double g3, double b3);
        
        void lightsRasterUp(Image &frameBuffer, vector < vector < double > > &depthBuffer, Color color, double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);

        void lightsRasterDown(Image &frameBuffer, vector < vector < double > > &depthBuffer, Color color, double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);

    public:
        ZBuffer();

        void renderMatter(RenderWindow &window, Image &frameBuffer, vector < vector < double > > &depthBuffer, Stuff::Object &Object);
        
        void renderLights(RenderWindow &window, Image &frameBuffer, vector < vector < double > > &depthBuffer, Stuff::LightsObject &lightsObject);

        ~ZBuffer();
};

#endif
