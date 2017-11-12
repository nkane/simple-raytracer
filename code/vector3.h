/*
 *	vector3.h
 *
 */

typedef union _v3
{
	struct
	{
		float X, Y, Z;
	};

	struct
	{
		float R, G, B;
	};
} V3;

inline V3
Vector3(float x, float y, float z)
{
	V3 Result =
	{
		x,
		y,
		z,
	};
	return Result;
}

inline float
SquaredLengthV3(V3 v)
{
	float Result = ((v.X * v.X) +
			(v.Y * v.Y) +
			(v.Z * v.Z));
	return Result;
}

inline float
LengthV3(V3 v)
{
	float Result = sqrt(SquaredLengthV3(v));
	return Result;
}

inline float
DotProductV3(V3 *v1, V3 *v2)
{
	float Result = ((v1->X * v2->X) + 
	         	(v1->Y * v2->Y) +
		 	(v1->Z * v2->Z));
	return Result;
}

inline V3
CrossProductV3(V3 *v1, V3 *v2)
{
	V3 Result = Vector3( (v1->Y * v2->Z) - (v1->Z * v2->Y),
	 	            -(v1->X * v2->Z) - (v1->Z * v2->X),
		             (v1->X * v2->Y) - (v1->Y * v2->X));
	return Result;
}

inline V3
AddVectorsV3(V3 *v1, V3 *v2)
{
	V3 Result = Vector3((v1->X + v2->X),
			    (v1->Y + v2->Y),
			    (v1->Z + v2->Z));
	return Result;
}

inline V3
SubtractVectorsV3(V3 *v1, V3 *v2)
{
	V3 Result = Vector3((v1->X - v2->X),
			    (v1->Y - v2->Y),
			    (v1->Z - v2->Z));
	return Result;
}

inline V3
MultiplyVectorsV3(V3 *v1, V3 *v2)
{
	V3 Result = Vector3((v1->X * v2->X),
		            (v1->Y * v2->Y),
		       	    (v1->Z * v2->Z));
	return Result;
}

inline V3
MultiplyScalarV3(V3 *v, float t)
{
	V3 Result = Vector3((v->X * t),
			    (v->Y * t),
			    (v->Z * t));
	return Result;
}

inline V3
DivideVectorsV3(V3 *v1, V3 *v2)
{
	V3 Result = Vector3((v1->X / v2->X),
		       	    (v1->Y / v2->Y),
		       	    (v1->Z / v2->Z));
	return Result;
}

inline V3
DivideScalarV3(V3 *v, float t)
{
	V3 Result = Vector3((v->X / t),
		            (v->Y / t),
		       	    (v->Z / t));
	return Result;
}

inline void
MakeUnitVectorV3(V3 *v)
{
	float unit = 1.0 / LengthV3(*v);
	v->X *= unit;
	v->Y *= unit;
	v->Z *= unit;
}

inline V3
UnitVectorV3(V3 *v)
{
	V3 Result = DivideScalarV3(v, LengthV3(*v));;
	return Result;
}

inline void
PrintV3(V3 v)
{
	printf("%f %f %f", v.X, v.Y, v.Z);
}
