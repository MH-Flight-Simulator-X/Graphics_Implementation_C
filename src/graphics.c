#include "graphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define max(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})

#define min(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})

static inline void print_matrix(mat4 matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void graphics_render_model(RenderContext_t* rc, Model_t* model) {
    mat4 mvp;
    glm_mat4_mul(rc->camera->view_matrix, model->model_matrix, mvp);
    glm_mat4_mul(rc->camera->projection_matrix, mvp, mvp);
    // glm_mat4_transpose(mvp);

    printf("Model matrix:\n");
    print_matrix(model->model_matrix);
    
    printf("View matrix:\n");
    print_matrix(rc->camera->view_matrix);
    
    printf("Projection matrix:\n");
    print_matrix(rc->camera->projection_matrix);
    
    printf("MVP matrix:\n");
    print_matrix(mvp);
    
    vec4* out_vertices = (vec4*)malloc(model->mesh.vertex_count * sizeof(vec4));
    vertex_shader(model->mesh.vertices, model->mesh.vertex_count, &mvp, out_vertices);
    
    vec3* post_processed_vertices = (vec3*)malloc(model->mesh.vertex_count * sizeof(vec3));
    vertex_post_processor(out_vertices, model->mesh.vertex_count, rc->camera->resolution[0], rc->camera->resolution[1], rc->camera->zfar, rc->camera->znear, post_processed_vertices);
    
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
        vec4 vert4 = {vertices[i][0], vertices[i][1], vertices[i][2], 1.0f};
        glm_mat4_mulv(*mvp, vert4, vert4);
        glm_vec4_copy(vert4, out_vertices[i]);
    }
}

void vertex_post_processor(vec4* vertices, int vertex_count, int width, int height, float zfar, float znear, vec3* out) {
    for (int i = 0; i < vertex_count; i++) {
        // Perspective divide
        vec3 v = {vertices[i][0] / vertices[i][3], vertices[i][1] / vertices[i][3], vertices[i][2] / vertices[i][3]};
        out[i][0] = (v[0] + 1.0f) * width / 2.0f;
        out[i][1] = (1.0f - v[1]) * height / 2.0f;
        out[i][2] = v[2] / (zfar - znear);
    }
}

void primitive_assembler(vec3* vertices, int vertex_count, int* indices, int index_count, vec3* camera_pos, Triangle_t* out) {
    vec3 colors[12] = {
        {1.0f,   0.702f, 0.729f},   // Light Pink
        {1.0f,   0.875f, 0.729f},   // Peach
        {1.0f,   1.0f,   0.729f},   // Light Yellow
        {0.729f, 1.0f,   0.788f},   // Mint Green
        {0.729f, 0.882f, 1.0f},     // Light Sky Blue
        {0.882f, 0.729f, 1.0f},     // Lavender
        {1.0f,   0.765f, 0.890f},   // Pastel Rose
        {0.765f, 1.0f,   0.867f},   // Pale Aqua
        {1.0f,   0.843f, 0.765f},   // Pastel Orange
        {1.0f,   0.961f, 0.729f},   // Pale Lemon
        {0.843f, 1.0f,   0.729f},   // Pale Lime Green
        {0.729f, 0.765f, 1.0f}      // Pastel Purple
    };

    for (int i = 0; i < index_count / 3; i++) {
        int ibuffer_offset = 3 * i;
        Triangle_t* t = &out[i];

        // Do backface culling
        vec3 v01, v02, n;
        glm_vec3_sub(vertices[indices[ibuffer_offset + 1]], vertices[indices[ibuffer_offset]], v01);
        glm_vec3_sub(vertices[indices[ibuffer_offset + 2]], vertices[indices[ibuffer_offset]], v02);
        glm_vec3_cross(v01, v02, n);

        vec3 a, b, c;
        glm_vec3_copy(vertices[indices[ibuffer_offset]], a);
        glm_vec3_copy(vertices[indices[ibuffer_offset + 1]], b);
        glm_vec3_copy(vertices[indices[ibuffer_offset + 2]], c);

        vec3 v0 = {
            (a[0] + b[0] + c[0]) / 3.0f, 
            (a[1] + b[1] + c[1]) / 3.0f, 
            (a[2] + b[2] + c[2]) / 3.0f
        };
        vec3 cam_to_pos; 
        glm_vec3_sub(*camera_pos, v0, cam_to_pos);
        float dp = glm_vec3_dot(cam_to_pos, n);

        // Backface culling happens here
        if (dp < 0) {
            t->valid = 0;
            continue;
        }
        t->valid = 1;

        // Create triangle
        glm_vec3_copy(vertices[indices[ibuffer_offset]], t->v[0]);
        glm_vec3_copy(vertices[indices[ibuffer_offset + 1]], t->v[1]);
        glm_vec3_copy(vertices[indices[ibuffer_offset + 2]], t->v[2]);
        glm_vec3_copy(colors[i % 12], t->color);
        glm_vec3_copy(n, t->normal);

        // Calculate bounding box
        t->bb_tl[0] = min(min(t->v[0][0], t->v[1][0]), t->v[2][0]);
        t->bb_tl[1] = min(min(t->v[0][1], t->v[1][1]), t->v[2][1]);
        t->bb_br[0] = max(max(t->v[0][0], t->v[1][0]), t->v[2][0]);
        t->bb_br[1] = max(max(t->v[0][1], t->v[1][1]), t->v[2][1]);
    }
}

