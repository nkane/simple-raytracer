/*
 *	main.c
 *
 */

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vector3.h"
#include "ray.h"
#include "camera.h"
#include "geometry.h"

#define drand48()((double)rand() / RAND_MAX)

V3
ColorSphere(Ray *r, Sphere **sList, int size)
{
	HitRecord hitRecord;
	V3 Result;
	if (HitSphereList(sList, r, 0.0f, FLT_MAX, &hitRecord, size))
	{
		Result = Vector3(hitRecord.Normal.X + 1.0f,
				 hitRecord.Normal.Y + 1.0f,
				 hitRecord.Normal.Z + 1.0f);
		Result = MultiplyScalarV3(&Result, 0.5f);
	}
	else
	{
		V3 unitDirection = UnitVectorV3(&r->Direction);
		float t = 0.5f * (unitDirection.Y + 1.0f);
		V3 v1 = Vector3(1.0f, 1.0f, 1.0f);
		V3 v2 = Vector3(0.5f, 0.7f, 1.0f);
		v1 = MultiplyScalarV3(&v1, (1.0f - t));
		v2 = MultiplyScalarV3(&v2, t);
		Result = AddVectorsV3(&v1, &v2);
	}
	return Result;
}

int
main()
{
	int nx = 200;
	int ny = 100;
	int ns = 100;
	printf("P3\n%d %d\n255\n", nx, ny);

	V3 lowerLeftCorner = Vector3(-2.0f, -1.0f, -1.0f);
	V3 horizontal 	   = Vector3(4.0f, 0.0f, 0.0f);
	V3 vertical	   = Vector3(0.0f, 2.0f, 0.0f);
	V3 origin	   = Vector3(0.0f, 0.0f, 0.0f);

	Camera camera = CreateCamera(origin, lowerLeftCorner, horizontal, vertical);
	Sphere *sphereList[2];;
	V3 tempCenter = Vector3(0.0f, 0.0f, -1.0f);
	sphereList[0] = (Sphere *)malloc(sizeof(Sphere));
	*sphereList[0] = CreateSphere(tempCenter, 0.5f);
	tempCenter = Vector3(0.0f, -100.5f, -1.0f);
	sphereList[1] = (Sphere *)malloc(sizeof(Sphere));
	*sphereList[1] = CreateSphere(tempCenter, 100.0f);

	srand(time(NULL));

	int j;
	int i;
	int s;
	V3 color;
	for(j = ny - 1; j >= 0; j--)
	{
		for (i = 0; i < nx; i++)
		{
			color = Vector3(0.0f, 0.0f, 0.0f);
			for (s = 0; s < ns; s++)
			{
				float u = ((float)i + drand48()) / (float)nx;
				float v = ((float)j + drand48()) / (float)ny;
				Ray r = GetRayCamera(&camera, u, v);
				// NOTE(nick): not used?
				V3 p = PointAtScalar(&r, 2.0f);
				V3 blendColor = ColorSphere(&r, sphereList, 2);
				color = AddVectorsV3(&color, &blendColor);
			}
			color = DivideScalarV3(&color, (float)ns);
			int ir = (int)(255.99 * color.R);
			int ig = (int)(255.99 * color.G);
			int ib = (int)(255.99 * color.B);
			printf("%d %d %d\n", ir, ig, ib);
		}
	}
	free(sphereList[0]);
	free(sphereList[1]);
	return 0;
}
