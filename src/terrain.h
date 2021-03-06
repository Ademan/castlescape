#pragma once

#ifndef TERRAIN_H
#define TERRAIN_H

#if 1
    #define TERRAIN_TYPE GL_TRIANGLES
#else
    #define TERRAIN_TYPE GL_TRIANGLE_STRIP
#endif

#include <cassert>
#include <iostream>
#include <boost/algorithm/string.hpp>

using std::cout;
using std::endl; 
#include <cml/cml.h>
#include <SDL/SDL_image.h>

#include "aabb.h"
#include "terrain_templates.h"
#include "types.h"

#include "terrain_vertex.h"
#include "args.h"

#include "util.h"

#include "texture.h"

template <>
struct gl_index_t <unsigned int>
{
    static const unsigned int gl_type = GL_UNSIGNED_INT;
};

template <>
struct gl_index_t <unsigned short>
{
    static const unsigned int gl_type = GL_UNSIGNED_SHORT;
};

template <>
struct gl_index_t <unsigned char>
{
    static const unsigned int gl_type = GL_UNSIGNED_BYTE;
};

template <typename index_t>
struct indexer_t
{
    size_t width;
    indexer_t(const size_t _width): width(_width) {}
    const index_t operator () (const size_t x, const size_t y)
    {
        return x + (y * width);
    }
};

template <typename index_t, unsigned int type>
struct terrain_indices_t
{
    typedef indexer_t<index_t> tindexer;

    index_t *       indices;
    size_t          count;

    terrain_indices_t() {}
    void generate(const size_t width, const size_t height)
    {
        if (type == GL_TRIANGLES)
            triangles(width, height);
        else if (type == GL_TRIANGLE_STRIP)
            strip(width, height);
        else {}
    }
    void draw()
    {
        glDrawElements(type,
                       count,
                       gl_index_t<index_t>::gl_type,
                       indices);
    }
    ~terrain_indices_t()
    {
        if (indices) delete[] indices;
    }

    void print()
    {
        for (index_t * i = indices; i != indices + count; i++)
            cout << *i << endl;
    }
private:
    size_t triangle_index_count(const size_t width, const size_t height)
    {
        return 6 * (width - 1) * (height - 1);
    }
    void triangles(const size_t width, const size_t height)
    {
        //cout << "Generating triangles!" << endl;
        count = triangle_index_count(width, height);
        indices = new index_t[count];

        index_t * i = indices;
        tindexer  in(width);

        for (int y = 0; y < (height - 1); y++)
        {
            for (int x = 0; x < (width - 1); x++)
            {
                *i++ = in(x, y);
                *i++ = in(x + 1, y);
                *i++ = in(x, y + 1);

                *i++ = in(x + 1, y);
                *i++ = in(x + 1, y + 1);
                *i++ = in(x, y + 1);
            }
        }
    }
    size_t strip_index_count(const size_t width, const size_t height)
    {
        return width * 2 * (height - 1) + ((height + 1) / 2) * 3;
    }
    void strip(const size_t width, const size_t height)
    {
        cout << "Generating triangle strips!" << endl;
        count = strip_index_count(width, height);
        indices = new index_t[count];

        index_t * i = indices;
        tindexer  in(width);

        for (int y = 0; y < (height - 1); y++)
        {
            //forwards
            if (y > 0)
            {
                *i++ = in(0, y);
                *i++ = in(0, y + 1);
            }

            *i++ = in(0, y);
            for (int x = 0; x < (width - 1); x++)
            {
                *i++ = in(x, y + 1);
                *i++ = in(x + 1, y);
            }
            *i++ = in(width - 1, y + 1);

            y++;
            if (y >= (height - 1)) break;
            *i++ = in(width - 1, y);
            *i++ = in(width - 1, y + 1);
            for (int x = 0; x < (width - 1); x++)
            {
                *i++ = in(width - x - 1, y + 1);
                *i++ = in(width - x - 2, y);
            }
            *i++ = in(0, y + 1);
        }
    }
};

