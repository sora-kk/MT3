#include <Novice.h>
#include <memory>
#include "MT3.h"

const char kWindowTitle[] = "LC1C_11_ダイドウソラ_MT3_00_04";

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

	Vector3 rotate{ 0.4f,1.43f,-0.8f };

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

		Matrix4x4 rotateXMatrix = matrix->MakeRotateXMatrix(rotate.x);
		Matrix4x4 rotateYMatrix = matrix->MakeRotateYMatrix(rotate.y);
		Matrix4x4 rotateZMatrix = matrix->MakeRotateZMatrix(rotate.z);

		Matrix4x4 rotateXYZMatrix = matrix->Multiply(rotateXMatrix, matrix->Multiply(rotateYMatrix, rotateZMatrix));

		///===================
		/// ↑ 更新処理 ここまで
		///===================

		///===================
		/// ↓ 描画処理 ここから
		///===================

		matrix->MatrixScreenPrintf(0, 0, rotateXMatrix);
		matrix->MatrixScreenPrintf(0, kRowHeight * 5, rotateYMatrix);
		matrix->MatrixScreenPrintf(0, kRowHeight * 5 * 2, rotateZMatrix);
		matrix->MatrixScreenPrintf(0, kRowHeight * 5 * 3, rotateXYZMatrix);


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
