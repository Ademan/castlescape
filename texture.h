#ifndef TEXTURE_H
#define TEXTURE_H

#include <cassert>
#include <SDL/SDL_image.h>
#include <GL/gl.h>

template <GLuint min_filter, GLuint mag_filter>
struct texture_t
{
    GLuint        texture;
    SDL_Surface * image;
    texture_t() {}

    bool open(const char * path)
    {
        image = IMG_Load(path);

        if (!image) return false;

        glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MIN_FILTER,
                        min_filter);

        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MAG_FILTER,
                        mag_filter);

        glTexImage2D(GL_TEXTURE_2D, 0, /*mipmap level*/
                     GL_RGBA, /*internal format*/
                     image->w, image->h,
                     0, /*border*/
                     gl_format(), /*data format*/
                     GL_UNSIGNED_BYTE, /*component data*/
                     image->pixels);
    }
    GLuint  gl_format()
    {
        switch (image->format->BitsPerPixel)
        {
        case 32: return GL_RGBA;
        case 24: return GL_RGB;
        default:
            assert(!"Unrecognized pixel format!");
            return 0;
        }
    }
    ~texture_t()
    {
        if (texture)
            glDeleteTextures(1, &texture);

        if (image)
            SDL_FreeSurface(image);
    }
};

//glEnable(GL_TEXTURE0) ?
//glActiveTexture(GL_TEXTURE0)

#endif /*TEXTURE_H*/
