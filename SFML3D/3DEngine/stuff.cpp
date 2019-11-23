#include "stuff.hpp"

Stuff::Object::Object()
{}

Stuff::Object::Object(const Object &o)
{
    this->object.clear();
    this->object.resize(o.object.size());
    this->verticesConnections.resize(o.verticesConnections.size());

#pragma omp parallel for
    for (int i = 0; i < o.object.size(); i++)
    {
        this->object[i].visible = o.object[i].visible;

        this->object[i].polygon = o.object[i].polygon;
    }

#pragma omp parallel for
    for (int i = 0; i < o.verticesConnections.size(); i++)
    {
        this->verticesConnections[i] = o.verticesConnections[i];
    }

    this->vertices = o.vertices;
    this->verticesColors = o.verticesColors;
    this->verticesNorms = o.verticesNorms;

    this->ambient = o.ambient;
    this->diffuse = o.diffuse;
    this->specular = o.specular;
    this->shininess = o.shininess;

    this->model = o.model;
}

Stuff::Object Stuff::Object::operator=(const Object &o)
{
    this->object.clear();
    this->object.resize(o.object.size());
    this->verticesConnections.resize(o.verticesConnections.size());

#pragma omp parallel for
    for (int i = 0; i < o.object.size(); i++)
    {
        this->object[i].visible = o.object[i].visible;

        this->object[i].polygon = o.object[i].polygon;
    }

#pragma omp parallel for
    for (int i = 0; i < o.verticesConnections.size(); i++)
    {
        this->verticesConnections[i] = o.verticesConnections[i];
    }

    this->vertices = o.vertices;
    this->verticesColors = o.verticesColors;
    this->verticesNorms = o.verticesNorms;

    this->ambient = o.ambient;
    this->diffuse = o.diffuse;
    this->specular = o.specular;
    this->shininess = o.shininess;

    this->model = o.model;

    return *this;
}
