/*
 *	main.c
 *
 */

typedef struct _camera
{
	V3 Origin;
	V3 LowerLeftCorner;
	V3 Horizontal;
	V3 Vertical;
} Camera;

inline Camera
CreateCamera(V3 origin, V3 lowerLeftCorner, V3 horizontal, V3 vertical)
{
	Camera Result = 
	{
		origin,
		lowerLeftCorner,
		horizontal,
		vertical,
	};
	return Result;
}

inline Ray
GetRayCamera(Camera *c, float u, float v)
{
	Ray Result;
	V3 v1 = MultiplyScalarV3(&c->Horizontal, u);
	V3 v2 = MultiplyScalarV3(&c->Vertical, v);
	V3 v3 = AddVectorsV3(&c->LowerLeftCorner, &v1);
	v3 = AddVectorsV3(&v3, &v2);
	v3 = SubtractVectorsV3(&v3, &c->Origin);
	Result = CreateRay(c->Origin, v3);
	return Result;
}
