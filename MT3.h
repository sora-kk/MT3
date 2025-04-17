#pragma once
#include <Novice.h>
#include <math.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Matrix3x3.h>
#include <Matrix4x4.h>

class Vector {
public:
	/// <summary>
	/// 3次元ベクトルの加算
	/// </summary>
	/// <param name="v1"> 3次元ベクトルの引数1 </param>
	/// <param name="v2"> 3次元ベクトルの引数2 </param>
	/// <returns> 加算結果 </returns>
	Vector3 Add(const Vector3 &v1, const Vector3 &v2);

	/// <summary>
	/// 3次元ベクトルの減算
	/// </summary>
	/// <param name="v1"> 3次元ベクトルの引数1 </param>
	/// <param name="v2"> 3次元ベクトルの引数2 </param>
	/// <returns> 減算結果 </returns>
	Vector3 Subtract(const Vector3 &v1, const Vector3 &v2);

	/// <summary>
	/// 3次元ベクトルの乗算(スカラー倍)
	/// </summary>
	/// <param name="scalar"> スカラー(倍率) </param>
	/// <param name="v"> 3次元ベクトルの引数 </param>
	/// <returns> 乗算結果 </returns>
	Vector3 Multiply(float scalar, const Vector3 &v);

	/// <summary>
	/// 3次元ベクトルの内積
	/// </summary>
	/// <param name="v1"> 3次元ベクトルの引数1 </param>
	/// <param name="v2"> 3次元ベクトルの引数2 </param>
	/// <returns> 3次元ベクトルの内積 </returns>
	float Dot(const Vector3 &v1, const Vector3 &v2);

	/// <summary>
	/// 3次元ベクトルのノルム(長さ)
	/// </summary>
	/// <param name="v"> 3次元ベクトルの引数 </param>
	/// <returns> 3次元ベクトルのノルム(長さ) </returns>
	float Length(const Vector3 &v);

	/// <summary>
	/// 3次元ベクトルの正規化
	/// </summary>
	/// <param name="v"> 3次元ベクトルの引数 </param>
	/// <returns> 3次元ベクトルの正規化 </returns>
	Vector3 Normalize(const Vector3 &v);

	/// <summary>
	/// 描画関数
	/// </summary>
	/// <param name="pos"> 表示する座標 </param>
	/// <param name="vector"> 表示する3次元ベクトル </param>
	/// <param name="label"> 3次元ベクトルに行った操作 </param>
	void VectorScreenPrintf(const Vector2 &pos, const Vector3 &vector, const char *label);

private:
	static const int kColumnWidth = 60;
};

class Matrix {
public:
	// 行列の加法
	Matrix4x4 add(const Matrix4x4 &m1, const Matrix4x4 &m2);

	// 行列の減法
	Matrix4x4 Subtract(const Matrix4x4 &m1, const Matrix4x4 &m2);

	// 行列の積
	Matrix4x4 Multiply(const Matrix4x4 &m1, const Matrix4x4 &m2);

	// 逆行列
	Matrix4x4 Inverse(const Matrix4x4 &m);

	// 転置行列
	Matrix4x4 Transpose(const Matrix4x4 &m);

	// 単位行列
	Matrix4x4 MakeIdentity4x4();

	// 描画関数
	void MatrixScreenPrintf(int x, int y, const Matrix4x4 &m);

private:
	static const int kRowHeight = 20;
	static const int kColumnWidth = 60;
};