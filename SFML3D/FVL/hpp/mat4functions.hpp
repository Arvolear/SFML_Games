#ifndef MAT4FUNC_HPP
#define MAT4FUNC_HPP

namespace fvl
{
    mat4 add(const mat4 &mat4tmp1, const mat4 &mat4tmp2);
    
    mat4 sub(const mat4 &mat4tmp1, const mat4 &mat4tmp2);
    
    mat4 mul(const mat4 &mat4tmp1, const mat4 &mat4tmp2);
    
    mat4 div(const mat4 &mat4tmp1, const mat4 &mat4tmp2);


    mat4 matrixMul(const mat4 &mat4tmp1, const mat4 &mat4tmp2);

    mat4 scale(const mat4 &mat4tmp, const vec3 &vec3scale);

    mat4 translate(const mat4 &mat4tmp, const vec3 &vec3translate);
    
    mat4 rotate(const mat4 &mat4tmp, double angle, const vec3 &vec3axis);
    
    mat4 perspective(double angle, double aspect, double front, double back);
            
    mat4 lookAt(const vec3 &vec3CamPos, const vec3 &vec3CamTarget, const vec3 &vec3Up);
}

#endif
