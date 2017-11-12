/*
 *	main.c
 *
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vector3.h"
#include "ray.h"


bool
HitSphere(V3 *center, float radius, Ray *r)
{
	V3 oc = SubtractVectorsV3(&r->Origin, center);
	float a = DotProductV3(&r->Direction, &r->Direction);
	float b = 2.0f * DotProductV3(&oc, &r->Direction);
	float c = DotProductV3(&oc, &oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	bool Result = (discriminant > 0) ? true : false;
	return Result;
}

V3
Color(Ray *r)
{
	V3 Result;
	V3 circleCenter = Vector3(0.0f, 0.0f, -1.0f);
	if (HitSphere(&circleCenter, 0.5, r))
	{
		Result = Vector3(1.0f, 0.0f, 0.0f);
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
			V3 color = Color(&r);
			int ir = (int)(255.99 * color.R);
			int ig = (int)(255.99 * color.G);
			int ib = (int)(255.99 * color.B);
			printf("%d %d %d\n", ir, ig, ib);
		}
	}

	return 0;
}
