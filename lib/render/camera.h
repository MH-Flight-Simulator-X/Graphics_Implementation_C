#pragma once
#include <cglm/cglm.h>

typedef struct {
    float zfar, znear;

    vec3 position;
    float pitch, yaw;

    vec3 forward, right, up, world_up;

    float fov;
    vec2 resolution;

    mat4 view_matrix;
    mat4 projection_matrix;
} Camera_t;

void camera_init(Camera_t* camera, vec2 resolution);

void camera_set_config(Camera_t* camera, vec3 pos, vec3 world_up, float pitch, float yaw, float fov, float zfar, float znear);

void camera_update_vectors(Camera_t* camera);

void camera_update_view(Camera_t* camera);
