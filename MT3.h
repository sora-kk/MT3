#pragma once
#include <Novice.h>
#include <math.h>
#include <assert.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Matrix4x4.h>

class Vector {
public:
	// 3次元ベクトルの加算
	Vector3 Add(const Vector3 &v1, const Vector3 &v2);

	// 3次元ベクトルの減算
	Vector3 Subtract(const Vector3 &v1, const Vector3 &v2);

	// 3次元ベクトルの乗算(スカラー倍)
	Vector3 Multiply(float scalar, const Vector3 &v);

	// 3次元ベクトルの内積
	float Dot(const Vector3 &v1, const Vector3 &v2);

	// 3次元ベクトルのノルム(長さ)
	float Length(const Vector3 &v);

	// 3次元ベクトルの正規化
	Vector3 Normalize(const Vector3 &v);

	// 描画関数
	void VectorScreenPrintf(const Vector2 &pos, const Vector3 &vector, const char *label);

	// 3次元ベクトルの座標変換
	Vector3 Transform(const Vector3 &vector, const Matrix4x4 &matrix);

private:
	static const int kColumnWidth = 60;
};

class Matrix {
public:
	// 4x4行列の加法
	Matrix4x4 add(const Matrix4x4 &m1, const Matrix4x4 &m2);

	// 4x4行列の減法
	Matrix4x4 Subtract(const Matrix4x4 &m1, const Matrix4x4 &m2);

	// 4x4行列の積
	Matrix4x4 Multiply(const Matrix4x4 &m1, const Matrix4x4 &m2);

	// 4x4逆行列
	Matrix4x4 Inverse(const Matrix4x4 &m);

	// 4x4転置行列
	Matrix4x4 Transpose(const Matrix4x4 &m);

	// 4x4単位行列
	Matrix4x4 MakeIdentity4x4();

	// 描画関数
	void MatrixScreenPrintf(int x, int y, const Matrix4x4 &m);

	// 4x4平行移動行列
	Matrix4x4 MakeTranslateMatrix(const Vector3 &translate);

	// 4x4拡大縮小行列
	Matrix4x4 MakeScaleMatrix(const Vector3 &scale);

private:
	static const int kRowHeight = 20;
	static const int kColumnWidth = 60;
};