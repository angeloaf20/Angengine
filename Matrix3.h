#pragma once
#include <math.h>
#include "Vector3.h"

#define MATRIX3_H

struct Matrix3
{
	Vector3 row0;
	Vector3 row1;
	Vector3 row2;
};

Matrix3 mat3_init();

/// <summary>
/// Returns identity matrix
/// </summary>
/// <returns></returns>
Matrix3 mat3_identity();


/// <summary>
/// Translate Matrix3 by some translation Vector3
/// </summary>
/// <param name="transVec"></param>
/// <param name="m"></param>
/// <returns></returns>
Matrix3 mat3_translate(Vector3 transVec, Matrix3 m);


Matrix3 mat3_add(Matrix3 m1, Matrix3 m2);


/// <summary>
/// Subtracts two Matrix4
/// </summary>
/// <param name="m1">Matrix4</param>
/// <param name="m2">Matrix4</param>
/// <returns></returns>
Matrix3 mat3_subtract(Matrix3 m1, Matrix3 m2);


/// <summary>
/// Multiples Matrix4 m * Matrix4 n
/// </summary>
/// <param name="m">Matrix4</param>
/// <param name="n">Matrix4</param>
/// <returns></returns>
Matrix3 mat3_muliply(Matrix3 m1, Matrix3 m2);


/// <summary>
/// Multiplies a Matrix3 by a scalar
/// </summary>
/// <param name="scalar">float scalar value</param>
/// <param name="m">Matrix3</param>
/// <returns></returns>
Matrix3 mat3_scalar(float scalar, Matrix3 m);


/// <summary>
/// Transpose Matrix3 
/// </summary>
/// <param name="m">Matrix3</param>
/// <returns></returns>
Matrix3 mat3_transpose(Matrix3 m);

/// <summary>
/// Find determinant of Matrix3
/// </summary>
/// <param name="m">Matrix3</param>
/// <returns></returns>
float mat3_determinant(Matrix3 m);
