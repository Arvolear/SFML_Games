#ifndef MAT4_HPP
#define MAT4_HPP

#include <vector>

using namespace std;

namespace fvl
{
    class mat4
    {
        public:
            vector < vector < double > > cells;

        public:
            mat4();
            
            mat4(vector < vector < double > > def);

            
            mat4 operator=(const mat4 &mat4tmp);

            mat4(const mat4 &mat4tmp);


            //void setCell(int i, int j, double val);

            vector < vector < double > > getMat() const; 

            ~mat4();
    };
}

#endif
