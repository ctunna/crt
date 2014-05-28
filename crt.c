#include "crt.h"

/* Arguments:
  
   Input
   
   pt: point of intersection on sphere
   n: normal on sphere
   
   Output
   
   dir: direction of reflection

   Calculate direction of reflecting ray 
   v = camera - pt
   v /= |v|
   dir = 2(v . n)n - n

*/
void reflect_ray(const vec3 *origin, const vec3 *pt, const vec3 *n, vec3 *dir)
{
	float x = 0.0f;
	vec3 v = *origin;
	
	vec_sub(&v, pt); 
	normalize(&v);
	dot(&v, n, &x);
	x *= 2.0f;
	*dir = *n;
	scale(dir, x);
	vec_sub(dir, &v);
	normalize(dir);
}

void sphere_normal(const sphere_t s, const vec3 *pt, vec3 *norm)
{
	*norm = s.o;
	vec_sub(norm, pt);
	normalize(norm);
}

float specular(const vec3 *refl, const vec3 *pt)
{
	float x;
	vec3 v = camera;

	vec_sub(&v, pt);
	normalize(&v);
	dot(refl, &v, &x);

	if(x < 0) x = 0;
	
	return pow(x, 50.0f);
}

float diffuse(const vec3 *intersection, const vec3* n)
{
	float x;
	vec3 dir;
	
	dir = lights[0].o;
	vec_sub(&dir, intersection);
	normalize(&dir);
	dot(&dir, n, &x);

	if(x > 0) x = 0.0f;

	return -x; /* why is this negative? :D */
}

bool sphere_intersect(const vec3 *d, float *t, const sphere_t s)
{
	float a, b, c, disc, distSqrt, q, t0, t1, temp;

	vec3 o_c = camera;

	vec_sub(&o_c, &s.o); // o_c = camera - origin
	dot(d, d, &a);
	dot(&o_c, d, &b);
	dot(&o_c, &o_c, &c);
	b *= 2;
	c -= s.r * s.r;
	disc = b * b - 4 * a * c;

	if (disc < 0) return false;

	distSqrt = sqrtf(disc);

	if (b < 0) {
		q = (-b - distSqrt) / 2.0;
	} else {
		q = (-b + distSqrt) / 2.0;
	}

	t0 = q / a;
	t1 = c / q;

	if (t0 > t1) {
		temp = t0;
		t0 = t1;
		t1 = temp;
	}

	if (t1 < 0) return false;

	t0 < 0 ? (*t = t1) : (*t = t0);

	return true;
}

int in_shadow(const vec3 *origin)
{
	int i;
	vec3 v = lights[0].o;
	float t;
	
	vec_sub(&v, origin);
	normalize(&v);
	
	for(i = 0; i < sphere_count; i++)
    {
		if(sphere_intersect(&v, &t, spheres[i]))
			return true;
    }

	return false;
}

vec3 send_ray(unsigned int depth, const vec3 *origin, vec3 *ray)
{
	vec3 pt, norm, new_dir, dif_col, col, spec_col, refl;
	int i;
	float t;
	
	pt = *ray;

	for(i = 0; i < sphere_count; i++)
    {
		if(sphere_intersect(ray, &t, spheres[i])) {
			scale(&pt, t);        /* find x, y, z coord from */
			vec_add(&pt, origin); /* r(t) = origin + pt*t */
			col = spheres[i].color; 
			scale(&col, spheres[i].mat.amb);
			break;
		}
    }

	/* if no intersection found! */
	if( i >= sphere_count || in_shadow(&pt) ) return black;

	sphere_normal(spheres[i], &pt, &norm);

	dif_col = spheres[i].color;
	scale(&dif_col, spheres[i].mat.dif * diffuse(&pt, &norm));
	vec_add(&col, &dif_col);

	reflect_ray(origin, &pt, &norm, &new_dir);

	spec_col = white;
	scale(&spec_col, spheres[i].mat.spec * specular(&new_dir, &pt));
	vec_add(&col, &spec_col);

	if( depth < MAX_DEPTH ) {
		refl = send_ray(depth+1, &pt, &new_dir);
		scale(&refl, spheres[i].reflec);
		vec_add(&col, &refl);
	}

	return col;
}

vec3 color_at(const int x, const int y)
{
	vec3 ray  = {(float)x, (float)y, 0.0};

	vec_sub(&ray, &camera);
	normalize(&ray);

	return send_ray(0, &camera, &ray);
}

void ray_trace()
{
	int x, y;

	for (y = 0; y < HEIGHT; ++y)
    {
		for(x = 0; x < WIDTH; ++x)
        {
			img[x][y] = color_at(x,y);
        }
    }
}

void write_ppm()
{
	FILE *fp = fopen("out.ppm", "wb");
	unsigned char color[3];
	int i, j;

	fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
	
	for (j = 0; j < HEIGHT; ++j)
    {
		for (i = 0; i < WIDTH; ++i)
        {
			color[0] = (int)fmin(img[i][j].x, 255.0f);
			color[1] = (int)fmin(img[i][j].y, 255.0f);
			color[2] = (int)fmin(img[i][j].z, 255.0f);
			(void) fwrite(color, 1, 3, fp);
        }
    }
}

void parse()
{
	FILE *fp;
	float x = 0.0f, y = 0.0f, z = 0.0f;
	int r, g, b;
	char fname[] = "scenes/pipe.obj";
	char buf[BSIZE];
	sphere_t temp;
	sphere_count = 0;

	fp = fopen(fname, "r");

	if (fp == NULL) {
		printf("Failed to open %s.\n", fname);
		exit(1);
	}

	while(fgets(buf, BSIZE, fp) != NULL)
    {
		sscanf(buf, "%f %f %f %d %d %d", &x, &y, &z, &r, &g, &b);
		vec_set(&temp.o, x, y, z);
		temp.r = 100.0f;
		temp.reflec = 1.0f;
		temp.refrac = 0.5f;
		temp.mat = gen;
		vec_set(&temp.color, r, g, b);
		spheres[sphere_count] = temp;
		sphere_count++;
    }

	fclose(fp);
}


void init()
{
	light_t l0 = {{100.0f, 200.0f, -100.0f}},
		l1 = {{0.0f, 0.0f, -200.0f}};
		
	lights[0] = l0;
	lights[1] = l1; // unused 
}

int main()
{
	init();
	parse();
	ray_trace();
	write_ppm();

	return 0;
}
