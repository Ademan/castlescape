#include <string>
#include "args.h"
#include "light.h"

using std::string;
using std::cin;

void construct(Engine & engine)
{
    while (cin)
    {
        string  type;
        cin >> type;

        if (type == "orbit_light")
        {
            string axis;
            cin >> axis;

            OrbitingLight::Axis a;

            if (axis == "xy")
             a = OrbitingLight::XY;
            else if (axis == "xz")
             a = OrbitingLight::XZ;   
            else
             a = OrbitingLight::ZY;

            float radius;
            float r, g, b;

            cin >> radius;
            cin >> r >> g >> b;

            //FIXME: introduces sweet memory leak
            OrbitingLight * light = new OrbitingLight(a, radius, r, g, b);

            engine.add_render_state(light);
            engine.add_entity(light);
        }
    }
}
