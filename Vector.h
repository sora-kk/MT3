#pragma once
#include <Novice.h>
#include <cmath>
#include <assert.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"

class Vector {
public:
	// ‰ÁZ
	Vector3 Add(const Vector3 &v1, const Vector3 &v2);

	// Œ¸Z
	Vector3 Subtract(const Vector3 &v1, const Vector3 &v2);

	// æZ(ƒXƒJƒ‰[”{)
	Vector3 Multiply(float scalar, const Vector3 &v);

	// “àÏ
	float Dot(const Vector3 &v1, const Vector3 &v2);

	// ƒmƒ‹ƒ€(’·‚³)
	float Length(const Vector3 &v);

	// ³‹K‰»
	Vector3 Normalize(const Vector3 &v);

	// •`‰æŠÖ”
	void VectorScreenPrintf(const Vector2 &pos, const Vector3 &vector, const char *label);

	// À•W•ÏŠ·
	Vector3 Transform(const Vector3 &vector, const Matrix4x4 &matrix);

private:
	static const int kRowHeight = 20;
	static const int kColumnWidth = 60;
};