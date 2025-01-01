#include "Vector4.h"

Vector4 vec4_init(float x, float y, float z, float w)
{
	return { x, y, z, w };
}

Vector4 vec4_zero()
{
	return { 0, 0, 0, 0 };
}

bool vec4_equals(Vector4 v1, Vector4 v2)
{
	return (v1.X == v2.X) && (v1.Y == v2.Y) && (v1.Z == v2.Z) && (v1.W == v2.W);
}

float vec4_magnitude(Vector4 v)
{
	return sqrtf(pow(v.X, 2) + pow(v.Y, 2) + pow(v.Z, 2) + pow(v.W, 2));
}

Vector4 vec4_add(Vector4 v1, Vector4 v2)
{
	return { v1.X + v2.X , v1.Y + v2.Y , v1.Z + v2.Z , v1.W + v2.W };
}

Vector4 vec4_subtract(Vector4 v1, Vector4 v2)
{
	return { v1.X - v2.X , v1.Y - v2.Y , v1.Z - v2.Z , v1.W - v2.W };
}

Vector4 vec4_scalarMultiply(float scalar, Vector4 v)
{
	return { scalar * v.X , scalar * v.Y , scalar * v.Z , scalar * v.W };
}

float vec4_dotProduct(Vector4 v1, Vector4 v2)
{
	return (v1.X * v2.X) + (v1.Y * v2.Y) + (v1.Z * v2.Z) + (v1.W * v2.W);
}

Vector4 vec4_normalize(Vector4 v)
{
	Vector4 result{};
	float mag = vec4_magnitude(v);

	if (mag != 0)
	{
		result.X = v.X / mag;
		result.Y = v.Y / mag;
		result.Z = v.Z / mag;
		result.W = v.W / mag;
	}

	return result;
}