#include "stuff.hpp"
#include "generate.hpp"
#include "fpstracker.hpp"
#include "camera.hpp"
#include "zbuffer.hpp"
#include "graphics.hpp"

using namespace std;
using namespace fvl;
using namespace sf;

Graphics::Graphics()
{
    width = 1066;
    height = 600;

    amountOfBulbs = 2;
    amountOfMatter = 2;

    fov = 45;

    camera = new Camera(vec3(0, 0, 300), vec3(0, 0, -1), vec3(0, 1, 0), width, height);

    FPS = new FPSTracker(width, height);

    generator = new Generate();

    projection = perspective(fov, 1.7777777, 10, 100000);

    underFocuse = true;
}

void Graphics::preinitLights()
{
    preLights.resize(2);

    vector < vec4 > cubeVertices = 
    {
        vec4(-1, 1, -1),
        vec4(1, 1, -1),
        vec4(1, -1, -1),
        vec4(-1, -1, -1),
        vec4(-1, 1, 1),
        vec4(1, 1, 1),
        vec4(1, -1, 1),
        vec4(-1, -1, 1)
    };

    vector < vec4 > cubeIndicies = 
    {
        vec4(0, 1, 2),
        vec4(0, 2, 3),
        vec4(2, 1, 5),
        vec4(2, 5, 6),
        vec4(3, 2, 6),
        vec4(3, 6, 7),
        vec4(0, 3, 7),
        vec4(0, 7, 4),
        vec4(1, 0, 4),
        vec4(1, 4, 5),
        vec4(6, 5, 4),
        vec4(6, 4, 7)
    };

    for (int k = 0; k < preLights.size(); k++)
    {
        preLights[k].lightsObject.resize(12);

        preLights[k].lightsVertices = cubeVertices; 

        for (int i = 0; i < cubeIndicies.size(); i++)
        {
            preLights[k].lightsObject[i].lightsPolygon.push_back(cubeIndicies[i].x()); 
            preLights[k].lightsObject[i].lightsPolygon.push_back(cubeIndicies[i].y()); 
            preLights[k].lightsObject[i].lightsPolygon.push_back(cubeIndicies[i].z()); 
        }
    }
}

void Graphics::preinitMatter()
{
    preMatter.resize(2);

    generator->spawn(preMatter[0], "./models/Sheriff.obj"); ///////////////////////////////////////////////////////////////////////////////////

    /*vector < vec4 > octaVertices = 
=======
    preMatter.resize(10);

    vector < vec4 > tetraVertices = 
    {
        vec4(1, 1, 1),
        vec4(-1, -1, 1),
        vec4(-1, 1, -1),
        vec4(1, -1, -1)
    };

    vector < vec4 > tetraIndicies = 
    {
        vec4(0, 2, 1),
        vec4(1, 2, 3),
        vec4(0, 3, 2),
        vec4(1, 3, 0)
    };

    preMatter[0].vertices = tetraVertices; 
    preMatter[0].object.resize(4);
    preMatter[0].verticesColors.resize(4);
    preMatter[0].verticesConnections.resize(4);

    for (int i = 0; i < tetraIndicies.size(); i++)
    {
        preMatter[0].object[i].polygon.push_back(tetraIndicies[i].x()); 
        preMatter[0].object[i].polygon.push_back(tetraIndicies[i].y()); 
        preMatter[0].object[i].polygon.push_back(tetraIndicies[i].z());

        preMatter[0].verticesConnections[tetraIndicies[i].x()].push_back(i);
        preMatter[0].verticesConnections[tetraIndicies[i].y()].push_back(i);
        preMatter[0].verticesConnections[tetraIndicies[i].z()].push_back(i);
    }

    vector < vec4 > octaVertices = 
>>>>>>> 2f7a0207ab68e667e5a7d85ddd2e7fb12ee8c238
    {
        vec4(1, 0, 0),
        vec4(0, 1, 0),
        vec4(0, 0, 1),
        vec4(-1, 0, 0),
        vec4(0, -1, 0),
        vec4(0, 0, -1)
    };

    vector < vec4 > octaIndicies = 
    {
        vec4(2, 0, 1),
        vec4(0, 5, 1),
        vec4(5, 3, 1),
        vec4(2, 1, 3),
        vec4(4, 0, 2),
        vec4(4, 5, 0),
        vec4(4, 3, 5),
        vec4(4, 2, 3)
    };

    preMatter[1].vertices = octaVertices; 
    preMatter[1].object.resize(8);
    preMatter[1].verticesColors.resize(6);
    preMatter[1].verticesConnections.resize(6);

    for (int i = 0; i < octaIndicies.size(); i++)
    {
        preMatter[1].object[i].polygon.push_back(octaIndicies[i].x()); 
        preMatter[1].object[i].polygon.push_back(octaIndicies[i].y()); 
        preMatter[1].object[i].polygon.push_back(octaIndicies[i].z()); 

        preMatter[1].verticesConnections[octaIndicies[i].x()].push_back(i);
        preMatter[1].verticesConnections[octaIndicies[i].y()].push_back(i);
        preMatter[1].verticesConnections[octaIndicies[i].z()].push_back(i);
    }

<<<<<<< HEAD
    preMatter[1] = generator->makeSphereFromOctahedron(preMatter[1], 1, 4);*/

    vec3 dir = camera->getDirection();
    generator->calculateNorms(preMatter, dir, fov);
}

