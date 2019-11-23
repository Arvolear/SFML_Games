#ifndef VEC4_HPP
#define VEC4_HPP

#include <algorithm>
#include <vector>

using namespace std;

namespace fvl
{
    class vec4
    {
        public:
            vector < double > coords;

        public:
            vec4(double x = 0, double y = 0, double z = 0, double w = 1);


            vec4 operator=(const vec4 &vec4tmp);

            vec4(const vec4 &vec4tmp);

            bool operator==(const vec4 &vec4tmp);

            double length() const;
            
            double x() const;
            double y() const;
            double z() const;
            double w() const;

            //void setCoord(int i, double val);

            vector < double > getCoords() const;

            ~vec4();
    };
}

#endif
