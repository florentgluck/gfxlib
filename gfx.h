#ifndef _GFX_H_
#define _GFX_H_

#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define GFX_COL_BLACK  (pixel_t){0,0,0,0}
#define GFX_COL_RED    (pixel_t){0,0,255,0}
#define GFX_COL_GREEN  (pixel_t){0,255,0,0}
#define GFX_COL_BLUE   (pixel_t){255,0,0,0}
#define GFX_COL_CYAN   (pixel_t){255,255,0,0}
#define GFX_COL_PURPLE (pixel_t){255,0,255,0}
#define GFX_COL_YELLOW (pixel_t){0,255,255,0}
#define GFX_COL_WHITE  (pixel_t){255,255,255,0}

typedef struct __attribute__ ((__packed__)) {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t a;
} pixel_t;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *pixels_texture;
    pixel_t *pixels;
    int width;
    int height;
} gfx_context_t;

void gfx_putpixel(gfx_context_t *ctxt, int x, int y, pixel_t color);
void gfx_clear(gfx_context_t *ctxt, pixel_t color);
gfx_context_t* gfx_create(char *text, int width, int height);
void gfx_destroy(gfx_context_t *ctxt);
void gfx_copy_pixels(gfx_context_t *ctxt);
void gfx_present(gfx_context_t *ctxt);
SDL_Keycode gfx_keypressed();

#endif