void Graphics::initDirectLights()
{
    directLights.resize(1);

    vector < vec3 > ambience = 
    {
        vec3(0.3, 0.3, 0.3)
    };

    vector < vec3 > diffusion = 
    {
        vec3(2.5, 2.5, 2.5)
    };

    vector < vec3 > speculum = 
    {
        vec3(0.5, 0.5, 0.5)
    };

    vector < vec4 > directions = 
    {
        vec4(-0.2, 1.0, -0.3)
    };

#pragma omp parallel for
    for (int k = 0; k < directLights.size(); k++)
    {
        directLights[k].ambient = ambience[k];
        directLights[k].diffuse = diffusion[k];
        directLights[k].specular = speculum[k];
        directLights[k].direction = directions[k];
    }
}

void Graphics::initLights(int &counter)
{
    lights.resize(preLights.size());

#pragma omp parallel for
    for (int i = 0; i < preLights.size(); i++)
    {
        lights[i] = preLights[i];
    }

    double radius = 1000.0;

    double radC = counter * 3.14159265 / 180.0;

    double lX = sin(radC) * radius;
    double lZ = cos(radC) * radius;

    vector < vec3 > positions = 
    {
        vec3(lX, 0.0, lZ),
        vec3(-lX, lZ, 0.0)
    };

    vector < vec3 > rotations = 
    {
    }; 

    vector < vec3 > scales = 
    {
        vec3(20.0, 20.0, 20.0),
        vec3(20.0, 20.0, 20.0)
    };

    double R = rand() / double(RAND_MAX);
    double G = rand() / double(RAND_MAX);
    double B = rand() / double(RAND_MAX);

    vector < vec3 > colors = 
    {
        vec3(1.0, 0.0, 1.0),
        vec3(0.2, 0.2, 0.2)
    };

    vector < vec3 > ambience = 
    {
        vec3(0.5, 0.0, 0.5),
        vec3(1.0, 1.0, 1.0)
    };

    vector < vec3 > diffusion = 
    {
        vec3(5.0, 0.0, 5.0),
        vec3(1.0, 1.0, 1.0)
    };

    vector < vec3 > speculum = 
    {
        vec3(1.0, 0.0, 1.0),
        vec3(1.0, 1.0, 1.0)
    };



    srand(time(0));

#pragma omp parallel for
    for (int k = 0; k < amountOfBulbs; k++)
    {
        mat4 localModel;

        if (!positions.empty())
        {
            localModel = translate(localModel, positions[k]);
        }

        if (!rotations.empty())
        {
            localModel = rotate(localModel, 69, toOrt(rotations[k]));
        }

        if (!scales.empty())
        {
            localModel = scale(localModel, scales[k]);
        }

        lights[k].model = localModel;

        lights[k].lightsObjectColor = colors[k];
        //lights[k].lightsObjectColor = 

        lights[k].ambient = ambience[k];        
        lights[k].diffuse = diffusion[k];        
        lights[k].specular = speculum[k];
    }
}

