#ifndef CRT_H__
#define CRT_H__

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

#define MAX_DEPTH 5
#define BSIZE 1024
#define WIDTH 400
#define HEIGHT 400

typedef struct {
	float amb;
	float dif;
	float spec;
} material_t;

typedef struct {
	vec3 o;
	vec3 color;
	float r;
	float reflec;
	float refrac;
	material_t mat;
} sphere_t;

typedef struct {
	/* To add: direction and color */
	vec3 o;
} light_t;

const vec3 camera = {200, 200, -200};
const vec3 red = {255, 0, 0};
const vec3 green = {0, 255, 0};
const vec3 black = {0, 0, 0};
const vec3 white = {255, 255, 255};
const material_t gen = {0.22f, 0.55f, 0.75f};

vec3 img[WIDTH][HEIGHT];
sphere_t spheres[1000];
light_t lights[2];
int sphere_count;

#endif
