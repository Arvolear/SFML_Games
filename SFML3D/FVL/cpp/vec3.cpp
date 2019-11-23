#include "../hpp/vec3.hpp"

using namespace std;

namespace fvl
{
    vec3::vec3(double x, double y, double z)
    {
        coords.push_back(x);
        coords.push_back(y);
        coords.push_back(z);
    }
            
    vec3 vec3::operator=(const vec3 &vec3tmp)
    {
        coords = vec3tmp.coords;

        return *this;
    }

    vec3::vec3(const vec3 &vec3tmp)
    {
        coords = vec3tmp.coords;
    }

    double vec3::length() const
    {
        return sqrt(coords[0] * coords[0] + coords[1] * coords[1] + coords[2] * coords[2]); 
    }
            
    double vec3::x() const
    {
        return coords[0];
    }
            
    double vec3::y() const
    {
        return coords[1];
    }
            
    double vec3::z() const
    {
        return coords[2];
    }

    vector < double > vec3::getCoords() const
    {
        return this->coords;
    }

    vec3::~vec3(){}
}
