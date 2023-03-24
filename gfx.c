/// @file gfx.c
/// @author Florent Gluck
/// @date 2016-2020
/// Helper routines to render pixels in fullscreen graphic mode.
/// Requires the SDL2 library.

#include "gfx.h"
#include <signal.h>

/// Create a fullscreen graphic window.
/// @param title Title of the window.
/// @param width Width of the window in pixels.
/// @param height Height of the window in pixels.
/// @return a pointer to the graphic context or NULL if it failed.
gfx_context_t* gfx_create(char *title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "%s", SDL_GetError());
        goto error;
    }
    // Restore SIGINT's default behavior so that we can use CTRL-C to stop the program
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &act, NULL) < 0) {
		perror("sigaction");
		exit(1);
	}

    // These a just for reference:
    // SDL_SetHint(SDL_HINT_NO_SIGNAL_HANDLERS, "1");
    // SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");  // opengl, opengles2, software
    // SDL_SetHint(SDL_HINT_RENDER_OPENGL_SHADERS, "0");
    // SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
    // SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_PING, "0");
    // SDL_SetHint(SDL_HINT_VIDEO_X11_XVIDMODE, "0");

    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    uint32_t *pixels = malloc(width*height*sizeof(uint32_t));
    gfx_context_t *ctxt = malloc(sizeof(gfx_context_t));

    if (!window || !renderer || !texture || !pixels || !ctxt) goto error;

    ctxt->renderer = renderer;
    ctxt->texture = texture;
    ctxt->window = window;
    ctxt->width = width;
    ctxt->height = height;
    ctxt->pixels = pixels;

    SDL_ShowCursor(SDL_DISABLE);
    gfx_clear(ctxt, GFX_BLACK);
    return ctxt;

error:
    return NULL;
}

/// Draw a pixel in the specified graphic context.
/// @param ctxt Graphic context where the pixel is to be drawn.
/// @param x X coordinate of the pixel.
/// @param y Y coordinate of the pixel.
/// @param color Color of the pixel.
void gfx_putpixel(gfx_context_t *ctxt, int x, int y, uint32_t color) {
    if (x < ctxt->width && y < ctxt->height)
        ctxt->pixels[ctxt->width*y+x] = color;
}

/// Clear the specified graphic context.
/// @param ctxt Graphic context to clear.
/// @param color Color to use.
void gfx_clear(gfx_context_t *ctxt, uint32_t color) {
    int n = ctxt->width*ctxt->height;
    while (n)
        ctxt->pixels[--n] = color;
}

/// Display the graphic context.
/// @param ctxt Graphic context to clear.
void gfx_present(gfx_context_t *ctxt) {
    SDL_UpdateTexture(ctxt->texture, NULL, ctxt->pixels, ctxt->width*sizeof(uint32_t));
    SDL_RenderCopy(ctxt->renderer, ctxt->texture, NULL, NULL);
    SDL_RenderPresent(ctxt->renderer);
}

/// Destroy a graphic window.
/// @param ctxt Graphic context of the window to close.
void gfx_destroy(gfx_context_t *ctxt) {
    SDL_ShowCursor(SDL_ENABLE);
    SDL_DestroyTexture(ctxt->texture);
    SDL_DestroyRenderer(ctxt->renderer);
    SDL_DestroyWindow(ctxt->window);
    free(ctxt->pixels);
    ctxt->texture = NULL;
    ctxt->renderer = NULL;
    ctxt->window = NULL;
    ctxt->pixels = NULL;
    SDL_Quit();
    free(ctxt);
}

/// If a key was pressed, returns its key code (non blocking call).
/// List of key codes: https://wiki.libsdl.org/SDL_Keycode
/// @return the key that was pressed or 0 if none was pressed.
SDL_Keycode gfx_keypressed() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN)
            return event.key.keysym.sym;
    }
    return 0;
}

