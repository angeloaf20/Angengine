#include "Matrix3.h"

Matrix3 mat3_init()
{
	return
	{
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0, 0 }
	};
}

/// <summary>
/// Returns identity matrix
/// </summary>
/// <returns></returns>
Matrix3 mat3_identity()
{
	return
	{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 },
	};
}


/// <summary>
/// Translate Matrix3 by some translation Vector3
/// </summary>
/// <param name="transVec"></param>
/// <param name="m"></param>
/// <returns></returns>
Matrix3 mat3_translate(Vector3 transVec, Matrix3 m)
{
	return
	{
		{ m.row0.X + transVec.X, m.row0.Y + transVec.Y, m.row0.Z + transVec.Z },
		{ m.row1.X + transVec.X, m.row1.Y + transVec.Y, m.row1.Z + transVec.Z },
		{ m.row2.X + transVec.X, m.row2.Y + transVec.Y, m.row2.Z + transVec.Z }
	};
}


Matrix3 mat3_add(Matrix3 m1, Matrix3 m2)
{
	return
	{
		{vec3_add(m1.row0, m2.row0)},
		{vec3_add(m1.row1, m2.row1)},
		{vec3_add(m1.row2, m2.row2)},
	};
}


/// <summary>
/// Subtracts two Matrix4
/// </summary>
/// <param name="m1">Matrix4</param>
/// <param name="m2">Matrix4</param>
/// <returns></returns>
Matrix3 mat3_subtract(Matrix3 m1, Matrix3 m2)
{
	return
	{
		{vec3_subtract(m1.row0, m2.row0)},
		{vec3_subtract(m1.row1, m2.row1)},
		{vec3_subtract(m1.row2, m2.row2)},
	};
}


/// <summary>
/// Multiples Matrix4 m * Matrix4 n
/// </summary>
/// <param name="m">Matrix4</param>
/// <param name="n">Matrix4</param>
/// <returns></returns>
Matrix3 mat3_muliply(Matrix3 m1, Matrix3 m2)
{
	return
	{
		{
				vec3_dotProduct(m1.row0, { m2.row0.X, m2.row1.X, m2.row2.X }),
				vec3_dotProduct(m1.row0, { m2.row0.Y, m2.row1.Y, m2.row2.Y }),
				vec3_dotProduct(m1.row0, { m2.row0.Z, m2.row1.Z, m2.row2.Z }),
		},
		{
				vec3_dotProduct(m1.row1, { m2.row0.X, m2.row1.X, m2.row2.X }),
				vec3_dotProduct(m1.row1, { m2.row0.Y, m2.row1.Y, m2.row2.Y }),
				vec3_dotProduct(m1.row1, { m2.row0.Z, m2.row1.Z, m2.row2.Z }),
		},
		{
				vec3_dotProduct(m1.row2, { m2.row0.X, m2.row1.X, m2.row2.X }),
				vec3_dotProduct(m1.row2, { m2.row0.Y, m2.row1.Y, m2.row2.Y }),
				vec3_dotProduct(m1.row2, { m2.row0.Z, m2.row1.Z, m2.row2.Z }),
		}
	};
}


/// <summary>
/// Multiplies a Matrix3 by a scalar
/// </summary>
/// <param name="scalar">float scalar value</param>
/// <param name="m">Matrix3</param>
/// <returns></returns>
Matrix3 mat3_scalar(float scalar, Matrix3 m)
{
	return
	{
		vec3_scalarMultiply(scalar, m.row0),
		vec3_scalarMultiply(scalar, m.row1),
		vec3_scalarMultiply(scalar, m.row2)
	};
}


/// <summary>
/// Transpose Matrix3 
/// </summary>
/// <param name="m">Matrix3</param>
/// <returns></returns>
Matrix3 mat3_transpose(Matrix3 m)
{
	return
	{
		{ m.row0.X, m.row1.X, m.row2.X },
		{ m.row0.Y, m.row1.Y, m.row2.X },
		{ m.row0.Z, m.row1.Z, m.row2.Z },
	};
}

/// <summary>
/// Find determinant of Matrix3
/// </summary>
/// <param name="m">Matrix3</param>
/// <returns></returns>
float mat3_determinant(Matrix3 m)
{
	return 
		(m.row0.X * m.row1.Y * m.row2.Z) + 
		(m.row0.Y * m.row1.Z * m.row2.X) + 
		(m.row0.Z * m.row1.X * m.row2.Y) - 
		(m.row0.Z * m.row1.Y * m.row2.X) - 
		(m.row0.Y * m.row1.X * m.row2.Z) - 
		(m.row0.X * m.row1.Z * m.row2.Y);
}