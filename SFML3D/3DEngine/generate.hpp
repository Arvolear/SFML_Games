#pragma once

#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <SFML/Graphics.hpp>
#include <FVL/fvl.hpp>

using namespace std;
using namespace sf;
using namespace fvl;

class Generate
{
    public:
        Generate();

        void spawn(Stuff::Object &object, string fileName);
   
        static Stuff::Object makeSphereFromOctahedron(Stuff::Object &octa, int radius, int quality = 2);
    
        static Stuff::Object triangulate(Stuff::Object &octa);

        void calculateNorms(vector < Stuff::Object > &matter, vec3 &dir, double fov);

        ~Generate();
};

