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
        cout << "type: " << type << endl;

        //cin.clear();

        if (type == constructor_t<OrbitingLight>::name())
            factory_t<OrbitingLight>::add(engine, cin);
        else if (type == constructor_t <Terrain>::name())
            factory_t<Terrain>::add(engine, cin);
        else if (type == constructor_t <RenderableOrbitingLight>::name())
            factory_t<RenderableOrbitingLight>::add(engine, cin);
        else
        {
            cout << "Unrecognized type: " << type << endl;
            cin.ignore(1024, '\n');
        }
    }
}
