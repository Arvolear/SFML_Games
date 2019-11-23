#ifndef VEC3_HPP
#define VEC3_HPP

#include <algorithm>
#include <vector>

using namespace std;

namespace fvl
{
    class vec3
    {
        public:
            vector < double > coords;

        public:
            vec3(double x = 0, double y = 0, double z = 0);
            

            vec3 operator=(const vec3 &vec3tmp);

            vec3(const vec3 &vec3tmp);


            double length() const;

            double x() const;
            double y() const;
            double z() const;

            //void setCoord(int i, double val);

            vector < double > getCoords() const;

            ~vec3();
    };
}

#endif
