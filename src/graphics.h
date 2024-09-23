#pragma once
#include "graphics_math.h"
#include "render.h"
#include "mesh.h"

void graphics_render_model(RenderContext_t* rc, Model_t* model);

void vertex_shader(vec3* vertices, int vertex_count, mat4* mvp, vec4* out_vertices);

void vertex_post_processor(vec4* vertices, int vertex_count, int width, int height, float zfar, float znear, vec3* out);

void primitive_assembler(vec3* vertices, int vertex_count, int* indices, int index_count, vec3* camera_pos, Triangle_t* out);

// TODO: Add binning
// void binner(Triangle_t* triangles, int triangle_count, int width, int height, int* out);

static inline void barycentric(vec2* v0, vec2* v1, vec2* v2, vec2* p, vec3* bc);

// Rasterizer and fragment shader in one
void rasterizer(Triangle_t* triangles, int triangle_count, RenderContext_t* rc);
