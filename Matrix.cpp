#include "Matrix.h"

using namespace std;

// 加法
Matrix4x4 Matrix::add(const Matrix4x4 &m1, const Matrix4x4 &m2) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}

	return result;
}

// 減法
Matrix4x4 Matrix::Subtract(const Matrix4x4 &m1, const Matrix4x4 &m2) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}

	return result;
}

// 積
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

// 逆行列
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

// 転置行列
Matrix4x4 Matrix::Transpose(const Matrix4x4 &m) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m.m[i][j];
		}
	}

	return result;
}

// 単位行列
Matrix4x4 Matrix::MakeIdentity4x4() {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		result.m[i][i] = 1.0f;
	}

	return result;
}

// 平行移動行列
Matrix4x4 Matrix::MakeTranslateMatrix(const Vector3 &translate) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;
}

// 拡大縮小行列
Matrix4x4 Matrix::MakeScaleMatrix(const Vector3 &scale) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;

	return result;
}

// X軸回転行列
Matrix4x4 Matrix::MakeRotateXMatrix(float radian) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[1][1] = cos(radian);
	result.m[1][2] = sin(radian);
	result.m[2][1] = -sin(radian);
	result.m[2][2] = cos(radian);

	return result;
}

// Y軸回転行列
Matrix4x4 Matrix::MakeRotateYMatrix(float radian) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[0][0] = cos(radian);
	result.m[0][2] = -sin(radian);
	result.m[2][0] = sin(radian);
	result.m[2][2] = cos(radian);

	return result;
}

// Z軸回転行列
Matrix4x4 Matrix::MakeRotateZMatrix(float radian) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[0][0] = cos(radian);
	result.m[0][1] = sin(radian);
	result.m[1][0] = -sin(radian);
	result.m[1][1] = cos(radian);

	return result;
}

// アフィン変換行列
Matrix4x4 Matrix::MakeAffineMatrix(const Vector3 &scale, const Vector3 &rotate, const Vector3 &translate) {
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

	Matrix4x4 affineMatrix = Multiply(scaleMatrix, Multiply(rotateXYZMatrix, translateMatrix));
	return affineMatrix;
}

// 透視投影行列
Matrix4x4 Matrix::MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
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
Matrix4x4 Matrix::MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
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
Matrix4x4 Matrix::MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
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
	result.m[2][2] = maxDepth - minDepth;
	result.m[2][3] = 0.0f;

	result.m[3][0] = left + width / 2.0f;
	result.m[3][1] = top + height / 2.0f;
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;

	return result;
}

// 描画関数
void Matrix::ScreenPrintf(int x, int y, const Matrix4x4 &m) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%.02f", m.m[row][column]);
		}
	}
}