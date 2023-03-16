#include "SDL2/SDL.h"

int main () {
    int drv_count = SDL_GetNumRenderDrivers();
    printf("SDL2 drivers count: %d\n", drv_count);

    for (int i = 0; i < drv_count; i++) {
        SDL_RendererInfo drv_info;
        SDL_GetRenderDriverInfo(i, &drv_info);
        printf("Driver %d: %s\n", i, drv_info.name);
    }

    return 0;
} 
