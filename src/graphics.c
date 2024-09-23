#include "graphics.h"
#include <stdlib.h>

void graphics_render_model(RenderContext_t* rc, Model_t* model) {
    mat4 vp = mat4_mat4_mul_ret(&rc->camera->projection_matrix, &rc->camera->view_matrix);
    mat4 mvp = mat4_mat4_mul_ret(&vp, &model->model_matrix);

    vec4* out_vertices = (vec4*)malloc(model->mesh.vertex_count * sizeof(vec4));
    vertex_shader(model->mesh.vertices, model->mesh.vertex_count, &mvp, out_vertices);

    vec3* post_processed_vertices = (vec3*)malloc(model->mesh.vertex_count * sizeof(vec3));
    vertex_post_processor(out_vertices, model->mesh.vertex_count, rc->camera->resolution.x, rc->camera->resolution.y, rc->camera->zfar, rc->camera->znear, post_processed_vertices);

    Triangle_t* triangles = (Triangle_t*)malloc(model->mesh.index_count / 3 * sizeof(Triangle_t));
    primitive_assembler(post_processed_vertices, model->mesh.vertex_count, model->mesh.indices, model->mesh.index_count, &rc->camera->position, triangles);

    rasterizer(triangles, model->mesh.index_count / 3, rc);

    // Free resources
    free(out_vertices);
    free(post_processed_vertices);
    free(triangles);
}

void vertex_shader(vec3* vertices, int vertex_count, mat4* mvp, vec4* out_vertices) {
    for (int i = 0; i < vertex_count; i++) {
        vec4 vert4 = (vec4){vertices[i].x, vertices[i].y, vertices[i].z, 1.0f};
        out_vertices[i] = mat4_vec4_mul(mvp, &vert4);
    }
}

void vertex_post_processor(vec4* vertices, int vertex_count, int width, int height, float zfar, float znear, vec3* out) {
    for (int i = 0; i < vertex_count; i++) {
        out[i].x = (vertices[i].x + 1.0f) * width / 2.0f;
        out[i].y = (1.0f - vertices[i].y) * height / 2.0f;
        out[i].z = vertices[i].z / (zfar - znear);
    }
}

void primitive_assembler(vec3* vertices, int vertex_count, int* indices, int index_count, vec3* camera_pos, Triangle_t* out) {
    vec3 colors[12] = {
        (vec3){1.0f,   0.702f, 0.729f},   // Light Pink
        (vec3){1.0f,   0.875f, 0.729f},   // Peach
        (vec3){1.0f,   1.0f,   0.729f},   // Light Yellow
        (vec3){0.729f, 1.0f,   0.788f},   // Mint Green
        (vec3){0.729f, 0.882f, 1.0f},     // Light Sky Blue
        (vec3){0.882f, 0.729f, 1.0f},     // Lavender
        (vec3){1.0f,   0.765f, 0.890f},   // Pastel Rose
        (vec3){0.765f, 1.0f,   0.867f},   // Pale Aqua
        (vec3){1.0f,   0.843f, 0.765f},   // Pastel Orange
        (vec3){1.0f,   0.961f, 0.729f},   // Pale Lemon
        (vec3){0.843f, 1.0f,   0.729f},   // Pale Lime Green
        (vec3){0.729f, 0.765f, 1.0f}      // Pastel Purple
    };

    for (int i = 0; i < index_count / 3; i++) {
        int ibuffer_offset = 3 * i;
        Triangle_t* t = &out[i];

        // Do backface culling
        vec3 v01 = vec3_sub(&vertices[indices[ibuffer_offset + 1]], &vertices[indices[ibuffer_offset]]);
        vec3 v02 = vec3_sub(&vertices[indices[ibuffer_offset + 2]], &vertices[indices[ibuffer_offset]]);
        vec3 n = vec3_cross(&v01, &v02);

        vec3 a = vertices[indices[ibuffer_offset]];
        vec3 b = vertices[indices[ibuffer_offset+1]];
        vec3 c = vertices[indices[ibuffer_offset+2]];

        vec3 v0 = {(a.x + b.x + c.x) / 3.0f, (a.y + b.y + c.y) / 3.0f, (a.z + b.z + c.z) / 3.0f};
        vec3 cam_to_pos = vec3_sub(camera_pos, &v0);
        float dp = vec3_dot(&cam_to_pos, &n);

        // Backface culling happens here
        if (dp >= 0) {
            t->valid = 0;
            continue;
        }
        t->valid = 1;

        // Create triangle
        t->v[0] = vertices[indices[ibuffer_offset]];
        t->v[1] = vertices[indices[ibuffer_offset + 1]];
        t->v[2] = vertices[indices[ibuffer_offset + 2]];
        t->color = colors[i % 12]; // TODO: Add color
        t->normal = n;

        // Calculate bounding box
        t->bb_tl.x = fminf(fminf(t->v[0].x, t->v[1].x), t->v[2].x);
        t->bb_tl.y = fminf(fminf(t->v[0].y, t->v[1].y), t->v[2].y);
        t->bb_br.x = fmaxf(fmaxf(t->v[0].x, t->v[1].x), t->v[2].x);
        t->bb_br.y = fmaxf(fmaxf(t->v[0].y, t->v[1].y), t->v[2].y);
    }
}

