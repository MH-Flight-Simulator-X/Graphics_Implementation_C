#include <stdio.h>
#include "graphics_math.h"
#include "math.h"

float radians(float degrees) {
    return degrees * (M_PI / 180.0f);
}

/*=============== VEC2 ===============*/
vec2 vec2_add(const vec2* v, const vec2* w) {
    return (vec2){v->x + w->x, v->y + w->y};
}

vec2 vec2_sub(const vec2* v, const vec2* w) {
    return (vec2){v->x - w->x, v->y - w->y};
}

vec2 vec2_mul(const vec2* v, double k) {
    return (vec2){v->x * k, v->y * k};
}

vec2 vec2_div(const vec2* v, double k) {
    return (vec2){v->x / k, v->y / k};
}

double vec2_dot(const vec2* v, const vec2* w) {
    return v->x * w->x + v->y * w->y;
}

void swap_vec2(vec2* v, vec2* w) {
    vec2 tmp = *v;
    *v = *w;
    *w = tmp;
}

/*=============== VEC3 ===============*/
vec3 vec3_add(const vec3* v, const vec3* w) {
    return (vec3){v->x + w->x, v->y + w->y, v->z + w->z};
}

vec3 vec3_sub(const vec3* v, const vec3* w) {
    return (vec3){v->x - w->x, v->y - w->y, v->z - w->z};
}

vec3 vec3_mul(const vec3* v, double k) {
    return (vec3){v->x * k, v->y * k, v->z * k};
}

vec3 vec3_div(const vec3* v, double k) {
    return (vec3){v->x / k, v->y / k, v->z / k};
}

double vec3_dot(const vec3* v, const vec3* w) {
    return v->x * w->x + v->y * w->y + v->z * w->z;
}

vec3 vec3_cross(const vec3* v, const vec3* w) {
    vec3 result;
    result.x = v->y * w->z - v->z * w->y;
    result.y = v->z * w->x - v->x * w->z;
    result.z = v->x * w->y - v->y * w->x;
    return result;
}

double vec3_length(const vec3* v) {
    return sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
}

vec3 vec3_normalize(const vec3* v) {
    return vec3_div(v, vec3_length(v));
}

void swap_vec3(vec3* v, vec3* w) {
    vec3 tmp = *v;
    *v = *w;
    *w = tmp;
}

vec3 vec3_clamp(const vec3* v, float min, float max) {
    vec3 res;
    if (v->x < min) res.x = min;
    else if (v->x > max) res.x = max;
    else res.x = v->x;

    if (v->y < min) res.y = min;
    else if (v->y > max) res.y = max;
    else res.y = v->y;

    if (v->z < min) res.z = min;
    else if (v->z > max) res.z = max;
    else res.z = v->z;

    return res;
}

/*=============== VEC4 ===============*/
vec4 vec4_add(const vec4* v, const vec4* w) {
    return (vec4){v->x + w->x, v->y + w->y, v->z + w->z, v->w + w->w};
}

vec4 vec4_sub(const vec4* v, const vec4* w) {
    return (vec4){v->x - w->x, v->y - w->y, v->z - w->z, v->w - w->w};
}

vec4 vec4_mul(const vec4* v, double k) {
    return (vec4){v->x * k, v->y * k, v->z * k, v->w * k};
}

vec4 vec4_div(const vec4* v, double k) {
    return (vec4){v->x / k, v->y / k, v->z / k, v->w / k};
}

double vec4_dot(const vec4* v, const vec4* w) {
    return v->x * w->x + v->y * w->y + v->z * w->z + v->w * w->w;
}

void swap_vec4(vec4* v, vec4* w) {
    vec4 tmp = *v;
    *v = *w;
    *w = tmp;
}

/*=============== MAT4 ===============*/
mat4 mat4_identity() {
    mat4 i = {0};
    i.m[0] = i.m[5] = i.m[10] = i.m[15] = 1.0;
    return i;
}

void mat4_mat4_add(const mat4*  a, const mat4*  b, mat4*  c) {
    c->m[0]  = a->m[0]  + b->m[0];  c->m[1]  = a->m[1]  + b->m[1];  c->m[2]  = a->m[2]  + b->m[2];  c->m[3]  = a->m[3]  + b->m[3]; 
    c->m[4]  = a->m[4]  + b->m[4];  c->m[5]  = a->m[5]  + b->m[5];  c->m[6]  = a->m[6]  + b->m[6];  c->m[7]  = a->m[7]  + b->m[7]; 
    c->m[8]  = a->m[8]  + b->m[8];  c->m[9]  = a->m[9]  + b->m[9];  c->m[10] = a->m[10] + b->m[10]; c->m[11] = a->m[11] + b->m[11];
    c->m[12] = a->m[12] + b->m[12]; c->m[13] = a->m[13] + b->m[13]; c->m[14] = a->m[14] + b->m[14]; c->m[15] = a->m[15] + b->m[15];
}

