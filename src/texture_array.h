#ifndef TEXTURE_ARRAY_H
#define TEXTURE_ARRAY_H

#include <GL/gl.h>
#include <vector>
#include "texture.h"

class TextureArray
{
    typedef std::vector <texture_t> array;
    typedef array::iterator         iter;
    array   textures;
public:
    TextureArray();
    void append(texture_t & tex)
    {
        textures.push_back(tex);
    }
    void bind()
    {
        for (int i = 0; i < textures.size(); i++)
        {
            textures[i].bind(i);
        }
    }
    void unbind()
    {
        for (int i = 0; i < textures.size(); i++)
        {
            glDisable(GL_TEXTURE0 + i);
        }
    }
};

#endif /*TEXTURE_ARRAY_H*/