void Graphics::initMatter(int &counter)
{
    ////////////////////////////////////////////////////////////////
    matter.resize(preMatter.size());

#pragma omp parallel for
    for (int i = 0; i < preMatter.size(); i++)
    {
        matter[i] = preMatter[i];
    }
    ////////////////////////////////////////////////////////////////

    vector < vec3 > positions = 
    {
        vec3(0, 50, 0),
        vec3(-300.0, -50.0, -250.0),
        vec3(150.0, -50.0, 50.0),
    };

    vector < vec3 > rotations = 
    {
        vec3(0, 1, 0),
        vec3(-2, -4, 1),
        vec3(-2, -1, 1),
    };

    vector < vec3 > scales = 
    {
        vec3(200.0, 200.0, 200.0),
        vec3(100.0, 100.0, 100.0),
        vec3(50.0, 50.0, 50.0),
    };

    vector < vec3 > ambience = 
    {
        vec3(0.2473, 0.1995, 0.0745), //gold
        vec3(0.0215, 0.1745, 0.0215), //emerald
        vec3(0.2125, 0.1275, 0.054), //bronze
        vec3(0.1745, 0.0118, 0.0118) //ruby
    };

    vector < vec3 > diffusion = 
    {
        vec3(0.7516, 0.6065, 0.2265), //gold
        vec3(0.0757, 0.6142, 0.0757), //emerald
        vec3(0.714, 0.4284, 0.1814), //bronze
        vec3(0.6142, 0.0414, 0.0414) //ruby
    };

    vector < vec3 > speculum = 
    {
        vec3(0.6282, 0.5558, 0.366), //gold
        vec3(0.633, 0.7278, 0.633), //emerald
        vec3(0.3935, 0.2719, 0.1667), //bronze
        vec3(0.7278, 0.627, 0.627) //ruby
    };

    vector < double > shine = 
    {
        0.4, //gold
        0.6, //emerald
        0.2, //bronze
        0.6 //ruby
    };


    srand(time(0));

    for (int k = 0; k < amountOfMatter; k++)
    {
        mat4 localModel;

        if (!positions.empty())
        {
            localModel = translate(localModel, positions[k]);
        }

        if (!rotations.empty())
        {
            localModel = rotate(localModel, 69, toOrt(rotations[k]));

            localModel = rotate(localModel, counter / double(2 * k + 1), toOrt(rotations[k]));

#pragma omp parallel for
            for (int i = 0; i < matter[k].verticesNorms.size(); i++)
            {
                mat4 local;
                local = rotate(local, 69, toOrt(rotations[k]));
                local = rotate(local, counter / double(2 * k + 1), toOrt(rotations[k]));

                matter[k].verticesNorms[i] = matrixMul(local, matter[k].verticesNorms[i]);
            }
        }

        if (!scales.empty())
        {
            localModel = scale(localModel, scales[k]);
        }

        matter[k].ambient = ambience[k];        
        matter[k].diffuse = diffusion[k];        
        matter[k].specular = speculum[k];
        matter[k].shininess = shine[k] * 128.0;

        matter[k].model = localModel;
    }
}

void Graphics::cameraTrigger(RenderWindow &scene)
{
    Vector2i pixelpos = Mouse::getPosition(scene);
    Vector2f pos = scene.mapPixelToCoords(pixelpos);

    camera->calculateRotation(pos.x, pos.y);

    Mouse::setPosition(Vector2i(int(scene.getSize().x / 2), int(scene.getSize().y / 2)), scene);

    if (keys[Keyboard::W])
    {
        camera->calculatePosition('w');
    }
    if (keys[Keyboard::S])
    {
        camera->calculatePosition('s');
    }

    if (keys[Keyboard::A])
    {
        camera->calculatePosition('a');
    }
    if (keys[Keyboard::D])
    {
        camera->calculatePosition('d');
    }
    if (keys[Keyboard::E])
    {
        camera->calculatePosition('e');
    }
    if (keys[Keyboard::Q])
    {
        camera->calculatePosition('q');
    }
}

