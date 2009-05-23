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
using std::cout;
using std::endl;

#include <cml/cml.h>
#include <SDL/SDL_image.h>

struct vertex_t
{
    float x, y, z;
    float r, g, b;
    //float s, t; /*texture coordinates*/
    //float nx, ny, nz; /*normal coordinates*/
};

template <typename index_t>
struct gl_index_t
{
    static const unsigned int gl_type = 0xDEADBEEF;
};

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

#define INDEX(x, y, w) ((x) + (y) * (w))

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
        cout << "Generating triangles!" << endl;
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

class Terrain
{
    size_t              width;
    size_t              height;

    vertex_t *          vertices;
    size_t              vertex_count;

    terrain_indices_t <unsigned int, TERRAIN_TYPE>   indices;

public:
    Terrain(const char * path)
    {
        SDL_Surface * image = IMG_Load(path);

        assert(image != NULL);
        indexer_t<unsigned int> in(image->w);

        vertex_count = image->w * image->h;
        width = image->w;
        height = image->h;

        vertices = new vertex_t[vertex_count];

        float highest = -999999.0f;
        for (int y = 0; y < image->h; y++)
            for (int x = 0; x < image->w; x++)
            {
                vertex_t * v = vertices + in(x, y);

                //v->x = x * 2 - width;
                v->x = x * 2.0 - width;
                int red = ((unsigned char *)image->pixels)[in(x, y) * 4];

                v->y = red / 16.0;
                if (v->y > highest) highest = v->y;

                //v->z = y * 2 - height;
                v->z = y * 2.0 - height;

                v->r = v->g = v->b = red / 256.0;

                if (v->r < 0.1)
                {
                    float orig = (v->r + 0.4) * 1.5;
                    /*v->r = v->g = v->r /16;
                    v->b = 0.7;*/

                    v->r = 0xff / 256.0;
                    v->g = 0x15 / 256.0;
                    v->b = 0x00 / 256.0;

                    v->r *= orig;
                    v->b *= orig;
                    v->g *= orig;
                }
                else if (v->r < 0.5)
                {
                    float orig = v->r * 1.5;
                    /*v->r = v->b = v->r /16;
                    v->g = 0.7;*/
                    v->r = 0x77 / 256.0;
                    v->g = 0x4C / 256.0;
                    v->b = 0x0f / 256.0;

                    v->r *= orig;
                    v->b *= orig;
                    v->g *= orig;

                }
                else
                {
                    float orig = v->r * 1.5;
                    v->r = v->g = v->b = orig * 0.5;
                }
            }

            for (int i = 0; i < vertex_count; i++)
            {
                vertices[i].y -= highest;
            }

        SDL_FreeSurface(image);
        indices.generate(width, height);
    }
    void render()
    {
        glColor3f(1.0, 1.0, 1.0);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        glVertexPointer(3, GL_FLOAT, sizeof(vertex_t), &(vertices->x));
        glColorPointer(3, GL_FLOAT, sizeof(vertex_t), &(vertices->r));

        indices.draw();

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
};

#endif /*TERRAIN_H*/
