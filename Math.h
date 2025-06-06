#pragma once
#include <Novice.h>
#include <cmath>
#include <assert.h>
#include "Line.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"

class Math {
public:
	// 加算
	Vector3 Add(const Vector3 &v1, const Vector3 &v2);

	// 減算
	Vector3 Subtract(const Vector3 &v1, const Vector3 &v2);

	// 乗算(スカラー倍)
	Vector3 Multiply(float scalar, const Vector3 &v);

	// 内積
	float Dot(const Vector3 &v1, const Vector3 &v2);

	// ノルム(長さ)
	float Length(const Vector3 &v);

	// 正規化
	Vector3 Normalize(const Vector3 &v);

	// 座標変換
	Vector3 Transform(const Vector3 &vector, const Matrix4x4 &matrix);

	// クロス積
	Vector3 Cross(const Vector3 &v1, const Vector3 &v2);

	// 
	Vector3 Project(const Vector3 &v1, const Vector3 &v2);

	// 
	Vector3 ClosestPoint(const Vector3 &point, const Segment &segment);

	// 
	Vector3 Perpendicular(const Vector3 &vector);

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

	// 透視投影行列
	Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

	// 正射影行列
	Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

	// ビューポート変換
	Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

	// 描画関数(ベクトル)
	void ScreenPrintf(const Vector2 &pos, const Vector3 &vector, const char *label);

	// 描画関数(行列)
	void ScreenPrintf(int x, int y, const Matrix4x4 &m);

private:
	static const int kRowHeight = 20;
	static const int kColumnWidth = 60;
};