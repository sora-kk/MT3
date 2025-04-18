#include "MT3.h"

// 3次元ベクトルの加算
Vector3 Vector::Add(const Vector3 &v1, const Vector3 &v2) {
	Vector3 result = { v1.x + v2.x,v1.y + v2.y,v1.z + v2.z };
	return result;
}

// 3次元ベクトルの減算
Vector3 Vector::Subtract(const Vector3 &v1, const Vector3 &v2) {
	Vector3 result = { v1.x - v2.x,v1.y - v2.y,v1.z - v2.z };
	return result;
}

// 3次元ベクトルの乗算(スカラー倍)
Vector3 Vector::Multiply(float scalar, const Vector3 &v) {
	Vector3 result = { scalar * v.x,scalar * v.y,scalar * v.z };
	return result;
}

// 3次元ベクトルの内積
float Vector::Dot(const Vector3 &v1, const Vector3 &v2) {
	float result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return result;
}

// 3次元ベクトルのノルム(長さ)
float Vector::Length(const Vector3 &v) {
	float result = sqrtf({ v.x * v.x + v.y * v.y + v.z * v.z });
	return result;
}

// 3次元ベクトルの正規化
Vector3 Vector::Normalize(const Vector3 &v) {
	Vector3 result = { v.x / Length(v),v.y / Length(v),v.z / Length(v) };
	return result;
}

// 描画関数
void Vector::VectorScreenPrintf(const Vector2 &pos, const Vector3 &vector, const char *label) {
	Novice::ScreenPrintf(static_cast<int>(pos.x), static_cast<int>(pos.y), "%.02f", vector.x);
	Novice::ScreenPrintf(static_cast<int>(pos.x + kColumnWidth), static_cast<int>(pos.y), "%.02f", vector.y);
	Novice::ScreenPrintf(static_cast<int>(pos.x + kColumnWidth * 2), static_cast<int>(pos.y), "%.02f", vector.z);
	Novice::ScreenPrintf(static_cast<int>(pos.x + kColumnWidth * 3), static_cast<int>(pos.y), "%s", label);
}

// 3次元ベクトルの座標変換
Vector3 Vector::Transform(const Vector3 &vector, const Matrix4x4 &matrix) {
	Vector3 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return Vector3();
}

// 4x4行列の加法
Matrix4x4 Matrix::add(const Matrix4x4 &m1, const Matrix4x4 &m2) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}

	return result;
}

// 4x4行列の減法
Matrix4x4 Matrix::Subtract(const Matrix4x4 &m1, const Matrix4x4 &m2) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}

	return result;
}

// 4x4行列の積
Matrix4x4 Matrix::Multiply(const Matrix4x4 &m1, const Matrix4x4 &m2) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	return result;
}

