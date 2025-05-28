#pragma once
#include <Novice.h>
#include <cmath>
#include <assert.h>
#include "Line.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"

class Vector {
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

	// 描画関数
	void ScreenPrintf(const Vector2 &pos, const Vector3 &vector, const char *label);

	// 座標変換
	Vector3 Transform(const Vector3 &vector, const Matrix4x4 &matrix);

	// クロス積
	Vector3 Cross(const Vector3 &v1, const Vector3 &v2);

	// 
	Vector3 Project(const Vector3 &v1, const Vector3 &v2);

	// 
	Vector3 ClosestPoint(const Vector3 &point, const Segment &segment);

private:
	static const int kRowHeight = 20;
	static const int kColumnWidth = 60;
};