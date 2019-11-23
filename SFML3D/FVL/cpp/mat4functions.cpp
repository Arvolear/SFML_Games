#include "../hpp/mat4.hpp"
#include "../hpp/vec3.hpp"
#include "../hpp/vec3functions.hpp"
#include "../hpp/mat4functions.hpp"

#include <cmath>
#include <iostream>

using namespace std;

namespace fvl
{
    mat4 add(const mat4 &mat4tmp1, const mat4 &mat4tmp2)
    {
        vector < vector < double > > res;

        for (int i = 0; i < 3; i++)
        {
            vector < double > tmp;
            for (int j = 0; j < 3; j++)
            {
                tmp.push_back(mat4tmp1.cells[i][j] + mat4tmp2.cells[i][j]);
            }

            res.push_back(tmp);
        }

        mat4 ans(res);
        return ans;
    }
    
    mat4 sub(const mat4 &mat4tmp1, const mat4 &mat4tmp2)
    {
        vector < vector < double > > res;

        for (int i = 0; i < 3; i++)
        {
            vector < double > tmp;
            for (int j = 0; j < 3; j++)
            {
                tmp.push_back(mat4tmp1.cells[i][j] - mat4tmp2.cells[i][j]);
            }

            res.push_back(tmp);
        }

        mat4 ans(res);
        return ans;
    }
    
    mat4 mul(const mat4 &mat4tmp1, const mat4 &mat4tmp2)
    {
        vector < vector < double > > res;

        for (int i = 0; i < 3; i++)
        {
            vector < double > tmp;
            for (int j = 0; j < 3; j++)
            {
                tmp.push_back(mat4tmp1.cells[i][j] * mat4tmp2.cells[i][j]);
            }

            res.push_back(tmp);
        }

        mat4 ans(res);
        return ans;
    }
    
    mat4 div(const mat4 &mat4tmp1, const mat4 &mat4tmp2)
    {
        vector < vector < double > > res;

        for (int i = 0; i < 3; i++)
        {
            vector < double > tmp;
            for (int j = 0; j < 3; j++)
            {
                if (mat4tmp2.cells[i][j] == 0)
                {
                    mat4 ans;

                    return ans;
                }

                tmp.push_back(mat4tmp1.cells[i][j] / mat4tmp2.cells[i][j]);
            }

            res.push_back(tmp);
        }

        mat4 ans(res);
        return ans;
    }

    mat4 matrixMul(const mat4 &mat4tmp1, const mat4 &mat4tmp2)
    {
        vector < vector < double > > res;
        
        for (int k = 0; k < 4; k++)
        {
            vector < double > tmp;

            for (int i = 0; i < 4; i++)
            {
                double a = 0;

                for (int j = 0; j < 4; j++)
                {
                    a += mat4tmp1.cells[k][j] * mat4tmp2.cells[j][i];
                }

                tmp.push_back(a);
            }

            res.push_back(tmp);
        }

        mat4 ans(res);

        return ans;
    }

    mat4 scale(const mat4 &mat4tmp, const vec3 &vec3scale)
    {
        mat4 res;

        for (int i = 0; i < 3; i++)
        {
            res.cells[i][i] = vec3scale.coords[i];
        }

        return matrixMul(mat4tmp, res);
    }
    
    mat4 translate(const mat4 &mat4tmp, const vec3 &vec3translate)
    {
        mat4 res;

        for (int i = 0; i < 3; i++)
        {
            res.cells[i][3] = vec3translate.coords[i];
        }

        return matrixMul(mat4tmp, res);
    }

    mat4 rotate(const mat4 &mat4tmp, double angle, const vec3 &vec3axis)
    {
        double radangle = angle * 3.14159265 / 180.0;

        vector < vector < double > > res;
        res.resize(4);

        res[0].push_back(cos(radangle) + vec3axis.x() * vec3axis.x() * (1 - cos(radangle)));
        res[0].push_back(vec3axis.x() * vec3axis.y() * (1 - cos(radangle)) - vec3axis.z() * sin(radangle));
        res[0].push_back(vec3axis.x() * vec3axis.z() * (1 - cos(radangle)) + vec3axis.y() * sin(radangle));
        res[0].push_back(0);

        res[1].push_back(vec3axis.y() * vec3axis.x() * (1 - cos(radangle)) + vec3axis.z() * sin(radangle));
        res[1].push_back(cos(radangle) + vec3axis.y() * vec3axis.y() * (1 - cos(radangle)));
        res[1].push_back(vec3axis.y() * vec3axis.z() * (1 - cos(radangle)) - vec3axis.x() * sin(radangle));
        res[1].push_back(0);

        res[2].push_back(vec3axis.z() * vec3axis.x() * (1 - cos(radangle)) - vec3axis.y() * sin(radangle));
        res[2].push_back(vec3axis.z() * vec3axis.y() * (1 - cos(radangle)) + vec3axis.x() * sin(radangle));
        res[2].push_back(cos(radangle) + vec3axis.z() * vec3axis.z() * (1 - cos(radangle)));
        res[2].push_back(0);

        res[3].push_back(0);
        res[3].push_back(0);
        res[3].push_back(0);
        res[3].push_back(1);

        mat4 ans(res);

        return matrixMul(mat4tmp, ans);
    }
    
    mat4 perspective(double angle, double aspect, double front, double back)
    {
        double radangle = angle * 3.14159265 / 180.0;

        vector < vector < double > > res;
        res.resize(4);

        res[0].push_back((1.0 / tan(radangle / 2.0)) / aspect);
        res[0].push_back(0);
        res[0].push_back(0);
        res[0].push_back(0);

        res[1].push_back(0);
        res[1].push_back(1.0 / tan(radangle / 2.0));
        res[1].push_back(0);
        res[1].push_back(0);

        res[2].push_back(0);
        res[2].push_back(0);
        res[2].push_back((-front - back) / (front - back));
        res[2].push_back((2.0 * back * front) / (front - back));
        
        res[3].push_back(0);
        res[3].push_back(0);
        res[3].push_back(1);
        res[3].push_back(0);

        mat4 ans(res);

        return ans;
    }
    
    mat4 lookAt(const vec3 &vec3CamPos, const vec3 &vec3CamTarget, const vec3 &vec3Up)
    {
        vec3 vec3CamDirection = toOrt(sub(vec3CamTarget, vec3CamPos));

        vec3 vec3CamRight = toOrt(vectorMul(vec3CamDirection, toOrt(vec3Up)));

        vec3 vec3CamUp = toOrt(vectorMul(vec3CamRight, vec3CamDirection));

        vector < vector < double > > first;

        first.resize(4);

        first[0].push_back(vec3CamRight.x());
        first[0].push_back(vec3CamRight.y());
        first[0].push_back(-vec3CamRight.z());
        first[0].push_back(-scalarMul(vec3CamRight, vec3CamPos));
        
        first[1].push_back(vec3CamUp.x());
        first[1].push_back(vec3CamUp.y());
        first[1].push_back(-vec3CamUp.z());
        first[1].push_back(-scalarMul(vec3CamUp, vec3CamPos));
        
        first[2].push_back(vec3CamDirection.x());
        first[2].push_back(vec3CamDirection.y());
        first[2].push_back(-vec3CamDirection.z());
        first[2].push_back(-scalarMul(vec3CamDirection, vec3CamPos));
        
        first[3].push_back(0);
        first[3].push_back(0);
        first[3].push_back(0);
        first[3].push_back(1);

        mat4 mat4First(first);

        return mat4First;
    }
}
