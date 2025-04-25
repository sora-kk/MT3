#pragma once
#include <Novice.h>
#include <cmath>
#include <assert.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"

class Matrix {
public:
	// 加法
	Matrix4x4 add(const Matrix4x4 &m1, const Matrix4x4 &m2);

	// 減法
	Matrix4x4 Subtract(const Matrix4x4 &m1, const Matrix4x4 &m2);

	// 積
	Matrix4x4 Multiply(const Matrix4x4 &m1, const Matrix4x4 &m2);

	// 逆行列
	Matrix4x4 Inverse(const Matrix4x4 &m);

	// 転置行列
	Matrix4x4 Transpose(const Matrix4x4 &m);

	// 単位行列
	Matrix4x4 MakeIdentity4x4();

	// 平行移動行列
	Matrix4x4 MakeTranslateMatrix(const Vector3 &translate);

	// 拡大縮小行列
	Matrix4x4 MakeScaleMatrix(const Vector3 &scale);

	// X軸回転行列
	Matrix4x4 MakeRotateXMatrix(float radian);

	// Y軸回転行列
	Matrix4x4 MakeRotateYMatrix(float radian);

	// Z軸回転行列
	Matrix4x4 MakeRotateZMatrix(float radian);

	// アフィン変換行列
	Matrix4x4 MakeAffineMatrix(const Vector3 &scale, const Vector3 &rotate, const Vector3 &translate);

	// 描画関数
	void MatrixScreenPrintf(int x, int y, const Matrix4x4 &m);

private:
	static const int kRowHeight = 20;
	static const int kColumnWidth = 60;
};