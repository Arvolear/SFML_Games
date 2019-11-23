#ifndef STUFF_HPP
#define STUFF_HPP

#include <vector>
#include <FVL/fvl.hpp>

using namespace std;
using namespace fvl;

struct Stuff
{
    struct Polygon
    {
        bool visible = true;

        vector < int > polygon;
    };

    struct Object
    {
        Object();

        vector < Polygon > object;
        
        vector < vec4 > vertices;
        vector < vector < int > > verticesConnections; //vector where i vertex connects each j polygon of i vector  
        vector < vec3 > verticesColors;
        vector < vec4 > verticesNorms;

        vec3 ambient;
        vec3 diffuse;
        vec3 specular;

        double shininess;

        mat4 model;

        Object(const Object &o);
        Object operator=(const Object &o);
    };
    
    struct LightsPolygon
    {
        bool visible = true;

        vector < int > lightsPolygon;
    };
    
    struct LightsObject
    {
        vector < LightsPolygon > lightsObject;
        vector < vec4 > lightsVertices;

        vec3 lightsObjectColor;//lights color

        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
        
        double constant = 1.0;
        double linear = 0.0014;
        double quadratic = 0.0000007;

        vec4 lightsStreamPos;

        mat4 model;
    };
    
    struct DirectLights
    {
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;

        vec4 direction;
    };  
};

#endif
