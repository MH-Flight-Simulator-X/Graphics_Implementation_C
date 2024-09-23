#pragma once
#include "camera.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

typedef struct {
    int* framebuffer;
    float* zbuffer;
    Camera_t* camera;
} RenderContext_t;

int render_init(RenderContext_t* render_context);

void render_clear(RenderContext_t* render_context, int clear_color);

void render_set_pixel(RenderContext_t* rc, int x, int y, int r, int g, int b);

int render_test_set_depth(RenderContext_t* render_context, int x, int y, float z);

void render_destroy(RenderContext_t* render_context);