vec3 Graphics::calculateDirLight(Stuff::DirectLights &directLights, int &i, Stuff::Object &Object, vec3 &viewDirection)
{
    //calculating diffusion value
    vec4 lightsRay = toOrt(mul(directLights.direction, -1));

    double diffusion = max(scalarMul(Object.verticesNorms[i], lightsRay), 0.0);

    //calculating reflection value
    vec4 reflectionRay = reflect(mul(lightsRay, -1), Object.verticesNorms[i]);

    double reflection = pow(max(scalarMul(viewDirection, tovec3(reflectionRay)), 0.0), Object.shininess);


    //final ambience
    vec3 ambient = mul(directLights.ambient, Object.ambient);

    //final diffusion
    vec3 diffused(diffusion * directLights.diffuse.x() * Object.diffuse.x(), diffusion * directLights.diffuse.y() * Object.diffuse.y(), diffusion * directLights.diffuse.z() * Object.diffuse.z());

    //final spuculum
    vec3 specular(reflection * directLights.specular.x() * Object.specular.x(), reflection * directLights.specular.y() * Object.specular.y(), reflection * directLights.specular.z() * Object.specular.z());

    return add(add(ambient, diffused), specular);
}

vec3 Graphics::calculatePointLight(Stuff::LightsObject &lightsObject, int &i, Stuff::Object &Object, vec3 &viewDirection)
{
    //lights ray direction
    vec4 lightsRay = toOrt(sub(lightsObject.lightsStreamPos, Object.vertices[i]));

    //calculating diffusion value
    double diffusion = max(scalarMul(Object.verticesNorms[i], lightsRay), 0.0);

    //reflection ray direction
    vec4 reflectionRay = reflect(mul(lightsRay, -1), Object.verticesNorms[i]);

    //calculating reflection value
    double reflection = pow(max(scalarMul(viewDirection, tovec3(reflectionRay)), 0.0), Object.shininess);////////////////////////


    //calculating distance between lights and object plane 
    vec4 dist = mul(sub(lightsObject.lightsStreamPos, Object.vertices[i]), sub(lightsObject.lightsStreamPos, Object.vertices[i]));

    //distance
    double distance = sqrt(dist.x() + dist.y() + dist.z());

    //calculating attenuation with distance
    double attenuation = 1.0 / (lightsObject.constant + lightsObject.linear * distance + lightsObject.quadratic * (distance * distance));

    //final ambience
    vec3 ambient = mul(lightsObject.ambient, Object.ambient);

    //final diffusion
    vec3 diffused(diffusion * lightsObject.diffuse.x() * Object.diffuse.x(), diffusion * lightsObject.diffuse.y() * Object.diffuse.y(), diffusion * lightsObject.diffuse.z() * Object.diffuse.z());

    //final speculum
    vec3 specular(reflection * lightsObject.specular.x() * Object.specular.x(), reflection * lightsObject.specular.y() * Object.specular.y(), reflection * lightsObject.specular.z() * Object.specular.z());

    //attenuating

    ambient = mul(ambient, attenuation);

    diffused = mul(diffused, attenuation);

    specular = mul(specular, attenuation);

    return add(add(ambient, diffused), specular);
}

void Graphics::calculateIllumination(Stuff::Object &Object, vec3 &viewDirection)
{
#pragma omp parallel for
    for (int i = 0; i < Object.vertices.size(); i++)
    {
        vec3 outputPointColor;

        /*if (i % 3 == 0)
          {
          outputPointColor = vec3(1, 0, 0);
          }

          if (i % 3 == 1)
          {
          outputPointColor = vec3(0, 1, 0);
          }

          if (i % 3 == 2)
          {
          outputPointColor = vec3(0, 0, 1);
          }*/

#pragma omp parallel
        {
            for (int k = 0; k < directLights.size(); k++)
            {
//                outputPointColor = add(outputPointColor, calculateDirLight(directLights[k], i, Object, viewDirection));
            }

            for (int k = 0; k < lights.size(); k++)
            {
                outputPointColor = add(outputPointColor, calculatePointLight(lights[k], i, Object, viewDirection));
            }
        }
        //outputPointcolor = add(outputPointColor, calculateSpotLight());

        Object.verticesColors[i] = outputPointColor;
    }
}

void Graphics::shineTrace(Stuff::LightsObject &lightsObject)
{
#pragma omp parallel for
    for (int j = 0; j < lightsObject.lightsVertices.size(); j++)
    {
        lightsObject.lightsVertices[j] = matrixMul(lightsObject.model, lightsObject.lightsVertices[j]);

        lightsObject.lightsVertices[j] = matrixMul(view, lightsObject.lightsVertices[j]);

        lightsObject.lightsVertices[j] = matrixMul(projection, lightsObject.lightsVertices[j]);

        lightsObject.lightsVertices[j] = normalize(lightsObject.lightsVertices[j]);

        lightsObject.lightsVertices[j] = toWindow(lightsObject.lightsVertices[j], width, height);
    }
}

