#include "camera.h"

void camera_init(Camera_t* camera, vec2 resolution) {
    camera->position = (vec3){0.0f, 0.0f, 0.0f};
    camera->pitch = 0.0f;
    camera->yaw = 0.0f;

    camera->forward = (vec3){0.0f, 0.0f, 0.0f};
    camera->right = (vec3){0.0f, 0.0f, 0.0f};
    camera->up = (vec3){0.0f, 0.0f, 0.0f};
    camera->world_up = (vec3){0.0f, 1.0f, 0.0f};

    camera->fov = 90.0f;
    camera->resolution = resolution;

    camera->view_matrix = mat4_identity();
    camera->projection_matrix = mat4_identity();
}

void camera_set_config(Camera_t* camera, vec3 pos, vec3 world_up, float pitch, float yaw, float fov, float zfar, float znear) {
    camera->position = pos;
    camera->world_up = world_up;
    camera->fov = fov;
    camera->yaw = yaw;
    camera->pitch = pitch;

    vec3 forward;
    forward.x = cos(radians(yaw)) * cos(radians(pitch));
    forward.y = sin(radians(pitch));
    forward.z = sin(radians(yaw)) * cos(radians(pitch));
    camera->forward = vec3_normalize(&forward);

    camera->projection_matrix = mat4_perspective(radians(fov), camera->resolution.x / camera->resolution.y, 0.1f, 100.0f);
    camera_update_vectors(camera);
    camera_update_view(camera);
}

void camera_update_vectors(Camera_t* camera) {
    vec3 forward;
    forward.x = cos(radians(camera->yaw)) * cos(radians(camera->pitch));
    forward.y = sin(radians(camera->pitch));
    forward.z = sin(radians(camera->yaw)) * cos(radians(camera->pitch));
    camera->forward = vec3_normalize(&forward);

    vec3 right = vec3_cross(&camera->forward, &camera->world_up);
    camera->right = vec3_normalize(&right);

    vec3 up = vec3_cross(&camera->right, &camera->forward);
    camera->up = vec3_normalize(&up);
}

void camera_update_view(Camera_t* camera) {
    vec3 center = vec3_add(&camera->position, &camera->forward);
    camera->view_matrix = mat4_lookAt(camera->position, center, camera->up);
}
