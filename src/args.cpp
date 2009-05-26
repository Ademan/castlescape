#include <string>
#include "args.h"
#include "light_factory.h"
#include "terrain.h"

using std::string;
using std::cin;
using std::cout;

void construct(Engine & engine)
{
    while (cin)
    {
        string  type;
        cin >> type;
        if (cin.eof()) break;

        cin.clear();

        if (type == constructor_t<OrbitingLight>::name())
        {
            OrbitingLight * light = constructor_t<OrbitingLight>::construct(cin);
            constructor_t<OrbitingLight>::add(engine, light);
        }
        else if (type == constructor_t <Terrain>::name())
        {
            Terrain * terrain = constructor_t<Terrain>::construct(cin);
            constructor_t<Terrain>::add(engine, terrain);
        }
        else
        {
            cout << "Unrecognized type: " << type << endl;
        }
    }
}
