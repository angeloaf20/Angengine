#pragma once
#include <math.h>

#define VECTOR3_H

struct Vector3
{
	float X;
	float Y;
	float Z;
};

Vector3 vec3_init(float x, float y, float z);

Vector3 vec3_same(float x);

bool vec3_equals(Vector3 v1, Vector3 v2);

float vec3_magnitude(Vector3 v3);

Vector3 vec3_add(Vector3 v1, Vector3 v2);

Vector3 vec3_subtract(Vector3 v1, Vector3 v2);

Vector3 vec3_scalarMultiply(float scalar, Vector3 v);

float vec3_dotProduct(Vector3 v1, Vector3 v2);

Vector3 vec3_crossProduct(Vector3 v1, Vector3 v2);

Vector3 vec3_normalize(Vector3 v3); 
