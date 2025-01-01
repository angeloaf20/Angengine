#pragma once
#include <math.h>

#define VECTOR4_H

struct Vector4
{
	float X;
	float Y;
	float Z;
	float W;
};

Vector4 vec4_init(float x, float y, float z, float w);

Vector4 vec4_zero();

bool vec4_equals(Vector4 v1, Vector4 v2);

float vec4_magnitude(Vector4 v);

Vector4 vec4_add(Vector4 v1, Vector4 v2);

Vector4 vec4_subtract(Vector4 v1, Vector4 v2);

Vector4 vec4_scalarMultiply(float scalar, Vector4 v);

float vec4_dotProduct(Vector4 v1, Vector4 v2);

Vector4 vec4_normalize(Vector4 v);