#include "../hpp/vec3.hpp"
#include "../hpp/vec4.hpp"
#include "../hpp/transform.hpp"

using namespace std;

namespace fvl
{
    vec4 tovec4(const vec3 &vec3tmp, double w)
    {
        return vec4(vec3tmp.x(), vec3tmp.y(), vec3tmp.z(), w);    
    }
    
    vec3 tovec3(const vec4 &vec4tmp)
    {
        return vec3(vec4tmp.x(), vec4tmp.y(), vec4tmp.z());    
    }
}