// 4x4逆行列
Matrix4x4 Matrix::Inverse(const Matrix4x4 &m) {
	Matrix4x4 result{};

	float determinant =
		m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]
		+ m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]
		+ m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]
		- m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]
		- m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]
		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]
		- m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]
		- m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]
		+ m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]
		+ m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]
		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]
		+ m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]
		- m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]
		- m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]
		- m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]
		+ m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]
		+ m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];

	result.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3]
					  + m.m[1][2] * m.m[2][3] * m.m[3][1]
					  + m.m[1][3] * m.m[2][1] * m.m[3][2]
					  - m.m[1][3] * m.m[2][2] * m.m[3][1]
					  - m.m[1][2] * m.m[2][1] * m.m[3][3]
					  - m.m[1][1] * m.m[2][3] * m.m[3][2]) / determinant;
	result.m[0][1] = -(m.m[0][1] * m.m[2][2] * m.m[3][3]
					   + m.m[0][2] * m.m[2][3] * m.m[3][1]
					   + m.m[0][3] * m.m[2][1] * m.m[3][2]
					   - m.m[0][3] * m.m[2][2] * m.m[3][1]
					   - m.m[0][2] * m.m[2][1] * m.m[3][3]
					   - m.m[0][1] * m.m[2][3] * m.m[3][2]) / determinant;
	result.m[0][2] = (m.m[0][1] * m.m[1][2] * m.m[3][3]
					  + m.m[0][2] * m.m[1][3] * m.m[3][1]
					  + m.m[0][3] * m.m[1][1] * m.m[3][2]
					  - m.m[0][3] * m.m[1][2] * m.m[3][1]
					  - m.m[0][2] * m.m[1][1] * m.m[3][3]
					  - m.m[0][1] * m.m[1][3] * m.m[3][2]) / determinant;
	result.m[0][3] = (m.m[0][1] * m.m[1][2] * m.m[2][3]
					  + m.m[0][2] * m.m[1][3] * m.m[2][1]
					  + m.m[0][3] * m.m[1][1] * m.m[2][2]
					  - m.m[0][3] * m.m[1][2] * m.m[2][1]
					  - m.m[0][2] * m.m[1][1] * m.m[2][3]
					  - m.m[0][1] * m.m[1][3] * m.m[2][2]) / determinant;

	result.m[1][0] = -(m.m[1][0] * m.m[2][2] * m.m[3][3]
					   + m.m[1][2] * m.m[2][3] * m.m[3][0]
					   + m.m[1][3] * m.m[2][0] * m.m[3][2]
					   - m.m[1][3] * m.m[2][2] * m.m[3][0]
					   - m.m[1][2] * m.m[2][0] * m.m[3][3]
					   - m.m[1][0] * m.m[2][3] * m.m[3][2]) / determinant;
	result.m[1][1] = (m.m[0][0] * m.m[2][2] * m.m[3][3]
					  + m.m[0][2] * m.m[2][3] * m.m[3][0]
					  + m.m[0][3] * m.m[2][0] * m.m[3][2]
					  - m.m[0][3] * m.m[2][2] * m.m[3][0]
					  - m.m[0][2] * m.m[2][0] * m.m[3][3]
					  - m.m[0][0] * m.m[2][3] * m.m[3][2]) / determinant;
	result.m[1][2] = -(m.m[0][0] * m.m[1][2] * m.m[3][3]
					   + m.m[0][2] * m.m[1][3] * m.m[3][0]
					   + m.m[0][3] * m.m[1][0] * m.m[3][2]
					   - m.m[0][3] * m.m[1][2] * m.m[3][0]
					   - m.m[0][2] * m.m[1][0] * m.m[3][3]
					   - m.m[0][0] * m.m[1][3] * m.m[3][2]) / determinant;
	result.m[1][3] = (m.m[0][0] * m.m[1][2] * m.m[2][3]
					  + m.m[0][2] * m.m[1][3] * m.m[2][0]
					  + m.m[0][3] * m.m[1][0] * m.m[2][2]
					  - m.m[0][3] * m.m[1][2] * m.m[2][0]
					  - m.m[0][2] * m.m[1][0] * m.m[2][3]
					  - m.m[0][0] * m.m[1][3] * m.m[2][2]) / determinant;

	result.m[2][0] = (m.m[1][0] * m.m[2][1] * m.m[3][3]
					  + m.m[1][1] * m.m[2][3] * m.m[3][0]
					  + m.m[1][3] * m.m[2][0] * m.m[3][1]
					  - m.m[1][3] * m.m[2][1] * m.m[3][0]
					  - m.m[1][1] * m.m[2][0] * m.m[3][3]
					  - m.m[1][0] * m.m[2][3] * m.m[3][1]) / determinant;
	result.m[2][1] = -(m.m[0][0] * m.m[2][1] * m.m[3][3]
					   + m.m[0][1] * m.m[2][3] * m.m[3][0]
					   + m.m[0][3] * m.m[2][0] * m.m[3][1]
					   - m.m[0][3] * m.m[2][1] * m.m[3][0]
					   - m.m[0][1] * m.m[2][0] * m.m[3][3]
					   - m.m[0][0] * m.m[2][3] * m.m[3][1]) / determinant;
	result.m[2][2] = (m.m[0][0] * m.m[1][1] * m.m[3][3]
					  + m.m[0][1] * m.m[1][3] * m.m[3][0]
					  + m.m[0][3] * m.m[1][0] * m.m[3][1]
					  - m.m[0][3] * m.m[1][1] * m.m[3][0]
					  - m.m[0][1] * m.m[1][0] * m.m[3][3]
					  - m.m[0][0] * m.m[1][3] * m.m[3][1]) / determinant;
	result.m[2][3] = (m.m[0][0] * m.m[1][1] * m.m[2][3]
					  + m.m[0][1] * m.m[1][3] * m.m[2][0]
					  + m.m[0][3] * m.m[1][0] * m.m[2][1]
					  - m.m[0][3] * m.m[1][1] * m.m[2][0]
					  - m.m[0][1] * m.m[1][0] * m.m[2][3]
					  - m.m[0][0] * m.m[1][3] * m.m[2][1]) / determinant;

	result.m[3][0] = (m.m[1][0] * m.m[2][1] * m.m[3][2]
					  + m.m[1][1] * m.m[2][2] * m.m[3][0]
					  + m.m[1][2] * m.m[2][0] * m.m[3][1]
					  - m.m[1][2] * m.m[2][1] * m.m[3][0]
					  - m.m[1][1] * m.m[2][0] * m.m[3][2]
					  - m.m[1][0] * m.m[2][2] * m.m[3][1]) / determinant;
	result.m[3][1] = -(m.m[0][0] * m.m[2][1] * m.m[3][2]
					   + m.m[0][1] * m.m[2][2] * m.m[3][0]
					   + m.m[0][2] * m.m[2][0] * m.m[3][1]
					   - m.m[0][2] * m.m[2][1] * m.m[3][0]
					   - m.m[0][1] * m.m[2][0] * m.m[3][2]
					   - m.m[0][0] * m.m[2][2] * m.m[3][1]) / determinant;
	result.m[3][2] = (m.m[0][0] * m.m[1][1] * m.m[3][2]
					  + m.m[0][1] * m.m[1][2] * m.m[3][0]
					  + m.m[0][2] * m.m[1][0] * m.m[3][1]
					  - m.m[0][2] * m.m[1][1] * m.m[3][0]
					  - m.m[0][1] * m.m[1][0] * m.m[3][2]
					  - m.m[0][0] * m.m[1][2] * m.m[3][1]) / determinant;
	result.m[3][3] = (m.m[0][0] * m.m[1][1] * m.m[2][2]
					  + m.m[0][1] * m.m[1][2] * m.m[2][0]
					  + m.m[0][2] * m.m[1][0] * m.m[2][1]
					  - m.m[0][2] * m.m[1][1] * m.m[2][0]
					  - m.m[0][1] * m.m[1][0] * m.m[2][2]
					  - m.m[0][0] * m.m[1][2] * m.m[2][1]) / determinant;

	return result;
}

// 4x4転置行列
Matrix4x4 Matrix::Transpose(const Matrix4x4 &m) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m.m[i][j];
		}
	}

	return result;
}

// 4x4単位行列
Matrix4x4 Matrix::MakeIdentity4x4() {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		result.m[i][i] = 1.0f;
	}

	return result;
}

// 描画関数
void Matrix::MatrixScreenPrintf(int x, int y, const Matrix4x4 &m) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%.01f", m.m[row][column]);
		}
	}
}

// 4x4平行移動行列
Matrix4x4 Matrix::MakeTranslateMatrix(const Vector3 &translate) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;
}

// 4x4拡大縮小行列
Matrix4x4 Matrix::MakeScaleMatrix(const Vector3 &scale) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;

	return Matrix4x4();
}
