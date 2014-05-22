#ifndef CRT_H__
#define CRT_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"

#define MAX_DEPTH 5
#define BSIZE 1024
#define WIDTH 400
#define HEIGHT 400
#define true 1
#define false 0

typedef struct {
	vec3 o;
	vec3 color;
	float r;
	float reflec;
	float refrac;
} sphere_t;

typedef struct {
	vec3 o;
} light_t;

const vec3 camera = {200, 200, -200};
vec3 img[WIDTH][HEIGHT];
sphere_t spheres[1000];
light_t lights[2];
int sphere_count;

vec3 red = {255, 0, 0};
vec3 green = {0, 255, 0};
vec3 black = {0, 0, 0};

#endif
