#include "../hpp/mat4.hpp"

namespace fvl
{
    mat4::mat4()
    {
        cells.resize(4);

        for (int i = 0; i < 4; i++)
        {
            cells[i].resize(4);
        }
        
        for (int i = 0; i < 4; i++)
        {
            cells[i][i] = 1;
        }
    }
    
    mat4::mat4(vector < vector < double > > def)
    {
        if (def.size() == 4)
        {
            for (int i = 0; i < 4; i++)
            {
                if (def[i].size() != 4)
                {
                    return;
                }
            }

            cells = def;
        }
    }


    mat4 mat4::operator=(const mat4 &mat4tmp)
    {
        this->cells = mat4tmp.getMat();

        return *this;
    }

    mat4::mat4(const mat4 &mat4tmp)
    {
        this->cells = mat4tmp.getMat();  
    }

            
    vector < vector < double > > mat4::getMat() const
    {
        return this->cells;
    }

    mat4::~mat4(){}
}
