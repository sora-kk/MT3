#include "MT3.h"

// 加算
Vector3 Vector::Add(const Vector3 &v1, const Vector3 &v2){
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
void Vector::VectorScreenPrintf(const Vector2 &pos, const Vector3 &vector, const char *label) {
	Novice::ScreenPrintf(static_cast<int>(pos.x), static_cast<int>(pos.y), "%.02f", vector.x);
	Novice::ScreenPrintf(static_cast<int>(pos.x+kColumnWidth), static_cast<int>(pos.y), "%.02f", vector.y);
	Novice::ScreenPrintf(static_cast<int>(pos.x + kColumnWidth*2), static_cast<int>(pos.y), "%.02f", vector.z);
	Novice::ScreenPrintf(static_cast<int>(pos.x + kColumnWidth * 3), static_cast<int>(pos.y), "%s", label);
}