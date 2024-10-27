#include <time.h>
#include <stdio.h>
#include <string.h>

#include <cglm/cglm.h>

#include "display.h"
#include "render.h"
#include "mesh.h"
#include "graphics.h"

// Matrix data is a 1d array of 16 floats
void print_matrix(mat4 matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    // Initialize display
    Display_t display;
    int err = Display_init(&display, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (err) {
        perror("Failed to initialize display\n");
        return 1;
    }
    printf("LOG: Successfully initialized display\n");

    // Initialize render
    RenderContext_t rc;
    err = render_init(&rc);
    if (err) {
        perror("Failed to initialize render\n");
        return 1;
    }
    printf("LOG: Successfully initialized render\n");

    // Configure camera
    float pitch = 0.0f;
    float yaw = -90.0f;

    float zfar = 100.0f;
    float znear = 0.1f;

    float fov = 90.0f;

    vec3 camera_pos = {0.0f, 0, 3.0f};
    vec3 world_up = {0.0f, 1.0f, 0.0f};
    camera_set_config(rc.camera, camera_pos, world_up, pitch, yaw, fov, zfar, znear);


    // Load mesh
    Model_t model;
    char model_path[] = "../assets/airplane.obj";
    model_init(&model, model_path);

    model.position[0] = 0.0f;
    model.position[1] = 0.0f;
    model.position[2] = 0.0f;

    printf("LOG: Loaded model from path: %s. Vertex count: %d\n", model_path, model.mesh.vertex_count);

    clock_t start, end;

    float t = 0.0f;
    int clear_color = 0x302E30;
    while (1) {
        render_clear(&rc, clear_color);


        // Scale model
        vec3 scale = {0.004f, 0.004f, 0.004f};
        mat4 scale_matrix;
        glm_scale_make(scale_matrix, scale);
        
        // Rotate model
        model.rotation[1] += 0.01f;
        vec3 y_axis = {0.0f, 1.0f, 0.0f};
        mat4 rotation_matrix;
        glm_rotate_make(rotation_matrix, model.rotation[1], y_axis);

        // Translate model
        mat4 translation_matrix;
        glm_mat4_identity(translation_matrix);
        glm_translate_make(translation_matrix, model.position); 

        // Calculate model matrix
        mat4 model_matrix;
        glm_mat4_mul(rotation_matrix, scale_matrix, model_matrix);
        glm_mat4_mul(translation_matrix, model_matrix, model.model_matrix);

        // Rotate camera around y axis 
        // rc.camera->pitch = 45;

        // Update camera
        camera_update_vectors(rc.camera);
        camera_update_view(rc.camera);

        // // Print camera vectors
        // printf("Camera position: %f %f %f\n", rc.camera->position[0], rc.camera->position[1], rc.camera->position[2]);
        // printf("Camera forward: %f %f %f\n", rc.camera->forward[0], rc.camera->forward[1], rc.camera->forward[2]);
        // printf("Camera right: %f %f %f\n", rc.camera->right[0], rc.camera->right[1], rc.camera->right[2]);
        // printf("Camera up: %f %f %f\n", rc.camera->up[0], rc.camera->up[1], rc.camera->up[2]);
        //
        // // Print projection matrix
        // printf("Projection matrix:\n");
        // print_matrix(rc.camera->projection_matrix);
        //
        // // Print view matrix
        // printf("View matrix:\n");
        // print_matrix(rc.camera->view_matrix);


        start = clock();
        graphics_render_model(&rc, &model);

        memcpy(display.framebuffer, rc.framebuffer, display.width * display.height * sizeof(int));
        Display_update(&display);
        end = clock();

        double time_taken = ((double)end - start) / CLOCKS_PER_SEC;
        t += time_taken;
        printf("Frame time: %f\n", time_taken);
        if (time_taken > 0)
            printf("FPS: %f\n", 1.0 / time_taken);
    }

    render_destroy(&rc);
    Display_destroy(&display);

    return 0;
}
