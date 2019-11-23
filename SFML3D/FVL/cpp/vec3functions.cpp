#include "../hpp/vec3.hpp"
#include "../hpp/vec3functions.hpp"

namespace fvl
{
    vec3 add(const vec3 &vec3tmp1, const vec3 &vec3tmp2)
    {
        vec3 res(vec3tmp1.coords[0] + vec3tmp2.coords[0], vec3tmp1.coords[1] + vec3tmp2.coords[1], vec3tmp1.coords[2] + vec3tmp2.coords[2]);

        return res;
    }
    
    vec3 add(const vec3 &vec3tmp, double d)
    {
        vec3 res = add(vec3tmp, vec3(d, d, d));

        return res;
    }

    vec3 sub(const vec3 &vec3tmp1, const vec3 &vec3tmp2)
    {

        vec3 res(vec3tmp1.coords[0] - vec3tmp2.coords[0], vec3tmp1.coords[1] - vec3tmp2.coords[1], vec3tmp1.coords[2] - vec3tmp2.coords[2]);

        return res;
    }
    
    vec3 sub(const vec3 &vec3tmp, double d)
    {
        vec3 res = sub(vec3tmp, vec3(d, d, d));

        return res;
    }
    
    vec3 mul(const vec3 &vec3tmp1, const vec3 &vec3tmp2)
    {
        double i = vec3tmp1.coords[0] * vec3tmp2.coords[0];
        double j = vec3tmp1.coords[1] * vec3tmp2.coords[1];
        double k = vec3tmp1.coords[2] * vec3tmp2.coords[2];
        
        if (i == -0)
        {
            i = 0;
        }
        
        if (j == -0)
        {
            j = 0;
        }
        
        if (k == -0)
        {
            k = 0;
        }

        vec3 res(i, j, k);

        return res;
    }

    vec3 mul(const vec3 &vec3tmp, double d)
    {
        vec3 res = mul(vec3tmp, vec3(d, d, d));

        return res;
    }

    vec3 div(const vec3 &vec3tmp1, const vec3 &vec3tmp2)
    {
        for (int i = 0; i < 3; i++)
        {
            if (vec3tmp2.coords[i] == 0)
            {
                vec3 err(0, 0, 0);

                return err;
            }
        }

        vec3 res(vec3tmp1.coords[0] / vec3tmp2.coords[0], vec3tmp1.coords[1] / vec3tmp2.coords[1], vec3tmp1.coords[2] / vec3tmp2.coords[2]);

        return res;
    }
    
    vec3 div(const vec3 &vec3tmp, double d)
    {
        if (d == 0)
        {
            return vec3();
        }

        vec3 res = div(vec3tmp, vec3(d, d, d));

        return res;
    }



    vec3 toOrt(const vec3 &vec3tmp)
    {
        double l = vec3tmp.length();
        
        vec3 res(vec3tmp.coords[0] / l, vec3tmp.coords[1] / l, vec3tmp.coords[2] / l);
        
        return res;
    }
    
    vec3 reflect(const vec3 &vec3tmp1, const vec3 &vec3tmp2)
    {
        double dp = scalarMul(vec3tmp1, vec3tmp2);

        vec3 res = sub(vec3tmp1, mul(vec3tmp2, 2 * dp));

        return res;
    }
    
    double scalarMul(const vec3 &vec3tmp1, const vec3 &vec3tmp2)
    {
        double res = 0;

        for (int i = 0; i < 3; i++)
        {
            res += vec3tmp1.coords[i] * vec3tmp2.coords[i];
        }

        return res;
    }

    vec3 vectorMul(const vec3 &vec3tmp1, const vec3 &vec3tmp2)
    {
        double i = vec3tmp1.coords[1] * vec3tmp2.coords[2] - vec3tmp1.coords[2] * vec3tmp2.coords[1];
        
        double j = vec3tmp1.coords[2] * vec3tmp2.coords[0] - vec3tmp1.coords[0] * vec3tmp2.coords[2];
        
        double k = vec3tmp1.coords[0] * vec3tmp2.coords[1] - vec3tmp1.coords[1] * vec3tmp2.coords[0];

        if (i == -0)
        {
            i = 0;
        }
        
        if (j == -0)
        {
            j = 0;
        }
        
        if (k == -0)
        {
            k = 0;
        }

        vec3 res(i, j, k);

        return res;
    }
}
