#include <glm/ext/matrix_transform.hpp>
#include <stdio.h>
#include <glm/ext.hpp>
#include "camera.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Camera::Camera(std::size_t res_x, std::size_t res_y) {
    this->resolution = glm::ivec2(res_x, res_y);
}

int Camera::set_config(glm::vec3 pos, glm::vec3 world_up, float pitch, float yaw, float fov) {
    this->pos = pos;
    this->world_up = world_up;
    this->fov = fov;
    this->yaw = yaw;
    this->pitch = pitch;

    glm::vec3 forward;
    forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward.y = sin(glm::radians(pitch));
    forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->forward = glm::normalize(forward);

    this->projection = glm::perspective(glm::radians(fov), (float)resolution.x / (float)resolution.y, 0.1f, 100.0f);
    Camera::update_vectors();
    Camera::update_view();

    return 0;
}

int Camera::update_vectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->forward = glm::normalize(front);
    this->right = glm::normalize(glm::cross(forward, world_up));
    this->up = glm::normalize(glm::cross(right, forward));

    return 0;
}

int Camera::update_view() {
    this->view = glm::lookAt(this->pos, this->forward + this->pos, this->up);
    return 0;
}

glm::mat4 Camera::get_view() const {
    return this->view;
}

glm::mat4 Camera::get_projection() const {
    return this->projection;
}

glm::vec3 Camera::get_forward() const {
    return this->forward;
}

glm::vec3 Camera::get_right() const {
    return this->right;
}

glm::vec3 Camera::get_world_up() const {
    return this->world_up;
}

void print_matrix(glm::mat4 matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            printf("%f ", matrix[j][i]);
        printf("\n");
    }
    printf("\n");
}

int main() {
    // Model matrix
    glm::vec3 scale = {0.004f, 0.004f, 0.004f};
    glm::mat4 scale_matrix = glm::scale(glm::mat4(1.0f), scale);

    // Rotate model
    glm::vec3 y_axis = {0.0f, 1.0f, 0.0f};
    glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), y_axis);

    // Translate model
    glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f)); 

    // Calculate model matrix
    glm::mat4 model_matrix = translation_matrix * rotation_matrix * scale_matrix;

    glm::vec3 cam_pos(0.0f, 0.0f, 3.0f);
    glm::vec3 world_up(0.0f, 1.0f, 0.0f);
    float pitch = 0.0f;
    float yaw = -90.0f;
    float fov = 90.0f;

    Camera camera_instance(SCREEN_WIDTH, SCREEN_HEIGHT);
    camera_instance.set_config(cam_pos, world_up, pitch, yaw, fov);

    // Rotate camera up 45 degrees
    camera_instance.pitch = 45.0f;
    camera_instance.update_vectors();
    camera_instance.update_view();

    glm::mat4 view = camera_instance.get_view();
    glm::mat4 projection = camera_instance.get_projection();

    print_matrix(model_matrix);
    print_matrix(view);
    print_matrix(projection);

    glm::mat4 mvp = projection * view * model_matrix;
    print_matrix(mvp);
}
