#include "Matrix4.h"

/// <summary>
/// Creates Matrix4 full of 0's
/// </summary>
/// <returns></returns>
Matrix4 mat4_init(void)
{
	return
	{
		 0, 0, 0, 0,
		 0, 0, 0, 0,
		 0, 0, 0, 0,
		 0, 0, 0, 0,
	};
}


/// <summary>
/// Create Matrix 4 full of @param val
/// </summary>
/// <param name="val">float</param>
/// <returns></returns>
Matrix4 mat4_init(float val)
{
	return
	{
		 0, 0, 0, 0,
		 0, 0, 0, 0,
		 0, 0, 0, 0,
		 0, 0, 0, val,
	};
}

/// <summary>
/// Returns identity matrix
/// </summary>
/// <returns></returns>
Matrix4 mat4_identity(void)
{
	return
	{
		 1, 0, 0, 0 ,
		 0, 1, 0, 0 ,
		 0, 0, 1, 0 ,
		 0, 0, 0, 1
	};
}


/// <summary>
/// Adds two Matrix4
/// </summary>
/// <param name="m1">Matrix4</param>
/// <param name="m2">Matrix4</param>
/// <returns></returns>
Matrix4 mat4_add(Matrix4 m1, Matrix4 m2)
{
	return
	{
		{vec4_add(m1.row0, m2.row0)},
		{vec4_add(m1.row1, m2.row1)},
		{vec4_add(m1.row2, m2.row2)},
		{vec4_add(m1.row3, m2.row3)},
	};
}


/// <summary>
/// Subtracts two Matrix4
/// </summary>
/// <param name="m1">Matrix4</param>
/// <param name="m2">Matrix4</param>
/// <returns></returns>
Matrix4 mat4_subtract(Matrix4 m1, Matrix4 m2)
{
	return
	{
		{vec4_subtract(m1.row0, m2.row0)},
		{vec4_subtract(m1.row1, m2.row1)},
		{vec4_subtract(m1.row2, m2.row2)},
		{vec4_subtract(m1.row3, m2.row3)},
	};
}


/// <summary>
/// Multiples Matrix4 m * Matrix4 n
/// </summary>
/// <param name="m">Matrix4</param>
/// <param name="n">Matrix4</param>
/// <returns></returns>
Matrix4 mat4_multiply(Matrix4 m1, Matrix4 m2)
{
	return
	{
		{
		vec4_init(
				vec4_dotProduct(m1.row0, vec4_init(m2.row0.X, m2.row1.X, m2.row2.X, m2.row3.X)),
				vec4_dotProduct(m1.row0, vec4_init(m2.row0.Y, m2.row1.Y, m2.row2.Y, m2.row3.Y)),
				vec4_dotProduct(m1.row0, vec4_init(m2.row0.Z, m2.row1.Z, m2.row2.Z, m2.row3.Z)),
				vec4_dotProduct(m1.row0, vec4_init(m2.row0.W, m2.row1.W, m2.row2.W, m2.row3.W))
		)},
		{
		vec4_init(
				vec4_dotProduct(m1.row1, vec4_init(m2.row0.X, m2.row1.X, m2.row2.X, m2.row3.X)),
				vec4_dotProduct(m1.row1, vec4_init(m2.row0.Y, m2.row1.Y, m2.row2.Y, m2.row3.Y)),
				vec4_dotProduct(m1.row1, vec4_init(m2.row0.Z, m2.row1.Z, m2.row2.Z, m2.row3.Z)),
				vec4_dotProduct(m1.row1, vec4_init(m2.row0.W, m2.row1.W, m2.row2.W, m2.row3.W))
		)},
		{
		vec4_init(
				vec4_dotProduct(m1.row2, vec4_init(m2.row0.X, m2.row1.X, m2.row2.X, m2.row3.X)),
				vec4_dotProduct(m1.row2, vec4_init(m2.row0.Y, m2.row1.Y, m2.row2.Y, m2.row3.Y)),
				vec4_dotProduct(m1.row2, vec4_init(m2.row0.Z, m2.row1.Z, m2.row2.Z, m2.row3.Z)),
				vec4_dotProduct(m1.row2, vec4_init(m2.row0.W, m2.row1.W, m2.row2.W, m2.row3.W))
		)},
		{
		vec4_init(
				vec4_dotProduct(m1.row3, vec4_init(m2.row0.X, m2.row1.X, m2.row2.X, m2.row3.X)),
				vec4_dotProduct(m1.row3, vec4_init(m2.row0.Y, m2.row1.Y, m2.row2.Y, m2.row3.Y)),
				vec4_dotProduct(m1.row3, vec4_init(m2.row0.Z, m2.row1.Z, m2.row2.Z, m2.row3.Z)),
				vec4_dotProduct(m1.row3, vec4_init(m2.row0.W, m2.row1.W, m2.row2.W, m2.row3.W))
		)},
	};
}


