#include "Math.h"

// 加算
Vector3 Math::Add(const Vector3 &v1, const Vector3 &v2) {
	Vector3 result = { v1.x + v2.x,v1.y + v2.y,v1.z + v2.z };
	return result;
}

// 減算
Vector3 Math::Subtract(const Vector3 &v1, const Vector3 &v2) {
	Vector3 result = { v1.x - v2.x,v1.y - v2.y,v1.z - v2.z };
	return result;
}

// 乗算(スカラー倍)
Vector3 Math::Multiply(float scalar, const Vector3 &v) {
	Vector3 result = { scalar * v.x,scalar * v.y,scalar * v.z };
	return result;
}

// 内積
float Math::Dot(const Vector3 &v1, const Vector3 &v2) {
	float result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return result;
}

// ノルム(長さ)
float Math::Length(const Vector3 &v) {
	float result = sqrtf({ v.x * v.x + v.y * v.y + v.z * v.z });
	return result;
}

// 正規化
Vector3 Math::Normalize(const Vector3 &v) {
	Vector3 result = { v.x / Length(v),v.y / Length(v),v.z / Length(v) };
	return result;
}

// 座標変換
Vector3 Math::Transform(const Vector3 &vector, const Matrix4x4 &matrix) {
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
Vector3 Math::Cross(const Vector3 &v1, const Vector3 &v2) {
	Vector3 result{};

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;
}

// 
Vector3 Math::Project(const Vector3 &v1, const Vector3 &v2) {
	float dotProduct = Dot(v1, v2);
	float lengthSqV2 = Dot(v2, v2);

	if (lengthSqV2 == 0.0f) {
		return Vector3{ 0.0f,0.0f,0.0f };
	}

	Vector3 result = Multiply(dotProduct / lengthSqV2, v2);

	return result;
}

// 
Vector3 Math::ClosestPoint(const Vector3 &point, const Segment &segment) {
	Vector3 segmentVector = Subtract(segment.diff, segment.origin);

	Vector3 pointToOrigin = Subtract(point, segment.origin);

	float t = Dot(pointToOrigin, segmentVector) / Dot(segmentVector, segmentVector);

	t = fmaxf(0.0f, fminf(1.0f, t));

	Vector3 closest = Add(segment.origin, Multiply(t, segmentVector));

	return closest;
}

// 
Vector3 Math::Perpendicular(const Vector3 &vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return{ -vector.y,vector.x,0.0f };
	}

	return { 0.0f,-vector.z,vector.y };
}

// 加法
Matrix4x4 Math::add(const Matrix4x4 &m1, const Matrix4x4 &m2) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}

	return result;
}

// 減法
Matrix4x4 Math::Subtract(const Matrix4x4 &m1, const Matrix4x4 &m2) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}

	return result;
}

// 積
Matrix4x4 Math::Multiply(const Matrix4x4 &m1, const Matrix4x4 &m2) {
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

// 逆行列
Matrix4x4 Math::Inverse(const Matrix4x4 &m) {
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

	// 行列式がゼロの場合は単位行列を返す
	if (determinant == 0.0f) {
		return MakeIdentity4x4();
	}

	// 逆行列の計算（行列式を利用）
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

// 転置行列
Matrix4x4 Math::Transpose(const Matrix4x4 &m) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m.m[i][j];
		}
	}

	return result;
}

// 単位行列
Matrix4x4 Math::MakeIdentity4x4() {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		result.m[i][i] = 1.0f;
	}

	return result;
}

// 平行移動行列
Matrix4x4 Math::MakeTranslateMatrix(const Vector3 &translate) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;
}

// 拡大縮小行列
Matrix4x4 Math::MakeScaleMatrix(const Vector3 &scale) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;

	return result;
}

// X軸回転行列
Matrix4x4 Math::MakeRotateXMatrix(float radian) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[1][1] = cos(radian);
	result.m[1][2] = sin(radian);
	result.m[2][1] = -sin(radian);
	result.m[2][2] = cos(radian);

	return result;
}

// Y軸回転行列
Matrix4x4 Math::MakeRotateYMatrix(float radian) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[0][0] = cos(radian);
	result.m[0][2] = -sin(radian);
	result.m[2][0] = sin(radian);
	result.m[2][2] = cos(radian);

	return result;
}

// Z軸回転行列
Matrix4x4 Math::MakeRotateZMatrix(float radian) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[0][0] = cos(radian);
	result.m[0][1] = sin(radian);
	result.m[1][0] = -sin(radian);
	result.m[1][1] = cos(radian);

	return result;
}

// アフィン変換行列
Matrix4x4 Math::MakeAffineMatrix(const Vector3 &scale, const Vector3 &rotate, const Vector3 &translate) {
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

	Matrix4x4 affineMatrix = Multiply(translateMatrix, Multiply(rotateXYZMatrix, scaleMatrix));
	return affineMatrix;
}

// 透視投影行列
Matrix4x4 Math::MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result{};
	float f = 1.0f / tan(fovY / 2.0f);
	float fRange = farClip / (farClip - nearClip);

	result.m[0][0] = f / aspectRatio;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = fRange;
	result.m[2][3] = 1.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = -fRange * nearClip;
	result.m[3][3] = 0.0f;

	return result;
}

// 正射影行列
Matrix4x4 Math::MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result{};
	float width = right - left;
	float height = top - bottom;
	float depth = farClip - nearClip;

	result.m[0][0] = 2.0f / width;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 2.0f / height;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f / depth;
	result.m[2][3] = 0.0f;

	result.m[3][0] = -(right + left) / width;
	result.m[3][1] = -(top + bottom) / height;
	result.m[3][2] = -nearClip / depth;
	result.m[3][3] = 1.0f;

	return result;
}

// ビューポート変換
Matrix4x4 Math::MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result{};

	result.m[0][0] = width / 2.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = -height / 2.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = (maxDepth - minDepth) / 2.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = left + width / 2.0f;
	result.m[3][1] = top + height / 2.0f;
	result.m[3][2] = (maxDepth + minDepth) / 2.0f;
	result.m[3][3] = 1.0f;

	return result;
}

// 描画関数
void Math::ScreenPrintf(const Vector2 &pos, const Vector3 &vector, const char *label) {
	Novice::ScreenPrintf(static_cast<int>(pos.x), static_cast<int>(pos.y), "%.02f", vector.x);
	Novice::ScreenPrintf(static_cast<int>(pos.x + kColumnWidth), static_cast<int>(pos.y), "%.02f", vector.y);
	Novice::ScreenPrintf(static_cast<int>(pos.x + kColumnWidth * 2), static_cast<int>(pos.y), "%.02f", vector.z);
	Novice::ScreenPrintf(static_cast<int>(pos.x + kColumnWidth * 3), static_cast<int>(pos.y), "%s", label);
}

// 描画関数
void Math::ScreenPrintf(int x, int y, const Matrix4x4 &m) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%.02f", m.m[row][column]);
		}
	}
}