void Graphics::magicTransform(Stuff::Object &Object)
{
#pragma omp parallel for
    for (int j = 0; j < Object.vertices.size(); j++)
    {
        Object.vertices[j] = matrixMul(Object.model, Object.vertices[j]);
    }
    vec3 dir = camera->getDirection();

    calculateIllumination(Object, dir);//in world space

#pragma omp parallel for
    for (int j = 0; j < Object.vertices.size(); j++)
    {
        Object.vertices[j] = matrixMul(view, Object.vertices[j]); 
        
        Object.vertices[j] = matrixMul(projection, Object.vertices[j]); 

        Object.vertices[j] = normalize(Object.vertices[j]); 
        
        Object.vertices[j] = toWindow(Object.vertices[j], width, height); 
    }
}

void Graphics::start()
{
    int counter = 1;

    thread PIM(&Graphics::preinitMatter, this);
    thread PIL(&Graphics::preinitLights, this);

    ContextSettings settings;
    //settings.antialiasingLevel = 8;

    RenderWindow scene(VideoMode(width, height), "Behold!", Style::Default, settings);
    scene.setSize(Vector2u(2560, 1440));

    scene.setFramerateLimit(60);

    scene.setMouseCursorVisible(false);

    Mouse::setPosition(Vector2i(int(scene.getSize().x / 2), int(scene.getSize().y / 2)), scene);


    PIL.join();
    PIM.join();

    thread CFPS(&FPSTracker::count, FPS, 1000);

    while (scene.isOpen())
    {
        Event event;

        while (scene.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                scene.close();
                //return 0;
            }
            if(event.type == Event::GainedFocus)
            {
                underFocuse = true;
            }

            if(event.type == sf::Event::LostFocus)
            {
                underFocuse = false;
            }

            if (event.type == Event::KeyReleased)
            {
                if (event.key.code >= 0 && event.key.code < 1024)
                {
                    keys[event.key.code] = false; 
                }
            }

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code >= 0 && event.key.code < 1024)
                {
                    keys[event.key.code] = true;
                }
            }
        }

        if (!underFocuse)
        {
            continue;
        }

        initMatter(counter);

        initLights(counter);

        initDirectLights();


        cameraTrigger(scene);

        camera->update(view);

        zBuffer = new ZBuffer();

        Image frameBuffer;

        frameBuffer.create(width, height, Color(20, 20, 20));//Color(210, 200, 170));

        vector < vector < double > > depthBuffer(height, vector < double > (width, 100.0));

        for (int k = 0; k < lights.size(); k++)
        { 
            lights[k].lightsStreamPos = matrixMul(lights[k].model, lights[k].lightsStreamPos);

            shineTrace(lights[k]);
        }

        for (int k = 0; k < matter.size(); k++)
        {
            magicTransform(matter[k]);
        } 

        for (int k = 0; k < matter.size(); k++)
        {
            zBuffer->renderMatter(scene, frameBuffer, depthBuffer, matter[k]);
        }

        for (int k = 0; k < lights.size(); k++)
        { 
            zBuffer->renderLights(scene, frameBuffer, depthBuffer, lights[k]);
        }

        Texture t;
        Sprite s;

        t.loadFromImage(frameBuffer);
        s.setTexture(t);

        scene.clear();

        scene.draw(s);

        FPS->show(scene);

        scene.display();

        counter++;
        counter %= 360 * 15;

        delete zBuffer;

        /*int c = 0;
        for (int i = 0; i < matter.size(); i++)
        {
            c += matter[i].object.size();
        }

        cout << c << endl;*/

        vector < Stuff::DirectLights >().swap(directLights);
        vector < Stuff::LightsObject >().swap(lights);
        vector < Stuff::Object >().swap(matter);

        FPS->addFPS();
    }   

    FPS->stopCounter();
    CFPS.join();
    return;
}

Graphics::~Graphics()
{
    delete camera;
    delete FPS;
    delete generator;
}