// TODO: Add binning
// void binner(Triangle_t* triangles, int triangle_count, int width, int height, int* out);

static inline void barycentric(vec2* v0, vec2* v1, vec2* v2, vec2* p, vec3* bc) {
    vec2 v10 = {v1->x - v0->x, v1->y - v0->y};
    vec2 v21 = {v2->x - v0->x, v2->y - v0->y};
    vec2 vp0 = {p->x - v0->x, p->y - v0->y};

    double d00 = v10.x * v10.x + v10.y * v10.y;
    double d01 = v10.x * v21.x + v10.y * v21.y;
    double d11 = v21.x * v21.x + v21.y * v21.y;
    double d20 = vp0.x * v10.x + vp0.y * v10.y;
    double d21 = vp0.x * v21.x + vp0.y * v21.y;

    double det = (d00 * d11 - d01 * d01);
    bc->y = (d11 * d20 - d01 * d21) / det;
    bc->z = (d00 * d21 - d01 * d20) / det;
    bc->x = 1.0f - bc->y - bc->z;
}

// Rasterizer and fragment shader in one
void rasterizer(Triangle_t* triangles, int triangle_count, RenderContext_t* rc) {
    Triangle_t* t;
    vec2 v0, v1, v2, p;
    vec3 bc;

    int x_min, x_max, y_min, y_max;
    for (t = triangles; t < &triangles[triangle_count]; ++t) {
        if (!t->valid) {
            continue;
        }

        x_min = fmaxf(t->bb_tl.x, 0);
        x_max = fminf(t->bb_br.x, rc->camera->resolution.x);
        y_min = fmaxf(t->bb_tl.y, 0);
        y_max = fminf(t->bb_br.y, rc->camera->resolution.y);

        for (int y = y_min; y < y_max; y++) {
            for (int x = x_min; x < x_max; x++) {

                p = (vec2){x + 0.5, y + 0.5};
                v0 = (vec2){t->v[0].x, t->v[0].y};
                v1 = (vec2){t->v[1].x, t->v[1].y};
                v2 = (vec2){t->v[2].x, t->v[2].y};

                barycentric(&v0, &v1, &v2, &p, &bc);

                // Check if point is inside triangle
                if (bc.x < 0 || bc.y < 0 || bc.z < 0) {
                    continue;
                }

                // Calculate z value and test zbuffer
                float z = t->v[0].z * bc.x + t->v[1].z * bc.y + t->v[2].z * bc.z;
                int z_valid = render_test_set_depth(rc, x, y, z);
                if (!z_valid) {
                    continue;
                }

                int r = (int)(t->color.x * 255);
                int g = (int)(t->color.y * 255);
                int b = (int)(t->color.z * 255);
                render_set_pixel(rc, x, y, r, g, b);
            }
        }
    }
}

