#include "zbuffer.hpp"

using namespace std;
using namespace sf;
using namespace fvl;

ZBuffer::ZBuffer(){}

void ZBuffer::matterRasterUp(Image &frameBuffer, vector < vector < double > > &depthBuffer, double x1, double y1, double z1, double r1, double g1, double b1, double x2, double y2, double z2, double r2, double g2, double b2, double x3, double y3, double z3, double r3, double g3, double b3)
{
    double triangleArea = (y1 - y3) * (x2 - x3) + (y2 - y3) * (x3 - x1);
        
    for (int i = max(0.0, y1); i < min(double(depthBuffer.size()), y2); i++)
    {
        int wx1 = int(double(double(i - y1) / double(y2 - y1)) * double(x2 - x1) + double(x1));
        int wx2 = int(double(double(i - y1) / double(y3 - y1)) * double(x3 - x1) + double(x1));

        if (wx1 > wx2)
        {
            swap(wx1, wx2);
        }
        

        // рисуем горизонтальную линию между рабочими
        // точками 
        
        for (int j = max(0, wx1); j <= min(int(depthBuffer[0].size()), wx2); j++)
        {
            double bc1 = ((i - y3) * (x2 - x3) + (y2 - y3) * (x3 - j)) / triangleArea;

            double bc2 = ((i - y1) * (x3 - x1) + (y3 - y1) * (x1 - j)) / triangleArea;

            double bc3 = ((i - y2) * (x1 - x2) + (y1 - y2) * (x2 - j)) / triangleArea;


            if (bc1 >= 0 && bc1 <= 1 && bc2 >= 0 && bc2 <= 1 && bc3 >= 0 && bc3 <= 1) 
            {
                double depth = bc1 * z1 + bc2 * z2 + bc3 * z3;

                double red = bc1 * r1 + bc2 * r2 + bc3 * r3;
                double green = bc1 * g1 + bc2 * g2 + bc3 * g3;
                double blue = bc1 * b1 + bc2 * b2 + bc3 * b3;
        
                Color color = Color(min(255.0, red * 255), min(255.0, green * 255), min(255.0, blue * 255));

                if (depthBuffer[i][j] > depth) 
                {
                    depthBuffer[i][j] = depth; 
                    frameBuffer.setPixel(j, i, color);
                }
            }
        }
    }
}

void ZBuffer::matterRasterDown(Image &frameBuffer, vector < vector < double > > &depthBuffer, double x1, double y1, double z1, double r1, double g1, double b1, double x2, double y2, double z2, double r2, double g2, double b2, double x3, double y3, double z3, double r3, double g3, double b3)
{
    double triangleArea = (y1 - y3) * (x2 - x3) + (y2 - y3) * (x3 - x1);

    for (int i = max(0.0, y2); i <= min(double(depthBuffer.size() - 1), y3); i++)
    {
        int wx1 = int(double(double(i - y1) / double(y3 - y1)) * double(x3 - x1) + double(x1));
        int wx2 = int(double(double(i - y2) / double(y3 - y2)) * double(x3 - x2) + double(x2));

        if (wx1 > wx2)
        {
            swap(wx1, wx2);
        }
            
        if (wx1 < 0)
        {
            wx1 = 0;          
        }
            
        if (wx2 < 0)
        {
            wx2 = 0;          
        }

        // рисуем горизонтальную линию между рабочими
        // точками 
        
        for (int j = max(0, wx1); j <= min(int(depthBuffer[0].size() - 1), wx2); j++)
        {
            double bc1 = ((i - y3) * (x2 - x3) + (y2 - y3) * (x3 - j)) / triangleArea;

            double bc2 = ((i - y1) * (x3 - x1) + (y3 - y1) * (x1 - j)) / triangleArea;

            double bc3 = ((i - y2) * (x1 - x2) + (y1 - y2) * (x2 - j)) / triangleArea;

            if (bc1 >= 0 && bc1 <= 1 && bc2 >= 0 && bc2 <= 1 && bc3 >= 0 && bc3 <= 1) 
            {
                double depth = bc1 * z1 + bc2 * z2 + bc3 * z3;
                
                double red = bc1 * r1 + bc2 * r2 + bc3 * r3;
                double green = bc1 * g1 + bc2 * g2 + bc3 * g3;
                double blue = bc1 * b1 + bc2 * b2 + bc3 * b3;
                
                Color color = Color(min(255.0, red * 255), min(255.0, green * 255), min(255.0, blue * 255));
                    
                if (depthBuffer[i][j] > depth) 
                {
                    depthBuffer[i][j] = depth; 
                    frameBuffer.setPixel(j, i, color);
                }
            }
        }
    }
}