void mat4_mat4_sub(const mat4*  a, const mat4*  b, mat4*  c) {
    c->m[0]  = a->m[0]  - b->m[0];  c->m[1]  = a->m[1]  - b->m[1];  c->m[2]  = a->m[2]  - b->m[2];  c->m[3]  = a->m[3]  - b->m[3]; 
    c->m[4]  = a->m[4]  - b->m[4];  c->m[5]  = a->m[5]  - b->m[5];  c->m[6]  = a->m[6]  - b->m[6];  c->m[7]  = a->m[7]  - b->m[7]; 
    c->m[8]  = a->m[8]  - b->m[8];  c->m[9]  = a->m[9]  - b->m[9];  c->m[10] = a->m[10] - b->m[10]; c->m[11] = a->m[11] - b->m[11];
    c->m[12] = a->m[12] - b->m[12]; c->m[13] = a->m[13] - b->m[13]; c->m[14] = a->m[14] - b->m[14]; c->m[15] = a->m[15] - b->m[15];
}

void mat4_mat4_mul(const mat4*  a, const mat4*  b, mat4*  c) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            c->m[i * 4 + j] = 0;
            for (int k = 0; k < 4; ++k) {
                c->m[i * 4 + j] += a->m[i * 4 + k] * b->m[k * 4 + j];
            }
        }
    }
}

mat4 mat4_mat4_add_ret(const mat4*  a, const mat4*  b) {
    mat4 r = {0};
    r.m[0]  = a->m[0]  + b->m[0];  r.m[1]  = a->m[1]  + b->m[1];  r.m[2]  = a->m[2]  + b->m[2];  r.m[3]  = a->m[3]  + b->m[3]; 
    r.m[4]  = a->m[4]  + b->m[4];  r.m[5]  = a->m[5]  + b->m[5];  r.m[6]  = a->m[6]  + b->m[6];  r.m[7]  = a->m[7]  + b->m[7]; 
    r.m[8]  = a->m[8]  + b->m[8];  r.m[9]  = a->m[9]  + b->m[9];  r.m[10] = a->m[10] + b->m[10]; r.m[11] = a->m[11] + b->m[11];
    r.m[12] = a->m[12] + b->m[12]; r.m[13] = a->m[13] + b->m[13]; r.m[14] = a->m[14] + b->m[14]; r.m[15] = a->m[15] + b->m[15];
    return r;
}

mat4 mat4_mat4_sub_ret(const mat4*  a, const mat4*  b) {
    mat4 r = {0};
    r.m[0]  = a->m[0]  - b->m[0];  r.m[1]  = a->m[1]  - b->m[1];  r.m[2]  = a->m[2]  - b->m[2];  r.m[3]  = a->m[3]  - b->m[3]; 
    r.m[4]  = a->m[4]  - b->m[4];  r.m[5]  = a->m[5]  - b->m[5];  r.m[6]  = a->m[6]  - b->m[6];  r.m[7]  = a->m[7]  - b->m[7]; 
    r.m[8]  = a->m[8]  - b->m[8];  r.m[9]  = a->m[9]  - b->m[9];  r.m[10] = a->m[10] - b->m[10]; r.m[11] = a->m[11] - b->m[11];
    r.m[12] = a->m[12] - b->m[12]; r.m[13] = a->m[13] - b->m[13]; r.m[14] = a->m[14] - b->m[14]; r.m[15] = a->m[15] - b->m[15];
    return r;
}

mat4 mat4_mat4_mul_ret(const mat4*  a, const mat4*  b) {
    mat4 r = {0};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            r.m[i * 4 + j] = 0;
            for (int k = 0; k < 4; ++k) {
                r.m[i * 4 + j] += a->m[i * 4 + k] * b->m[k * 4 + j];
            }
        }
    }
    return r;
}

vec4 mat4_vec4_mul(const mat4*  a, const vec4*  v) {
    vec4 result;
    result.x = a->m[0] * v->x  + a->m[1]  * v->y + a->m[2]  * v->z + a->m[3]  * v->w;
    result.y = a->m[4] * v->x  + a->m[5]  * v->y + a->m[6]  * v->z + a->m[7]  * v->w;
    result.z = a->m[8] * v->x  + a->m[9]  * v->y + a->m[10] * v->z + a->m[11] * v->w;
    result.w = a->m[12] * v->x + a->m[13] * v->y + a->m[14] * v->z + a->m[15] * v->w;
    return result;
}

/*=============== GRAPHICS MATH ===============*/
mat4 mat4_scale(float sx, float sy, float sz) {
    mat4 res = mat4_identity();
    res.m[0] = sx;   
    res.m[5] = sy;   
    res.m[10] = sz;  
    res.m[15] = 1.0f; 
    return res;
}

