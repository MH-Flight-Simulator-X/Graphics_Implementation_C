#include "render.h"
#include <stdlib.h>
#include <stdio.h>

int render_init(RenderContext_t* rc) {
    rc->framebuffer = (int*)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(int));
    rc->zbuffer = (float*)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(float));

    rc->camera = (Camera_t*)malloc(sizeof(Camera_t));
    camera_init(rc->camera, (vec2){SCREEN_WIDTH, SCREEN_HEIGHT});

    if (rc->framebuffer == NULL || rc->zbuffer == NULL || rc->camera == NULL) {
        return 1;
    }
    return 0;
}

void render_clear(RenderContext_t* rc, int clear_color) {
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        rc->zbuffer[i] = 1.0f; // Max depth
    }
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        rc->framebuffer[i] = clear_color;
    }
}

void render_set_pixel(RenderContext_t* rc, int x, int y, int r, int g, int b) {
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return;
    }

    int index = y * SCREEN_WIDTH + x;
    rc->framebuffer[index] = (int)r << 16 | (int)g << 8 | (int)b;
}

int render_test_set_depth(RenderContext_t* rc, int x, int y, float z) {
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return 0;
    }
    int index = y * SCREEN_WIDTH + x;
    if (rc->zbuffer[index] < z) {
        return 0;
    }
    rc->zbuffer[index] = z;
    return 1;
}

void render_destroy(RenderContext_t* rc) {
    free(rc->framebuffer);
    free(rc->zbuffer);
    free(rc->camera);
}
