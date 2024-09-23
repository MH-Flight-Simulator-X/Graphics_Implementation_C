#pragma once
#include <stdbool.h>

// For loading model data
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/vector3.h>

#include "../graphics_math/graphics_math.h"

typedef struct {
    vec3 v[3];
    vec3 normal;
    vec3 color;
    vec2 bb_tl;
    vec2 bb_br;
    bool valid;
} Triangle_t;

typedef struct {
    int* indices;
    vec3* vertices;
    int index_count;
    int vertex_count;
} Mesh_t;

typedef struct {
    Mesh_t mesh;
    vec3 position;
    vec3 rotation;
    vec3 scale;
    mat4 model_matrix;
} Model_t;

void model_init(Model_t* model, const char* path);

void model_destroy(Model_t* model);
