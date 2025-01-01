#include "Vector3.h"

Vector3 vec3_init(float x, float y, float z)
{
	return { x, y, z };
}

Vector3 vec3_same(float x) { return { x, x, x }; }

bool vec3_equals(Vector3 v1, Vector3 v2)
{
	return (v1.X == v2.X) && (v1.Y == v2.Y) && (v1.Z == v2.Z);
}

float vec3_magnitude(Vector3 v3)
{
	return sqrtf((float)pow(v3.X, 2) + (float)pow(v3.Y, 2) + (float)pow(v3.Z, 2));
}

Vector3 vec3_add(Vector3 v1, Vector3 v2)
{
	return { v1.X + v2.X , v1.Y + v2.Y , v1.Z + v2.Z };
}

Vector3 vec3_subtract(Vector3 v1, Vector3 v2)
{
	return { v1.X - v2.X , v1.Y - v2.Y , v1.Z - v2.Z };
}

Vector3 vec3_scalarMultiply(float scalar, Vector3 v)
{
	return { scalar * v.X , scalar * v.Y , scalar * v.Z };
}

float vec3_dotProduct(Vector3 v1, Vector3 v2)
{
	return (v1.X * v2.X) + (v1.Y * v2.Y) + (v1.Z * v2.Z);
}

Vector3 vec3_crossProduct(Vector3 v1, Vector3 v2)
{
	return
	{
		{ (v1.Y * v2.Z) - (v1.Z * v2.Y) },
		{ (v1.Z * v2.X) - (v1.X * v2.Z) },
		{ (v1.X * v2.Y) - (v1.Y * v2.X) }
	};
}

Vector3 vec3_normalize(Vector3 v3)
{
	Vector3 result{};
	float mag = vec3_magnitude(v3);

	if (mag != 0)
	{
		result.X = v3.X / mag;
		result.Y = v3.Y / mag;
		result.Z = v3.Z / mag;
	}

	return result;
}