template <typename vertex_t>
class terrain_t
{
    AABB                box;
    size_t              width;
    size_t              height;

    vertex_t *          vertices;
    size_t              vertex_count;
    texture_t           texture;

    terrain_indices_t <unsigned int, TERRAIN_TYPE>   indices;

public:
    terrain_t(const char * path)
    {
        SDL_Surface * image = IMG_Load(path);
        //FIXME: Don't hard code the grass texture!
        texture.open("media/grass.jpg", GL_LINEAR, GL_LINEAR);

#ifdef _DEBUG
        if (! image)
            cout << "Failed loading: " << path << endl;
        assert(image != NULL);
#endif
        indexer_t<unsigned int> in(image->w);

        vertex_count = image->w * image->h;
        width = image->w;
        height = image->h;

        vertices = new vertex_t[vertex_count];

        for (int y = 0; y < image->h; y++)
            for (int x = 0; x < image->w; x++)
            {
                size_t i = in(x, y) * image->format->BytesPerPixel;
                color_t color = {
                    ((unsigned char *)image->pixels)[i],
                    ((unsigned char *)image->pixels)[i + 1],
                    ((unsigned char *)image->pixels)[i + 2]
                                };
                vertex_processor <vertex_t, unsigned int>::generate(
                        vertices[in(x, y)],
                        x, y,
                        width, height,
                        color);
            }

            smallest_aabb(box, vertices, vertex_count);

        SDL_FreeSurface(image);
        indices.generate(width, height);

        vertex_processor<vertex_t, unsigned int>::postprocess(vertices, vertex_count, indices.indices, indices.count);
    }
    const AABB & get_aabb() const {return box;}
    void render()
    {
        glColor3f(1.0, 1.0, 1.0);

        glEnable(GL_TEXTURE_2D);
        texture.bind(0);
        vertex_processor<vertex_t, unsigned int>::prepare();
        vertex_processor<vertex_t, unsigned int>::submit(vertices);

        indices.draw();
#       ifdef _DEBUG
        draw_aabb(box);
#       endif

        vertex_processor<vertex_t, unsigned int>::done();
        glDisable(GL_TEXTURE_2D);

#       ifdef WIREFRAME
        show_normals(vertices, vertex_count);
		show_wireframe<vertex_t, unsigned int>(vertices, vertex_count, indices.indices, indices.count);
#       endif
    }

    ~terrain_t()
    {
        if (vertices)
            delete[] vertices;
    }

	size_t get_vertex_count() {return vertex_count;}
	size_t get_index_count() {return indices.count;} };

class Terrain: public IRenderable
{
terrain_t<terrain_vertex_t>     terrain;
vec3                            position;
vec3                            scaling;
public:
    Terrain(const char * path,
            const float px, const float py, const float pz,
            const float sx, const float sy, const float sz):
            position(px, py, pz), scaling(sx, sy, sz), terrain(path) {}
    virtual void render();
};

template <>
struct constructor_t<Terrain>
{
    static const char * name() {return "terrain";}
    static Terrain * construct(std::istream & stream)
    {
        float x, y, z, sx, sy, sz;

        std::string heightmap;

        stream >> x >> y >> z >> sx >> sy >> sz;
        
        std::getline(stream, heightmap);
        //stream.ignore(128, '\n');

        boost::trim(heightmap);
#       ifdef _DEBUG
        cout << x << " " << y << " " << z << endl;
        cout << sx << " " << sy << " " << sz << endl;

        cout << "heightmap: \"" << heightmap << '\"' << endl;
#       endif
        return new Terrain(heightmap.c_str(), x, y, z, sx, sy, sz);
    }
    static void add(Engine & engine, Terrain * terrain)
    {
        engine.add_renderable(terrain);
    }
};

#endif /*TERRAIN_H*/
