#include <stdlib.h>
#include <signal.h>
#include "../gfx.h"

#define DISPLAY_WIDTH  1280
#define DISPLAY_HEIGHT 720

/// Render some white noise.
/// @param context graphical context to use.
static void render(gfx_context_t *context) {
    gfx_clear(context, GFX_COL_BLACK);

    for (int i = 0; i < DISPLAY_WIDTH*DISPLAY_HEIGHT/10; i++) {
        int x = rand() % context->width;
        int y = rand() % context->height;
        uint32_t intensity = rand() % 256;  // 8-bit per color channel
        pixel_t color = GFX_RGB(intensity,intensity,intensity);
        gfx_putpixel(context, x, y, color);
    }
}

/// Program entry point.
/// @return the application status code (0 if success).
int main() {
    gfx_context_t *ctxt = gfx_create("Basic Example", DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if (!ctxt) {
        fprintf(stderr, "Graphics initialization failed!\n");
        return EXIT_FAILURE;
    }

    while (gfx_keypressed() != SDLK_ESCAPE) {
        render(ctxt);
        gfx_copy_pixels(ctxt);
        gfx_present(ctxt);
    }

    gfx_destroy(ctxt);
    return EXIT_SUCCESS;
}
