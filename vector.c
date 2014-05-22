#include "vector.h"

void dot(const vec3 *X, const vec3 *Y, float *s)
{
	*s = (X->x * Y->x) + (X->y * Y->y) + (X->z * Y->z);
}

void pvec(const vec3 * X)
{
	printf("%f %f %f ", X->x, X->y, X->z);
}

void scale(vec3 *X, const float s)
{
	X->x *= s;
	X->y *= s;
	X->z *= s;
}

void vec_add(vec3 *X, const vec3 *Y)
{
	X->x += Y->x;
	X->y += Y->y;
	X->z += Y->z;
}

void vec_sub(vec3 *X, const vec3 *Y)
{
	X->x -= Y->x;
	X->y -= Y->y;
	X->z -= Y->z;
}

void vec_set(vec3 *X, const float x, const float y, const float z)
{
	X->x = x;
	X->y = y;
	X->z = z;
}
	
void normalize(vec3 *X)
{
	float len = 0.0;
	dot(X, X, &len);
	if(len > 0.001) len = 1 / sqrt(len);
	scale(X, len);
}


float mag(const vec3 *X)
{
	float len;
	dot(X, X, &len);
	return sqrt(len);
}
   
