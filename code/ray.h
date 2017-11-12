/*
 *	ray.h
 *
 */

typedef struct _ray
{
	V3 Origin;
	V3 Direction;
} Ray; 

inline Ray
CreateRay(V3 origin, V3 direction)
{
	Ray Result =
	{
		origin,
		direction,
	};
	return Result;
}

inline V3
PointAtScalar(Ray *r, float t)
{
	V3 Result = MultiplyScalarV3(&r->Direction, t);
	Result = AddVectorsV3(&r->Origin, &Result);
	return Result;
}
