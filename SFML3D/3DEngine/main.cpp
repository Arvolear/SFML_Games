#include "stuff.hpp"
#include "generate.hpp"
#include "fpstracker.hpp"
#include "camera.hpp"
#include "zbuffer.hpp"
#include "graphics.hpp"

using namespace std;
using namespace sf;
using namespace fvl;

int main()
{
    Graphics *G = new Graphics();

    G->start();

    delete G;
    return 0;
}
