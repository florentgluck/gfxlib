#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "gfx.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

#define REFRESH_RATE  300

/// Render some white noise.
/// @param context graphical context to use.
static void render(gfx_context_t *context) {
    int x, y;
    uint32_t button = SDL_GetMouseState(&x, &y);
    // Left button: draw pixel at mouse position
    if (button & 1) {
        gfx_putpixel(context, x, y, GFX_GREEN);
    }
    // Right button: clear screen
    else if (button & 4) {
        gfx_clear(context, GFX_BLACK);
    }
}

/// Program entry point.
/// @return the application status code (0 if success).
int main() {
    gfx_context_t *ctxt = gfx_create("Example", SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!ctxt) {
        fprintf(stderr, "Graphics initialization failed!\n");
        return EXIT_FAILURE;
    }

    // Create and show a "cross" cursor
    SDL_Cursor* cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
    SDL_SetCursor(cursor);
    SDL_ShowCursor(SDL_ENABLE);

    struct timespec ts = { 
        .tv_sec = 0,
        .tv_nsec = 999999999  // 1 second delay (1 Hz)
    };

    ts.tv_nsec /= REFRESH_RATE;

    while (gfx_keypressed() != SDLK_ESCAPE) {
        render(ctxt);
        gfx_present(ctxt);
        nanosleep(&ts, NULL);
    }

    SDL_FreeCursor(cursor);
    gfx_destroy(ctxt);
    return EXIT_SUCCESS;
}