/// <summary>
/// Multiplies a Matrix4 by a scalar
/// </summary>
/// <param name="scalar">float scalar value</param>
/// <param name="m">Matrix4</param>
/// <returns></returns>
Matrix4 mat4_scalar(float scalar, Matrix4 m)
{
	return
	{
		vec4_scalarMultiply(scalar, m.row0),
		vec4_scalarMultiply(scalar, m.row1),
		vec4_scalarMultiply(scalar, m.row2),
		vec4_scalarMultiply(scalar, m.row3)
	};
}


/// <summary>
/// Transpose Matrix4
/// </summary>
/// <param name="m"></param>
/// <returns></returns>
Matrix4 mat4_transpose(Matrix4 m)
{
	return
	{
		{ m.row0.X, m.row1.X, m.row2.X, m.row3.X },
		{ m.row0.Y, m.row1.Y, m.row2.X, m.row3.Y },
		{ m.row0.Z, m.row1.Z, m.row2.Z, m.row3.Z },
		{ m.row0.W, m.row1.W, m.row2.W, m.row3.W }
	};
}

/// <summary>
/// Find determinant of Matrix4
/// </summary>
/// <param name="m">Matrix4</param>
/// <returns></returns>
float mat4_determinant(Matrix4 m)
{
	//det(m) = (m.row0.x * det(m11)) - (m.row0.y * det(m12)) + (m.row0.Z * det(m13)) - (m.row0.W * det(m14))
	Matrix3 m11 = {
					{m.row1.Y, m.row1.Z, m.row1.W},
					{m.row2.Y, m.row2.Z, m.row2.W},
					{m.row3.Y, m.row3.Z, m.row3.W},
	};

	Matrix3 m12 = {
					{m.row1.X, m.row1.Z, m.row1.W},
					{m.row2.X, m.row2.Z, m.row2.W},
					{m.row3.X, m.row3.Z, m.row3.W},
	};

	Matrix3 m13 = {
					{m.row1.X, m.row1.Y, m.row1.W},
					{m.row2.X, m.row2.Y, m.row2.W},
					{m.row3.X, m.row3.Y, m.row3.W},
	};

	Matrix3 m14 = {
					{m.row1.X, m.row1.Y, m.row1.Z},
					{m.row2.X, m.row2.Y, m.row2.Z},
					{m.row3.X, m.row3.Y, m.row3.Z},
	};

	return (m.row0.X * mat3_determinant(m11))
		- (m.row0.Y * mat3_determinant(m12))
		+ (m.row0.Z * mat3_determinant(m13))
		- (m.row0.W * mat3_determinant(m14));

}

Matrix4 mat4_translate(Vector3 transVec, Matrix4 m)
{
	return
	{
		{ m.row0.X + transVec.X, m.row0.Y + transVec.Y, m.row0.Z + transVec.Z, m.row0.W },
		{ m.row1.X + transVec.X, m.row1.Y + transVec.Y, m.row1.Z + transVec.Z, m.row1.W  },
		{ m.row2.X + transVec.X, m.row2.Y + transVec.Y, m.row2.Z + transVec.Z, m.row2.W  },
		{ m.row3.X , m.row3.Y , m.row3.Z , m.row3.W  },
	};
}