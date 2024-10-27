#include "mesh.h"
#include <assimp/postprocess.h>
#include <stdlib.h>
#include <stdio.h>

void model_init(Model_t* model, const char* path) {
    const struct aiScene* scene = aiImportFile(path, aiProcess_Triangulate | aiProcess_OptimizeMeshes);
    if (!scene) {
        printf("Error loading model: %s\n", path);
        return;
    }

    // Merge all meshes into one large mesh, and save that mesh to the model
    model->mesh.vertex_count = 0;
    model->mesh.index_count = 0;
    for (int i = 0; i < scene->mNumMeshes; i++) {
        model->mesh.vertex_count += scene->mMeshes[i]->mNumVertices;
        model->mesh.index_count += scene->mMeshes[i]->mNumFaces * 3;
    }

    model->mesh.vertices = (vec3*)malloc(model->mesh.vertex_count * sizeof(vec3));
    model->mesh.indices = (int*)malloc(model->mesh.index_count * sizeof(int));

    int vertex_offset = 0;
    int index_offset = 0;
    for (int i = 0; i < scene->mNumMeshes; i++) {
        for (int j = 0; j < scene->mMeshes[i]->mNumVertices; j++) {
            model->mesh.vertices[vertex_offset + j][0] = scene->mMeshes[i]->mVertices[j].x;
            model->mesh.vertices[vertex_offset + j][1] = scene->mMeshes[i]->mVertices[j].y;
            model->mesh.vertices[vertex_offset + j][2] = scene->mMeshes[i]->mVertices[j].z;
        }

        for (int j = 0; j < scene->mMeshes[i]->mNumFaces; j++) {
            model->mesh.indices[index_offset + j * 3] = scene->mMeshes[i]->mFaces[j].mIndices[0] + vertex_offset;
            model->mesh.indices[index_offset + j * 3 + 1] = scene->mMeshes[i]->mFaces[j].mIndices[1] + vertex_offset;
            model->mesh.indices[index_offset + j * 3 + 2] = scene->mMeshes[i]->mFaces[j].mIndices[2] + vertex_offset;
        }

        vertex_offset += scene->mMeshes[i]->mNumVertices;
        index_offset += scene->mMeshes[i]->mNumFaces * 3;
    }

    aiReleaseImport(scene);
}

void model_destroy(Model_t* model) {
    free(model->mesh.vertices);
    free(model->mesh.indices);
}
