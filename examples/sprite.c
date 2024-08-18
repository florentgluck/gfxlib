#include <stdlib.h>
#include <signal.h>
#include "../gfx.h"

#define DISPLAY_WIDTH  640
#define DISPLAY_HEIGHT 360

/// Render an animated "plasma".
/// Converted from an ancient dirty Turbo Pascal code I wrote in the early 90's ;-)
/// @param context Graphical context to use.
static void render_plasma(gfx_context_t *context) {
    static const int delay = 15;
    static int delay_cnt = 0;
    static pixel_t palette[256];
    static int u = 0, v = 0;
    static bool first_run = true;

    int sintab[256] = {
        127,130,133,136,139,143,146,149,152,155,158,161,164,167,170,173,176,179,182,184,187,190,193,
        195,198,200,203,205,208,210,213,215,217,219,221,224,226,228,229,231,233,235,236,238,239,241,
        242,244,245,246,247,248,249,250,251,251,252,253,253,254,254,254,254,254,255,254,254,254,254,
        254,253,253,252,251,251,250,249,248,247,246,245,244,242,241,239,238,236,235,233,231,229,228,
        226,224,221,219,217,215,213,210,208,205,203,200,198,195,193,190,187,184,182,179,176,173,170,
        167,164,161,158,155,152,149,146,143,139,136,133,130,127,124,121,118,115,111,108,105,102,99,
        96,93,90,87,84,81,78,75,72,70,67,64,61,59,56,54,51,49,46,44,41,39,37,35,33,30,28,26,25,23,21,
        19,18,16,15,13,12,10,9,8,7,6,5,4,3,3,2,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,2,3,3,4,5,6,7,8,9,10,12,
        13,15,16,18,19,21,23,25,26,28,30,33,35,37,39,41,44,46,49,51,54,56,59,61,64,67,70,72,75,78,81,
        84,87,90,93,96,99,102,105,108,111,115,118,121,124};

    if (first_run) {
        first_run = false;
        int i,j,k;
        for (i = 0; i < 256; i++) {
            j = sintab[(i+64) & 255] >> 2;
            k = sintab[i] >> 2;
            palette[i] = GFX_RGB(j*4,k*4,30*4);
        }
    }

    int c,c1,c2,w,t1,t2;
    w = sintab[((v & 255)+64) & 255] >> 2;

    for (int j = 0; j < DISPLAY_HEIGHT/2; j++) {
        for (int i = 0; i < DISPLAY_WIDTH/2; i++) {
            c1 = sintab[(u-w+j) & 255];
            c2 = sintab[(((v+j) & 255)+64) & 255];
            t1 = i+c1-sintab[u & 255];
            t2 = j+c2;
            c = sintab[t1 & 255]-sintab[((t2 & 255)+64) & 255]-sintab[((t1 & 255)+64) & 255];
            pixel_t col = palette[(c & 254)+1];
            gfx_putpixel(context, i*2+1,j*2,col);
            gfx_putpixel(context, i*2,j*2+1,col);
            gfx_putpixel(context, i*2,j*2,col);
            gfx_putpixel(context, i*2+1,j*2+1,col);
        }
    }

    if ((++delay_cnt % delay) == 0) { u--; v++; }
}

/// Program entry point.
/// @return the application status code (0 if success).
int main() {
    gfx_context_t *ctxt = gfx_create("Sprite Example", DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if (!ctxt) {
        fprintf(stderr, "Graphics initialization failed!\n");
        return EXIT_FAILURE;
    }

    SDL_Texture *sprite_tex = gfx_loadsprite(ctxt, "examples/tux_jedi.png");
    if (!sprite_tex) {
        fprintf(stderr, "Failed loading sprite!\n");
        return EXIT_FAILURE;
    }

    bool quit = false;
    int x = 50, y = 50, speed = 4;

    while (!quit) {
        render_plasma(ctxt);
        gfx_copy_pixels(ctxt);
        gfx_rendersprite(ctxt, sprite_tex, x, y, 128, 128);
        gfx_present(ctxt);

        SDL_Keycode key = gfx_keypressed();
        switch (key) {
            case SDLK_ESCAPE:
                quit = true;
                break;
            case SDLK_UP:
                y -= speed;
                break;
            case SDLK_DOWN:
                y += speed;
                break;
            case SDLK_LEFT:
                x -= speed;
                break;
            case SDLK_RIGHT:
                x += speed;
                break;
        }
    }

    gfx_destroy(ctxt);
    return EXIT_SUCCESS;
}
