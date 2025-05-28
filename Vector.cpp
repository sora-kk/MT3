#include "Vector.h"

using namespace std;

// 加算
Vector3 Vector::Add(const Vector3 &v1, const Vector3 &v2) {
	Vector3 result = { v1.x + v2.x,v1.y + v2.y,v1.z + v2.z };
	return result;
}

// 減算
Vector3 Vector::Subtract(const Vector3 &v1, const Vector3 &v2) {
	Vector3 result = { v1.x - v2.x,v1.y - v2.y,v1.z - v2.z };
	return result;
}

// 乗算(スカラー倍)
Vector3 Vector::Multiply(float scalar, const Vector3 &v) {
	Vector3 result = { scalar * v.x,scalar * v.y,scalar * v.z };
	return result;
}

// 内積
float Vector::Dot(const Vector3 &v1, const Vector3 &v2) {
	float result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return result;
}

// ノルム(長さ)
float Vector::Length(const Vector3 &v) {
	float result = sqrtf({ v.x * v.x + v.y * v.y + v.z * v.z });
	return result;
}

// 正規化
Vector3 Vector::Normalize(const Vector3 &v) {
	Vector3 result = { v.x / Length(v),v.y / Length(v),v.z / Length(v) };
	return result;
}

// 描画関数
void Vector::ScreenPrintf(const Vector2 &pos, const Vector3 &vector, const char *label) {
	Novice::ScreenPrintf(static_cast<int>(pos.x), static_cast<int>(pos.y), "%.02f", vector.x);
	Novice::ScreenPrintf(static_cast<int>(pos.x + kColumnWidth), static_cast<int>(pos.y), "%.02f", vector.y);
	Novice::ScreenPrintf(static_cast<int>(pos.x + kColumnWidth * 2), static_cast<int>(pos.y), "%.02f", vector.z);
	Novice::ScreenPrintf(static_cast<int>(pos.x + kColumnWidth * 3), static_cast<int>(pos.y), "%s", label);
}

// 座標変換
Vector3 Vector::Transform(const Vector3 &vector, const Matrix4x4 &matrix) {
	Vector3 result{};

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

// クロス積
Vector3 Vector::Cross(const Vector3 &v1, const Vector3 &v2) {
	Vector3 result{};

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;
}

// 
Vector3 Vector::Project(const Vector3 &v1, const Vector3 &v2) {
	float dotProduct = Dot(v1, v2);
	float lengthSqV2 = Dot(v2, v2);

	if (lengthSqV2 == 0.0f) {
		return Vector3{ 0.0f,0.0f,0.0f };
	}

	Vector3 result = Multiply(dotProduct / lengthSqV2, v2);

	return result;
}

// 
Vector3 Vector::ClosestPoint(const Vector3 &point, const Segment &segment) {
	Vector3 segmentVector = Subtract(segment.diff, segment.origin);

	Vector3 pointToOrigin = Subtract(point, segment.origin);

	float t = Dot(pointToOrigin, segmentVector) / Dot(segmentVector, segmentVector);

	t = fmaxf(0.0f, fminf(1.0f, t));

	Vector3 closest = Add(segment.origin, Multiply(t, segmentVector));

	return closest;
}

// 
Vector3 Vector::Perpendicular(const Vector3 &vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return{ -vector.y,vector.x,0.0f };
	}

	return { 0.0f,-vector.z,vector.y };
}
