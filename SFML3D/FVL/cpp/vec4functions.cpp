#include "../hpp/vec4.hpp"
#include "../hpp/mat4.hpp"
#include "../hpp/vec4functions.hpp"

using namespace std;

namespace fvl
{
    vec4 add(const vec4 &vec4tmp1, const vec4 &vec4tmp2)
    {
        vec4 res(vec4tmp1.coords[0] + vec4tmp2.coords[0], vec4tmp1.coords[1] + vec4tmp2.coords[1], vec4tmp1.coords[2] + vec4tmp2.coords[2]);

        return res;
    }
    
    vec4 add(const vec4 &vec4tmp, double d)
    {
        vec4 res = add(vec4tmp, vec4(d, d, d));

        return res;
    }

    vec4 sub(const vec4 &vec4tmp1, const vec4 &vec4tmp2)
    {
        vec4 res(vec4tmp1.coords[0] - vec4tmp2.coords[0], vec4tmp1.coords[1] - vec4tmp2.coords[1], vec4tmp1.coords[2] - vec4tmp2.coords[2]);

        return res;
    }
    
    vec4 sub(const vec4 &vec4tmp, double d)
    {
        vec4 res = sub(vec4tmp, vec4(d, d, d));

        return res;
    }
    
    vec4 mul(const vec4 &vec4tmp1, const vec4 &vec4tmp2)
    {
        vec4 res(vec4tmp1.coords[0] * vec4tmp2.coords[0], vec4tmp1.coords[1] * vec4tmp2.coords[1], vec4tmp1.coords[2] * vec4tmp2.coords[2]);

        return res;
    }
    
    vec4 mul(const vec4 &vec4tmp, double d)
    {
        vec4 res = mul(vec4tmp, vec4(d, d, d));

        return res;
    }

    vec4 div(const vec4 &vec4tmp1, const vec4 &vec4tmp2)
    {
        for (int i = 0; i < 3; i++)
        {
            if (vec4tmp2.coords[i] == 0)
            {
                vec4 err(0, 0, 0);

                return err;
            }
        }

        vec4 res(vec4tmp1.coords[0] / vec4tmp2.coords[0], vec4tmp1.coords[1] / vec4tmp2.coords[1], vec4tmp1.coords[2] / vec4tmp2.coords[2]);

        return res;
    }
    
    vec4 div(const vec4 &vec4tmp, double d)
    {
        if (d == 0)
        {
            return vec4();
        }

        vec4 res = div(vec4tmp, vec4(d, d, d));

        return res;
    }

    vec4 toOrt(const vec4 &vec4tmp)
    {
        double l = vec4tmp.length();
        
        vector < double > vec4tmpcoords = vec4tmp.getCoords();

        vec4 res(vec4tmpcoords[0] / l, vec4tmpcoords[1] / l, vec4tmpcoords[2] / l);
        
        return res;
    }
    
    vec4 normalize(const vec4 &vec4tmp)
    {
        vector < double > res;

        for (int i = 0; i < 3; i++)
        {
            if (vec4tmp.coords[3] != 0)
            {
                res.push_back(double(vec4tmp.coords[i] / vec4tmp.coords[3]));
            }
            else
            {
                res.push_back(double(vec4tmp.coords[i]));
            }
        }

        vec4 ans(res[0], res[1], res[2]);

        return ans;
    }
    
    vec4 reflect(const vec4 &vec4tmp1, const vec4 &vec4tmp2)
    {
        double dp = scalarMul(vec4tmp1, vec4tmp2);

        vec4 res = sub(vec4tmp1, mul(vec4tmp2, 2 * dp));

        return res;
    }
    
    vec4 toWindow(const vec4 &vec4tmp, double width, double height)
    {
        double wx = (vec4tmp.x() + 1) * width / 2.0;     
        double wy = (vec4tmp.y() + 1) * height / 2.0;

        vec4 res(wx, wy, vec4tmp.z());
        return res;
    }

    double scalarMul(const vec4 &vec4tmp1, const vec4 &vec4tmp2)
    {
        double res = 0;

        for (int i = 0; i < 3; i++)
        {
            res += vec4tmp1.coords[i] * vec4tmp2.coords[i];
        }

        return res;
    }

    vec4 vectorMul(const vec4 &vec4tmp1, const vec4 &vec4tmp2)
    {
        double i = vec4tmp1.coords[1] * vec4tmp2.coords[2] - vec4tmp1.coords[2] * vec4tmp2.coords[1];
        
        double j = vec4tmp1.coords[2] * vec4tmp2.coords[0] - vec4tmp1.coords[0] * vec4tmp2.coords[2];
        
        double k = vec4tmp1.coords[0] * vec4tmp2.coords[1] - vec4tmp1.coords[1] * vec4tmp2.coords[0];

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

        vec4 res(i, j, k);

        return res;
    }

    vec4 matrixMul(const mat4 &mat4tmp, const vec4 &vec4tmp)
    {
        vector < double > tmp;
        tmp.resize(4);

        for (int i = 0; i < 4; i++)
        {
            double val = 0;
            for (int j = 0; j < 4; j++)
            {
                val += mat4tmp.cells[i][j] * vec4tmp.coords[j];
            }

            tmp[i] = val;
        }

        vec4 res(tmp[0], tmp[1], tmp[2], tmp[3]);

        return res;
    }
}