void ZBuffer::lightsRasterUp(Image &frameBuffer, vector < vector < double > > &depthBuffer, Color color, double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3)
{
    double triangleArea = (y1 - y3) * (x2 - x3) + (y2 - y3) * (x3 - x1);
        
    for (int i = max(0.0, y1); i < min(double(depthBuffer.size()), y2); i++)
    {
        int wx1 = int(double(double(i - y1) / double(y2 - y1)) * double(x2 - x1) + double(x1));
        int wx2 = int(double(double(i - y1) / double(y3 - y1)) * double(x3 - x1) + double(x1));

        if (wx1 > wx2)
        {
            swap(wx1, wx2);
        }
        

        // рисуем горизонтальную линию между рабочими
        // точками 
        
        for (int j = max(0, wx1); j <= min(int(depthBuffer[0].size()), wx2); j++)
        {
            double bc1 = ((i - y3) * (x2 - x3) + (y2 - y3) * (x3 - j)) / triangleArea;

            double bc2 = ((i - y1) * (x3 - x1) + (y3 - y1) * (x1 - j)) / triangleArea;

            double bc3 = ((i - y2) * (x1 - x2) + (y1 - y2) * (x2 - j)) / triangleArea;


            if (bc1 >= 0 && bc1 <= 1 && bc2 >= 0 && bc2 <= 1 && bc3 >= 0 && bc3 <= 1) 
            {
                double depth = bc1 * z1 + bc2 * z2 + bc3 * z3;
                    
                if (depthBuffer[i][j] > depth) 
                {
                    depthBuffer[i][j] = depth; 
                    frameBuffer.setPixel(j, i, color);
                }
            }
        }
    }
}

void ZBuffer::lightsRasterDown(Image &frameBuffer, vector < vector < double > > &depthBuffer, Color color, double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3)
{
    double triangleArea = (y1 - y3) * (x2 - x3) + (y2 - y3) * (x3 - x1);

    for (int i = max(0.0, y2); i <= min(double(depthBuffer.size() - 1), y3); i++)
    {
        int wx1 = int(double(double(i - y1) / double(y3 - y1)) * double(x3 - x1) + double(x1));
        int wx2 = int(double(double(i - y2) / double(y3 - y2)) * double(x3 - x2) + double(x2));

        if (wx1 > wx2)
        {
            swap(wx1, wx2);
        }
            
        if (wx1 < 0)
        {
            wx1 = 0;          
        }
            
        if (wx2 < 0)
        {
            wx2 = 0;          
        }

        // рисуем горизонтальную линию между рабочими
        // точками 
        
        for (int j = max(0, wx1); j <= min(int(depthBuffer[0].size() - 1), wx2); j++)
        {
            double bc1 = ((i - y3) * (x2 - x3) + (y2 - y3) * (x3 - j)) / triangleArea;

            double bc2 = ((i - y1) * (x3 - x1) + (y3 - y1) * (x1 - j)) / triangleArea;

            double bc3 = ((i - y2) * (x1 - x2) + (y1 - y2) * (x2 - j)) / triangleArea;

            if (bc1 >= 0 && bc1 <= 1 && bc2 >= 0 && bc2 <= 1 && bc3 >= 0 && bc3 <= 1) 
            {
                double depth = bc1 * z1 + bc2 * z2 + bc3 * z3;
                    
                if (depthBuffer[i][j] > depth) 
                {
                    depthBuffer[i][j] = depth; 
                    frameBuffer.setPixel(j, i, color);
                }
            }
        }
    }
}

