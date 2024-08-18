#ifndef _GFX_H_
#define _GFX_H_

#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define GFX_RGB(r,g,b) ((pixel_t){b,g,r,0})

#define GFX_COL_BLACK  GFX_RGB(0,0,0)
#define GFX_COL_RED    GFX_RGB(0,0,255)
#define GFX_COL_GREEN  GFX_RGB(0,255,0)
#define GFX_COL_BLUE   GFX_RGB(255,0,0)
#define GFX_COL_CYAN   GFX_RGB(255,255,0)
#define GFX_COL_PURPLE GFX_RGB(255,0,255)
#define GFX_COL_YELLOW GFX_RGB(0,255,255)
#define GFX_COL_WHITE  GFX_RGB(255,255,255)

// Structure of a pixel: 32-bits (ARGB)
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

gfx_context_t* gfx_create(char *text, int width, int height);
void gfx_destroy(gfx_context_t *ctxt);
void gfx_putpixel(gfx_context_t *ctxt, int x, int y, pixel_t color);
void gfx_clear(gfx_context_t *ctxt, pixel_t color);
void gfx_copy_pixels(gfx_context_t *ctxt);
void gfx_present(gfx_context_t *ctxt);
SDL_Keycode gfx_keypressed();
SDL_Texture *gfx_loadsprite(gfx_context_t *ctxt, char *filename);
void gfx_rendersprite(gfx_context_t *ctxt, SDL_Texture *sprite, int x, int y, int sprite_width, int sprite_height);

#endif
