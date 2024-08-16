#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "../gfx.h"

#define DISPLAY_WIDTH  1280
#define DISPLAY_HEIGHT 720

/// Draw a "cross" when the mouse's left button is pressed,
/// or clear the screen when the right is pressed.
/// @param context graphical context to use.
static void render(gfx_context_t *context) {
    int x, y;
    uint32_t button = SDL_GetMouseState(&x, &y);

    // Scale mouse position to window size
    int width, height;
    SDL_GetWindowSize(context->window, &width, &height);
    float sx = ((float)width/DISPLAY_WIDTH);
    float sy = ((float)height/DISPLAY_HEIGHT);
    x /= sx;
    y /= sy;

    // Left button: draw a "cross" at mouse position
    if (button & 1) {
        gfx_putpixel(context, x,   y, (pixel_t){255,255,0,0});
        gfx_putpixel(context, x-1, y, (pixel_t){200,200,0,0});
        gfx_putpixel(context, x+1, y, (pixel_t){200,200,0,0});
        gfx_putpixel(context, x, y-1, (pixel_t){200,200,0,0});
        gfx_putpixel(context, x, y+1, (pixel_t){200,200,0,0});
    }
    // Right button: clear screen
    else if (button & 4) {
        gfx_clear(context, GFX_COL_BLACK);
    }
}

/// Program entry point.
/// @return the application status code (0 if success).
int main() {
    gfx_context_t *ctxt = gfx_create("Mouse Example", DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if (!ctxt) {
        fprintf(stderr, "Graphics initialization failed!\n");
        return EXIT_FAILURE;
    }

    // Create and show a "cross" cursor
    SDL_Cursor* cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
    SDL_SetCursor(cursor);
    SDL_ShowCursor(SDL_ENABLE);

    while (gfx_keypressed() != SDLK_ESCAPE) {
        render(ctxt);
        gfx_copy_pixels(ctxt);
        gfx_present(ctxt);
    }

    SDL_FreeCursor(cursor);
    gfx_destroy(ctxt);
    return EXIT_SUCCESS;
}
