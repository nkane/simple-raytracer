/*
 *	main.c
 *
 */

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector3.h"
#include "ray.h"
#include "geometry.h"

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

	printf("P3\n%d %d\n255\n", nx, ny);

	V3 lowerLeftCorner = Vector3(-2.0f, -1.0f, -1.0f);
	V3 horizontal 	   = Vector3(4.0f, 0.0f, 0.0f);
	V3 vertical	   = Vector3(0.0f, 2.0f, 0.0f);
	V3 origin	   = Vector3(0.0f, 0.0f, 0.0f);

	Sphere *sphereList[2];;
	V3 tempCenter = Vector3(0.0f, 0.0f, -1.0f);
	sphereList[0] = (Sphere *)malloc(sizeof(Sphere));
	*sphereList[0] = CreateSphere(tempCenter, 0.5f);
	tempCenter = Vector3(0.0f, -100.5f, -1.0f);
	sphereList[1] = (Sphere *)malloc(sizeof(Sphere));
	*sphereList[1] = CreateSphere(tempCenter, 100.0f);

	int j;
	int i;
	for(j = ny - 1; j >= 0; j--)
	{
		for (i = 0; i < nx; i++)
		{
			float u = (float)i / (float)nx;
			float v = (float)j / (float)ny;
			V3 v1 = MultiplyScalarV3(&horizontal, u);
			V3 v2 = MultiplyScalarV3(&vertical, v);
			V3 direction = AddVectorsV3(&lowerLeftCorner, &v1);;
			direction = AddVectorsV3(&direction, &v2);
			Ray r = CreateRay(origin, direction);
			V3 position = PointAtScalar(&r, 2.0f);
			V3 color = ColorSphere(&r, sphereList, 2);
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
