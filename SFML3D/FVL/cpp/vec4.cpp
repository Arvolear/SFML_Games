#include "../hpp/vec4.hpp"

using namespace std;

namespace fvl
{
    vec4::vec4(double x, double y, double z, double w)
    {
        coords.push_back(x);
        coords.push_back(y);
        coords.push_back(z);
        coords.push_back(w);
    }

   
    vec4 vec4::operator=(const vec4 &vec4tmp)
    {
        coords = vec4tmp.coords;

        return *this;
    }

    vec4::vec4(const vec4 &vec4tmp)
    {
        coords = vec4tmp.coords;
    }
            
    bool vec4::operator==(const vec4 &vec4tmp)
    {
        if (coords[0] != vec4tmp.x())
        {
            return false;
        }
        
        if (coords[1] != vec4tmp.y())
        {
            return false;
        }
        
        if (coords[2] != vec4tmp.z())
        {
            return false;
        }
        
        if (coords[3] != vec4tmp.w())
        {
            return false;
        }

        return true;
    }

    double vec4::length() const
    {
        return sqrt(coords[0] * coords[0] + coords[1] * coords[1] + coords[2] * coords[2]); 
    }
    
    double vec4::x() const
    {
        return coords[0];
    }
            
    double vec4::y() const
    {
        return coords[1];
    }
            
    double vec4::z() const
    {
        return coords[2];
    }
    
    double vec4::w() const
    {
        return coords[3];
    }

    vector < double > vec4::getCoords() const
    {
        return this->coords;
    }

    vec4::~vec4(){}
}
