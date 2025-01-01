#pragma once
#include "Vector4.h"
#include "Matrix3.h"

#define MATRIX4_H

struct Matrix4
{
	Vector4 row0;
	Vector4 row1;
	Vector4 row2;
	Vector4 row3;
};

Matrix4 mat4_init(void);

Matrix4 mat4_init(float val);

Matrix4 mat4_identity(void);


/// <summary>
/// Adds two Matrix4
/// </summary>
/// <param name="m1">Matrix4</param>
/// <param name="m2">Matrix4</param>
/// <returns></returns>
Matrix4 mat4_add(Matrix4 m1, Matrix4 m2);


/// <summary>
/// Subtracts two Matrix4
/// </summary>
/// <param name="m1">Matrix4</param>
/// <param name="m2">Matrix4</param>
/// <returns></returns>
Matrix4 mat4_subtract(Matrix4 m1, Matrix4 m2);


/// <summary>
/// Multiples Matrix4 m * Matrix4 n
/// </summary>
/// <param name="m">Matrix4</param>
/// <param name="n">Matrix4</param>
/// <returns></returns>
Matrix4 mat4_multiply(Matrix4 m1, Matrix4 m2);


/// <summary>
/// Multiplies a Matrix4 by a scalar
/// </summary>
/// <param name="scalar">float scalar value</param>
/// <param name="m">Matrix4</param>
/// <returns></returns>
Matrix4 mat4_scalar(float scalar, Matrix4 m);


/// <summary>
/// Transpose Matrix4
/// </summary>
/// <param name="m"></param>
/// <returns></returns>
Matrix4 mat4_transpose(Matrix4 m);

/// <summary>
/// Find determinant of Matrix4
/// </summary>
/// <param name="m">Matrix4</param>
/// <returns></returns>
float mat4_determinant(Matrix4 m);


Matrix4 mat4_translate(Vector3 v, Matrix4 m);