#include <stdio.h>
#include <stdlib.h>

#define BSIZE 1024

int main()
{
	FILE *fp;
	float x, y, z;
	char fname[] = "spheres.obj";
	static char buf[BSIZE];

	fp = fopen(fname, "r");

	if (fp == NULL) {
		printf("Failed to open %s.\n", fname);
		exit(1);
	}

	while(fgets(buf, BSIZE, fp) != NULL)
	{
		fscanf(buf, "%f %f %f", x, y, z);
		
	}

	return 0;
}
