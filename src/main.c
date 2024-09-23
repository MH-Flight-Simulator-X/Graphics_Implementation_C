#include <time.h>
#include <stdio.h>
#include <string.h>

#include "display.h"
#include "render.h"
#include "mesh.h"
#include "graphics.h"

// Matrix data is a 1d array of 16 floats
void print_matrix(mat4 matrix) {
    for (int i = 0; i < 16; i++) {
        printf("%f ", matrix.m[i]);
        if ((i + 1) % 4 == 0) {
            printf("\n");
        }
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

    vec3 camera_pos = {0.0f, -3.25f, -6.5f};
    vec3 world_up = {0.0f, 1.0f, 0.0f};
    camera_set_config(rc.camera, camera_pos, world_up, pitch, yaw, fov, zfar, znear);

    // Print camera forward vector
    printf("Camera forward vector: %f %f %f\n", rc.camera->forward.x, rc.camera->forward.y, rc.camera->forward.z);

    // Load mesh
    Model_t model;
    char model_path[] = "../assets/airplane.obj";
    model_init(&model, model_path);

    printf("LOG: Loaded model from path: %s. Vertex count: %d\n", model_path, model.mesh.vertex_count);

    clock_t start, end;

    float t = 0.0f;
    int clear_color = 0x302E30;
    while (1) {
        render_clear(&rc, clear_color);


        // Scale model
        float scale = 0.004f;
        mat4 scale_matrix = mat4_scale(scale, scale, scale);

        // Rotate model
        // model.rotation.x += 0.05f;
        model.rotation.y += 0.1f;

        mat4 identity = mat4_identity();
        mat4 rotation_matrix = mat4_rotate(radians(model.rotation.x), radians(model.rotation.y), radians(model.rotation.z)); 

        // Translate model
        model.position.z = 25.0f;
        mat4 translation_matrix = mat4_translate(model.position.x, model.position.y, model.position.z);

        // Calculate model matrix
        mat4 model_matrix = mat4_mat4_mul_ret(&rotation_matrix, &scale_matrix);
        model.model_matrix = mat4_mat4_mul_ret(&translation_matrix, &model_matrix);

        // Update camera
        // rc.camera->pitch = sin(t) * 1.75f;
        rc.camera->position.y = sin(t) * 1.0f;
        camera_update_vectors(rc.camera);
        camera_update_view(rc.camera);

        // Print view matrix for debugging
        printf("View matrix:\n");
        print_matrix(rc.camera->view_matrix);

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