// TODO: Add binning
// void binner(Triangle_t* triangles, int triangle_count, int width, int height, int* out);

static inline void barycentric(vec2* v0, vec2* v1, vec2* v2, vec2* p, vec3* bc) {
    vec2 v10 = {v1[0] - v0[0], v1[1] - v0[1]};
    vec2 v20 = {v2[0] - v0[0], v2[1] - v0[1]};
    vec2 vp0 = {p[0]  - v0[0], p[1]  - v0[1]};

    double d00 = v10[0] * v10[0] + v10[1] * v10[1];
    double d01 = v10[0] * v20[0] + v10[1] * v20[1];
    double d11 = v20[0] * v20[0] + v20[1] * v20[1];
    double d20 = vp0[0] * v10[0] + vp0[1] * v10[1];
    double d21 = vp0[0] * v20[0] + vp0[1] * v20[1];

    float det = (d00 * d11 - d01 * d01);
    // if (det <= 0.0f) {
    //     (*bc)[0] = -1.0f;
    //     (*bc)[1] = -1.0f;
    //     (*bc)[2] = -1.0f;
    //     return;
    // }
    (*bc)[0] = (float)(d11 * d20 - d01 * d21) / det;
    (*bc)[1] = (float)(d00 * d21 - d01 * d20) / det;
    (*bc)[2] = 1.0f - (*bc)[0] - (*bc)[1];
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

        // Constrain bounding box to screen
        x_min = fmaxf(0.0f, (int)t->bb_tl[0]);
        x_min = fminf(rc->camera->resolution[0], x_min);

        x_max = fminf(rc->camera->resolution[0], (int)t->bb_br[0]);
        x_max = fmaxf(0.0f, x_max);

        y_min = fmaxf(0.0f, (int)t->bb_tl[1]);
        y_min = fminf(rc->camera->resolution[1], y_min);

        y_max = fminf(rc->camera->resolution[1], (int)t->bb_br[1]);
        y_max = fmaxf(0.0f, y_max);

        for (int y = y_min; y < y_max; y++) {
            for (int x = x_min; x < x_max; x++) {

                // p[0] = x + 0.5; p[1] = y + 0.5;
                // v0[0] = (int)t->v[0][0]; v0[1] = (int)t->v[0][1];
                // v1[0] = (int)t->v[1][0]; v1[1] = (int)t->v[1][1];
                // v2[0] = (int)t->v[2][0]; v2[1] = (int)t->v[2][1];
                //
                // barycentric(&v0, &v1, &v2, &p, &bc);
                //
                // // Check if point is inside triangle
                // if (bc[0] < 0 || bc[1] < 0 || bc[2] < 0) {
                //     continue;
                // }
                //
                // printf("bc: %f %f %f\n", bc[0], bc[1], bc[2]);
                //
                // // Calculate z value and test zbuffer
                // float z = t->v[0][2] * bc[0] + t->v[1][2] * bc[1] + t->v[2][2] * bc[2];
                // int z_valid = render_test_set_depth(rc, x, y, z);
                // if (!z_valid) {
                //     continue;
                // }

                int r = (int)(t->color[0] * 255);
                int g = (int)(t->color[1] * 255);
                int b = (int)(t->color[2] * 255);
                render_set_pixel(rc, x, y, r, g, b);
            }
        }
    }
}

