#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <vector>

using namespace std;

namespace fvl
{
    vec4 tovec4(const vec3 &vec3tmp, double w = 1.0);
    
    vec3 tovec3(const vec4 &vec4tmp);
}

#endif
