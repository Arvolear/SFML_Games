#ifndef VEC4FUNC_HPP
#define VEC4FUNC_HPP

namespace fvl
{
    vec4 add(const vec4 &vec4tmp1, const vec4 &vec4tmp2);
    vec4 add(const vec4 &vec4tmp, double d);
            
    vec4 sub(const vec4 &vec4tmp1, const vec4 &vec4tmp2);
    vec4 sub(const vec4 &vec4tmp, double d);
            
    vec4 mul(const vec4 &vec4tmp1, const vec4 &vec4tmp2);
    vec4 mul(const vec4 &vec4tmp, double d);
        
    vec4 div(const vec4 &vec4tmp1,const vec4 &vec4tmp2);
    vec4 div(const vec4 &vec4tmp, double d);

    vec4 toOrt(const vec4 &vec4tmp);
    
    vec4 normalize(const vec4 &vec4tmp);
    
    vec4 reflect(const vec4 &vec4tmp1, const vec4 &vec4tmp2);

    vec4 toWindow(const vec4 &vec4tmp, double width, double height);

    double scalarMul(const vec4 &vec4tmp1, const vec4 &vec4tmp2);

    vec4 vectorMul(const vec4 &vec4tmp1, const vec4 &vec4tmp2);
    
    vec4 matrixMul(const mat4 &mat4tmp, const vec4 &vec4tmp);
}

#endif
