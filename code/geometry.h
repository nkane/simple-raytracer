/*
 *	geometry.h
 *
 */

typedef struct _hitRecord
{
	float T;
	V3 Position;
	V3 Normal;
} HitRecord;

typedef struct _sphere
{
	V3 Center;
	float Radius;
} Sphere;

inline Sphere
CreateSphere(V3 center, float t)
{
	Sphere Result =
	{
		center,
		t,
	};
	return Result;
}

bool
HitSphere(Sphere *s, Ray *r, float tMin, float tMax, HitRecord *hitRecord)
{
	V3 oc = SubtractVectorsV3(&r->Origin, &s->Center);
	float a = DotProductV3(&r->Direction, &r->Direction);
	float b = DotProductV3(&oc, &r->Direction);
	float c = DotProductV3(&oc, &oc) - s->Radius * s->Radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0.0f)
	{
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < tMax && temp > tMin)
		{
			hitRecord->T = temp;
			hitRecord->Position = PointAtScalar(r, hitRecord->T);
			hitRecord->Normal = SubtractVectorsV3(&hitRecord->Position, &s->Center);
			hitRecord->Normal = DivideScalarV3(&hitRecord->Normal, s->Radius);
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < tMax && temp > tMin)
		{
			hitRecord->T = temp;
			hitRecord->Position = PointAtScalar(r, hitRecord->T);
			hitRecord->Normal = SubtractVectorsV3(&hitRecord->Position, &s->Center);
			hitRecord->Normal = DivideScalarV3(&hitRecord->Normal, s->Radius);
			return true;
		}
	}
	return false;
}

bool
HitSphereList(Sphere **sList, Ray *r, float tMin, float tMax, HitRecord *hitRecord, int size)
{
	HitRecord tempRecord;
	bool Result = false;
	double closestSoFar = tMax;
	int i;
	for (i = 0; i < size; i++)
	{
		if (HitSphere(sList[i], r, tMin, closestSoFar, &tempRecord))
		{
			Result = true;
			closestSoFar = tempRecord.T;
			*hitRecord = tempRecord;
		}
	}
	return Result;
}
