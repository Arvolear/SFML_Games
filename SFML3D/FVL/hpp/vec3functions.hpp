#ifndef VEC3FUNC_HPP
#define VEC3FUNC_HPP

namespace fvl
{
    vec3 add(const vec3 &vec3tmp1, const vec3 &vec3tmp2);
    vec3 add(const vec3 &vec3tmp, double d);
            
    vec3 sub(const vec3 &vec3tmp1, const vec3 &vec3tmp2);
    vec3 sub(const vec3 &vec3tmp, double d);
            
    vec3 mul(const vec3 &vec3tmp1, const vec3 &vec3tmp2);
    vec3 mul(const vec3 &vec3tmp, double d);
            
    vec3 div(const vec3 &vec3tmp1, const vec3 &vec3tmp2);
    vec3 div(const vec3 &vec3tmp, double d);

    vec3 toOrt(const vec3 &vec3tmp);
    
    vec3 reflect(const vec3 &vec3tmp1, const vec3 &vec3tmp2);

    double scalarMul(const vec3 &vec3tmp1, const vec3 &vec3tmp2);

    vec3 vectorMul(const vec3 &vec3tmp1, const vec3 &vec3tmp2);
    
    //vec3 matrixMul(const mat3 &mat3tmp1, const vec3 &vec3tmp1);
}

#endif
