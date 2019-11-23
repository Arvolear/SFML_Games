#include "stuff.hpp"
#include "camera.hpp"
#include "generate.hpp"

using namespace std;
using namespace sf;
using namespace fvl;

Generate::Generate(){}

void Generate::spawn(Stuff::Object &object, string fileName)
{
    int fragment = 0;

    FILE *file = fopen(fileName.c_str(), "r");

    if (file == 0)
    {
        cout << "Wrong path!\n";
        return;
    }

    while(true)
    {
        char line[256];

        int res = fscanf(file, "%s", line);

        if (res == EOF)
        {
            break;
        }

        if (strcmp(line, "v") == 0)
        {
            vec4 vertex;
            double x, y, z;

            fscanf(file, "%lf %lf %lf\n", &x, &y, &z);

            vertex = vec4(x, y, z);

            object.vertices.push_back(vertex);

            vector < int > tmp;
            object.verticesConnections.push_back(tmp);
        }
        else if(strcmp(line, "f") == 0)
        {   
            int x, y, z;

            fscanf(file, "%d %d %d\n", &x, &y, &z);
            x--;
            y--;
            z--;

            vector < int > tmp{x, y, z};

            object.object.push_back({true, tmp});

            object.verticesConnections[x].push_back(fragment);
            object.verticesConnections[y].push_back(fragment);
            object.verticesConnections[z].push_back(fragment);

            fragment++;
        }
    }
    
    object.verticesColors.resize(object.vertices.size());
}

Stuff::Object Generate::triangulate(Stuff::Object &octa)
{
    Stuff::Object localSphere;
    localSphere.object.resize(octa.object.size() * 4);

    for (int i = 0; i < localSphere.object.size(); i++)
    {
        localSphere.object[i].polygon.resize(3);
    }

    struct O
    {
        vector < vec4 > p;

        vector < bool > b{false, false, false};
    };

    vector < O > o;
    o.resize(octa.object.size() * 4);

#pragma omp parallel for
    for (int i = 0; i < octa.object.size(); i++)
    {
        vec4 p1 = octa.vertices[octa.object[i].polygon[0]];
        vec4 p3 = octa.vertices[octa.object[i].polygon[1]];
        vec4 p5 = octa.vertices[octa.object[i].polygon[2]];

        vec4 p2 = div(add(p1, p3), 2.0);
        vec4 p4 = div(add(p3, p5), 2.0);
        vec4 p6 = div(add(p5, p1), 2.0);

        o[i * 4].p = {p1, p2, p6};

        o[i * 4 + 1].p = {p2, p3, p4};

        o[i * 4 + 2].p = {p6, p4, p5};

        o[i * 4 + 3].p = {p2, p4, p6};
    }

    int counter = 0;
    for (int i = 0; i < o.size(); i++)
    {
        for (int j = 0; j < o[i].p.size(); j++)
        {
            if (!o[i].b[j])
            {
                vec4 tp = o[i].p[j];
                o[i].b[j] = true;

                localSphere.vertices.push_back(tp);
                localSphere.object[i].polygon[j] = counter;

#pragma omp parallel for
                for (int k = 0; k < o.size(); k++)
                {
                    for (int l = 0; l < o[k].p.size(); l++)
                    {
                        if (k != i)
                        {
                            vec4 ttp = o[k].p[l];

                            if (ttp == tp)
                            {
                                o[k].b[l] = true;
                                localSphere.object[k].polygon[l] = counter;
                            }
                        }
                    }
                }

                counter++;
            }
        }
    }

    localSphere.verticesConnections.resize(localSphere.vertices.size());

    localSphere.verticesColors.resize(localSphere.vertices.size());

    for (int i = 0; i < localSphere.object.size(); i++)
    {
        for (int j = 0; j < localSphere.object[i].polygon.size(); j++)
        {
            localSphere.verticesConnections[localSphere.object[i].polygon[j]].push_back(i);
        }
    }

    return localSphere;
}

Stuff::Object Generate::makeSphereFromOctahedron(Stuff::Object &octa, int radius, int quality)
{
    Stuff::Object sphere = octa;

    for (int i = 0; i < quality; i++)
    {
        sphere = triangulate(sphere);
    }

#pragma omp parallel for
    for (int j = 0; j < sphere.vertices.size(); j++)
    {
        vec4 d = sphere.vertices[j];

        double dist = sqrt(d.x() * d.x() + d.y() * d.y() + d.z() * d.z());
        d = mul(d, radius / dist);

        sphere.vertices[j] = d;
    }

    return sphere;
}

void Generate::calculateNorms(vector < Stuff::Object > &matter, vec3 &dir, double fov)
{
    //dir = mul(dir, vec3(1, 1, -1));

    for (int n = 0; n < matter.size(); n++)
    { 
        matter[n].verticesNorms.resize(matter[n].vertices.size());

#pragma omp parallel for 
        for (int k = 0; k < matter[n].verticesConnections.size(); k++)
        {
            vec4 pointNorm;
            for (int j = 0; j < matter[n].verticesConnections[k].size(); j++)
            {
                vec4 a = sub(matter[n].vertices[matter[n].object[matter[n].verticesConnections[k][j]].polygon[1]], 
                             matter[n].vertices[matter[n].object[matter[n].verticesConnections[k][j]].polygon[0]]);

                vec4 b = sub(matter[n].vertices[matter[n].object[matter[n].verticesConnections[k][j]].polygon[2]], 
                             matter[n].vertices[matter[n].object[matter[n].verticesConnections[k][j]].polygon[0]]);

                vec4 norm = toOrt(vectorMul(a, b));

                /*double sc = scalarMul(dir, tovec3(norm));

                if (sc > fov / 100.0)
                {
                    matter[n].object[matter[n].verticesConnections[k][j]].visible = false;
                }*/

                pointNorm = add(pointNorm, norm);
            }

            pointNorm = toOrt(pointNorm);

            matter[n].verticesNorms[k] = pointNorm;
        }
    }
}

Generate::~Generate(){}
