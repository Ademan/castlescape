#pragma once

#ifndef TERRAIN_TEMPLATES_H
#define TERRAIN_TEMPLATES_H

template <typename index_t>
struct gl_index_t
{
    static const unsigned int gl_type = 0xDEADBEEF;
};

template <typename T>
struct vertex_processor
{
    static void generate(T & v, const int x, const int y,
                         float height);
    static void postprocess(T * vertices,
                            const size_t width, const size_t height);
    static void prepare();
    static void submit(T * vertices);
    static void done();
};

#endif /*TERRAIN_TEMPLATES_H*/