mat4 mat4_translate(double tx, double ty, double tz) {
    mat4 res = mat4_identity();
    res.m[3] = tx;
    res.m[7] = ty;
    res.m[11] = tz;
    return res;
}

mat4 mat4_rotate_x(float angle) {
    mat4 result = mat4_identity();
    double c = cos(angle);
    double s = sin(angle);
    result.m[5] = c;
    result.m[6] = s;
    result.m[9] = -s;
    result.m[10] = c;
    return result;
}

mat4 mat4_rotate_y(float angle) {
    mat4 result = mat4_identity();
    float c = cos(angle);
    float s = sin(angle);
    result.m[0] = c;
    result.m[2] = -s;
    result.m[8] = s;
    result.m[10] = c;
    return result;
}

mat4 mat4_rotate_z(float angle) {
    mat4 result = mat4_identity();
    float c = cos(angle);
    float s = sin(angle);
    result.m[0] = c;
    result.m[1] = -s;
    result.m[4] = s;
    result.m[5] = c;
    return result;
}

mat4 mat4_rotate(double pitch, double yaw, double roll) {
    mat4 rx = mat4_rotate_x(pitch);
    mat4 ry = mat4_rotate_y(yaw);
    mat4 rz = mat4_rotate_z(roll);

    // Combine rotations: R = Rz * Ry * Rx
    mat4 result;
    mat4_mat4_mul(&rz, &ry, &result);
    mat4 result_2;
    mat4_mat4_mul(&result, &rx, &result_2);
    return result_2;
}

mat4 mat4_perspective(float fov, float aspect, float znear, float zfar) {
    mat4 res = {0};
    double tan_half_fov = tan(fov / 2.0f);

    res.m[0] = 1.0f / (aspect * tan_half_fov);
    res.m[5] = 1.0f / tan_half_fov;
    res.m[10] = zfar / (znear - zfar);
    res.m[11] = -1.0f;
    res.m[14] = -(zfar * znear) / (zfar - znear);
    return res;
}

vec3 perspective_divide(const vec4*  v) {
    return (vec3){v->x / v->w, v->y / v->w, v->z / v->w};
}

vec3 viewport_transform(const vec3*  ndc, int width, int height, double z_near, double z_far) {
    return (vec3){(ndc->x + 1.0) * width * 0.5, (ndc->y + 1) * height * 0.5, ndc->z / (z_far - z_near)};
}

vec3 transform_vertex(const vec4*  v, const mat4*  model, const mat4*  view, const mat4*  projection, int s_width, int s_height, double z_near, double z_far) {
    vec4 world_pos = mat4_vec4_mul(model, v);
    vec4 view_pos = mat4_vec4_mul(view, &world_pos);
    vec4 clip_pos = mat4_vec4_mul(projection, &view_pos);
    vec3 ndc = perspective_divide(&clip_pos);
    return viewport_transform(&ndc, s_width, s_height, z_near, z_far);
}

mat4 transformation_matrix(const mat4*  model, const mat4*  view, const mat4*  projection) {
    mat4 mv_matrix = mat4_mat4_mul_ret(view, model);             // Combine model and view matrices
    mat4 mvp_matrix = mat4_mat4_mul_ret(projection, &mv_matrix); // Combine with projection matrix
    return mvp_matrix;
}

mat4 mat4_lookAt(vec3 eye, vec3 center, vec3 up) {
    // printf("Eye: %f %f %f\n", eye.x, eye.y, eye.z);
    // printf("Center: %f %f %f\n", center.x, center.y, center.z);
    // printf("Up: %f %f %f\n", up.x, up.y, up.z);

    vec3 center_eye = vec3_sub(&center, &eye);
    vec3 f = vec3_normalize(&center_eye);
    vec3 right = vec3_cross(&f, &up);
    vec3 s = vec3_normalize(&right);
    vec3 u = vec3_cross(&s, &f);

    mat4 result = mat4_identity();
    result.m[0 * 4 + 0] = s.x;
    result.m[1 * 4 + 0] = s.y;
    result.m[2 * 4 + 0] = s.z;
    result.m[0 * 4 + 1] = u.x;
    result.m[1 * 4 + 1] = u.y;
    result.m[2 * 4 + 1] = u.z;
    result.m[0 * 4 + 2] = -f.x;
    result.m[1 * 4 + 2] = -f.y;
    result.m[2 * 4 + 2] = -f.z;
    result.m[3 * 4 + 0] = -vec3_dot(&s, &eye);
    result.m[3 * 4 + 1] = -vec3_dot(&u, &eye);
    result.m[3 * 4 + 2] = -vec3_dot(&f, &eye);

    return result;
}
