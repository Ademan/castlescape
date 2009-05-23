#include "util.h"

static SDL_Event quit_event = {SDL_QUIT};

void send_quit(int code) //ignores the code for the moment
{
    SDL_PushEvent(&quit_event);
}
