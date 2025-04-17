#include <Novice.h>
#include <memory>
#include "MT3.h"

const char kWindowTitle[] = "LC1C_11_ダイドウソラ_MT3_00_02";

// ローカル変数の宣言と初期化
const float kWinWidth = 1280.0f;
const float kWinHeight = 720.0f;

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(
		kWindowTitle,
		static_cast<int>(kWinWidth),
		static_cast<int>(kWinHeight)
	);

	///====================
	/// ↓ 変数の宣言と初期化
	///====================

	std::unique_ptr<Vector> vector;
	std::unique_ptr<Matrix> matrix;

	Matrix4x4 m1 = {
			3.2f,0.7f,9.6f,4.4f,
			5.5f,1.3f,7.8f,2.1f,
			6.9f,8.0f,2.6f,1.0f,
			0.5f,7.2f,5.1f,3.3f
	};

	Matrix4x4 m2 = {
		4.1f,6.5f,3.3f,2.2f,
		8.8f,0.6f,9.9f,7.7f,
		1.1f,5.5f,6.6f,0.0f,
		3.3f,9.9f,8.8f,2.2f
	};

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	///====================
	/// ↑ 変数の宣言と初期化
	///====================

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///===================
		/// ↓ 更新処理 ここから
		///===================

		Matrix4x4 resultAdd = matrix->add(m1, m2);
		Matrix4x4 resultMultiply = matrix->Multiply(m1, m2);
		Matrix4x4 resultSubtract = matrix->Subtract(m1, m2);
		Matrix4x4 inverseM1 = matrix->Inverse(m1);
		Matrix4x4 inverseM2 = matrix->Inverse(m2);
		Matrix4x4 transposeM1 = matrix->Transpose(m1);
		Matrix4x4 transposeM2 = matrix->Transpose(m2);
		Matrix4x4 identity = matrix->MakeIdentity4x4();

		///===================
		/// ↑ 更新処理 ここまで
		///===================

		///===================
		/// ↓ 描画処理 ここから
		///===================

		matrix->MatrixScreenPrintf(0, 0, resultAdd);
		matrix->MatrixScreenPrintf(0, kRowHeight * 5, resultMultiply);
		matrix->MatrixScreenPrintf(0, kRowHeight * 5 * 2, resultSubtract);
		matrix->MatrixScreenPrintf(0, kRowHeight * 5 * 3, inverseM1);
		matrix->MatrixScreenPrintf(0, kRowHeight * 5 * 4, inverseM2);
		matrix->MatrixScreenPrintf(kColumnWidth * 5, 0, transposeM1);
		matrix->MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5, transposeM2);
		matrix->MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5 * 2, identity);

		///===================
		/// ↑ 描画処理 ここまで
		///===================

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