void ZBuffer::renderMatter(RenderWindow &window, Image &frameBuffer, vector < vector < double > > &depthBuffer, Stuff::Object &Object)
{
#pragma omp parallel for
    for (int k = 0; k < Object.object.size(); k++)
    {
        if (!Object.object[k].visible)
        {
            continue;
        }

        double x0 = Object.vertices[Object.object[k].polygon[0]].x();
        double y0 = Object.vertices[Object.object[k].polygon[0]].y();
        double z0 = Object.vertices[Object.object[k].polygon[0]].z();
        
        double r0 = Object.verticesColors[Object.object[k].polygon[0]].x();
        double g0 = Object.verticesColors[Object.object[k].polygon[0]].y();
        double b0 = Object.verticesColors[Object.object[k].polygon[0]].z();
        
        
        double x1 = Object.vertices[Object.object[k].polygon[1]].x();
        double y1 = Object.vertices[Object.object[k].polygon[1]].y();
        double z1 = Object.vertices[Object.object[k].polygon[1]].z();
        
        double r1 = Object.verticesColors[Object.object[k].polygon[1]].x();
        double g1 = Object.verticesColors[Object.object[k].polygon[1]].y();
        double b1 = Object.verticesColors[Object.object[k].polygon[1]].z();
        
        
        double x2 = Object.vertices[Object.object[k].polygon[2]].x();
        double y2 = Object.vertices[Object.object[k].polygon[2]].y();
        double z2 = Object.vertices[Object.object[k].polygon[2]].z();
        
        double r2 = Object.verticesColors[Object.object[k].polygon[2]].x();
        double g2 = Object.verticesColors[Object.object[k].polygon[2]].y();
        double b2 = Object.verticesColors[Object.object[k].polygon[2]].z();
        
        
        if (z0 > 1 || z1 > 1 || z2 > 1) //////////////////////
        {
            continue;
        }

        // Упорядочиваем все точки
        
        if (y1 < y0)
        {
            swap(y0, y1);
            swap(x0, x1);
            swap(z0, z1);
            
            swap(r0, r1);
            swap(g0, g1);
            swap(b0, b1);
        }
        
        if (y2 < y0) 
        {
            swap(y0, y2);
            swap(x0, x2);
            swap(z0, z2);
            
            swap(r0, r2);
            swap(g0, g2);
            swap(b0, b2);
        }
      
        if (y1 > y2) 
        {
            swap(y1, y2);
            swap(x1, x2); 
            swap(z1, z2); 
            
            swap(r1, r2);
            swap(g1, g2);
            swap(b1, b2);
        }

        #pragma omp parallel
        {
            // растеризуем верхний полутреугольник
            
            matterRasterUp(frameBuffer, depthBuffer, x0, y0, z0, r0, g0, b0, x1, y1, z1, r1, g1, b1, x2, y2, z2, r2, g2, b2);
        
            // растеризуем нижний полутреугольник
            
            matterRasterDown(frameBuffer, depthBuffer, x0, y0, z0, r0, g0, b0, x1, y1, z1, r1, g1, b1, x2, y2, z2, r2, g2, b2);
        }
    } 
}

void ZBuffer::renderLights(RenderWindow &window, Image &frameBuffer, vector < vector < double > > &depthBuffer, Stuff::LightsObject &lightsObject)
{
#pragma omp parallel for
    for (int k = 0; k < lightsObject.lightsObject.size(); k++)
    {
        if (!lightsObject.lightsObject[k].visible)
        {
            continue;
        }

        double x0 = lightsObject.lightsVertices[lightsObject.lightsObject[k].lightsPolygon[0]].x();
        double y0 = lightsObject.lightsVertices[lightsObject.lightsObject[k].lightsPolygon[0]].y();
        double z0 = lightsObject.lightsVertices[lightsObject.lightsObject[k].lightsPolygon[0]].z();
        
        double x1 = lightsObject.lightsVertices[lightsObject.lightsObject[k].lightsPolygon[1]].x();
        double y1 = lightsObject.lightsVertices[lightsObject.lightsObject[k].lightsPolygon[1]].y();
        double z1 = lightsObject.lightsVertices[lightsObject.lightsObject[k].lightsPolygon[1]].z();
        
        double x2 = lightsObject.lightsVertices[lightsObject.lightsObject[k].lightsPolygon[2]].x();
        double y2 = lightsObject.lightsVertices[lightsObject.lightsObject[k].lightsPolygon[2]].y();
        double z2 = lightsObject.lightsVertices[lightsObject.lightsObject[k].lightsPolygon[2]].z();

        if (z0 > 1 || z1 > 1 || z2 > 1) //////////////////////
        {
            continue;
        }
        
        // Упорядочиваем все точки
        
        if (y1 < y0)
        {
            swap(y0, y1);
            swap(x0, x1);
            swap(z0, z1);
        }
        
        if (y2 < y0) 
        {
            swap(y0, y2);
            swap(x0, x2);
            swap(z0, z2);
        }
      
        if (y1 > y2) 
        {
            swap(y1, y2);
            swap(x1, x2); 
            swap(z1, z2); 
        }

        Color color = Color(lightsObject.lightsObjectColor.x() * 255, lightsObject.lightsObjectColor.y() * 255, lightsObject.lightsObjectColor.z() * 255);

        #pragma omp parallel
        {
            // растеризуем верхний полутреугольник
    
            lightsRasterUp(frameBuffer, depthBuffer, color, x0, y0, z0, x1, y1, z1, x2, y2, z2);
        
            // растеризуем нижний полутреугольник
        
            lightsRasterDown(frameBuffer, depthBuffer, color, x0, y0, z0, x1, y1, z1, x2, y2, z2);
        }
    } 
}

ZBuffer::~ZBuffer(){}
