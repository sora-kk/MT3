#include "Matrix.h"

using namespace std;

// ‰Á–@
Matrix4x4 Matrix::add(const Matrix4x4 &m1, const Matrix4x4 &m2) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}

	return result;
}

// Œ¸–@
Matrix4x4 Matrix::Subtract(const Matrix4x4 &m1, const Matrix4x4 &m2) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}

	return result;
}

// Ï
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

// ‹ts—ñ
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

// “]’us—ñ
Matrix4x4 Matrix::Transpose(const Matrix4x4 &m) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m.m[i][j];
		}
	}

	return result;
}

// ’PˆÊs—ñ
Matrix4x4 Matrix::MakeIdentity4x4() {
	Matrix4x4 result{};

	for (int i = 0; i < 4; i++) {
		result.m[i][i] = 1.0f;
	}

	return result;
}

// •½sˆÚ“®s—ñ
Matrix4x4 Matrix::MakeTranslateMatrix(const Vector3 &translate) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;
}

// Šg‘åk¬s—ñ
Matrix4x4 Matrix::MakeScaleMatrix(const Vector3 &scale) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;

	return result;
}

// XŽ²‰ñ“]s—ñ
Matrix4x4 Matrix::MakeRotateXMatrix(float radian) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[1][1] = cos(radian);
	result.m[1][2] = sin(radian);
	result.m[2][1] = -sin(radian);
	result.m[2][2] = cos(radian);

	return result;
}

// YŽ²‰ñ“]s—ñ
Matrix4x4 Matrix::MakeRotateYMatrix(float radian) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[0][0] = cos(radian);
	result.m[0][2] = -sin(radian);
	result.m[2][0] = sin(radian);
	result.m[2][2] = cos(radian);

	return result;
}

// ZŽ²‰ñ“]s—ñ
Matrix4x4 Matrix::MakeRotateZMatrix(float radian) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[0][0] = cos(radian);
	result.m[0][1] = sin(radian);
	result.m[1][0] = -sin(radian);
	result.m[1][1] = cos(radian);

	return result;
}

// ƒAƒtƒBƒ“•ÏŠ·s—ñ
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

// •`‰æŠÖ”
void Matrix::MatrixScreenPrintf(int x, int y, const Matrix4x4 &m) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%.02f", m.m[row][column]);
		}
	}
}