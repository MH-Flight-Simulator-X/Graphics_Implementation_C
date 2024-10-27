#include "camera.h"
#include "cglm/vec3.h"

void camera_init(Camera_t* camera, vec2 resolution) {
    // Initialize camera
    glm_vec3_zero(camera->position);
    camera->pitch = 0.0f;
    camera->yaw = 0.0f;

    // Initialize vectors
    glm_vec3_zero(camera->forward);
    glm_vec3_zero(camera->right);
    glm_vec3_zero(camera->up);
    glm_vec3_zero(camera->world_up);
    camera->world_up[1] = 1.0f;


    camera->fov = 90.0f;
    camera->resolution[0] = resolution[0];
    camera->resolution[1] = resolution[1];

    glm_mat4_identity(camera->view_matrix);
    glm_mat4_identity(camera->projection_matrix);
}

void camera_set_config(Camera_t* camera, vec3 pos, vec3 world_up, float pitch, float yaw, float fov, float zfar, float znear) {
    // Set the camera configuration
    glm_vec3_copy(pos, camera->position);
    glm_vec3_copy(world_up, camera->world_up);
    camera->fov = fov;
    camera->yaw = yaw;
    camera->pitch = pitch;
    camera->zfar = zfar;
    camera->znear = znear;

    // Calculate the forward vector
    vec3 forward;
    forward[0] = cos(glm_rad(yaw)) * cos(glm_rad(pitch));
    forward[1] = sin(glm_rad(pitch));
    forward[2] = sin(glm_rad(yaw)) * cos(glm_rad(pitch));
    glm_vec3_normalize_to(forward, camera->forward);

    // Set up the projection matrix
    glm_perspective(glm_rad(fov), camera->resolution[0] / camera->resolution[1], znear, zfar, camera->projection_matrix);
    printf("fov: %f aspect: %f znear: %f zfar: %f\n", fov, camera->resolution[0] / camera->resolution[1], znear, zfar);

    // Update the camera vectors
    camera_update_vectors(camera);
    camera_update_view(camera);
}

void camera_update_vectors(Camera_t* camera) {
    vec3 forward;
    forward[0] = cos(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    forward[1] = sin(glm_rad(camera->pitch));
    forward[2] = sin(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    glm_vec3_normalize_to(forward, camera->forward);

    printf("Camera forward: %f %f %f\n", camera->forward[0], camera->forward[1], camera->forward[2]);

    vec3 right;
    glm_vec3_cross(camera->forward, camera->world_up, right);
    glm_vec3_normalize_to(right, camera->right);

    vec3 up;
    glm_vec3_cross(camera->right, camera->forward, up);
    glm_vec3_normalize_to(up, camera->up);
}

void camera_update_view(Camera_t* camera) {
    vec3 center;
    glm_vec3_add(camera->position, camera->forward, center);
    glm_lookat(camera->position, center, camera->up, camera->view_matrix);
}
