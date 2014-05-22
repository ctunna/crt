#ifndef VECTOR_H__
#define VECTOR_H__

#include <math.h>
#include <stdio.h>

typedef struct {
	float x;
	float y;
	float z;
} vec3;

void dot(const vec3 *X, const vec3 *Y, float *s);
void pvec(const vec3 * X);
void scale(vec3 *X, const float s);
void vec_add(vec3 *X, const vec3 *Y);
void vec_sub(vec3 *X, const vec3 *Y);
void normalize(vec3 *X);
void vec_set(vec3 *X, const float x, const float y, const float z);

float mag(const vec3 *X);

#endif
