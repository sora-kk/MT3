#include <Novice.h>
#include <memory>
#include "Vector.h"
#include "Matrix.h"

const char kWindowTitle[] = "LC1C_11_ダイドウソラ_MT3_01_00";

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

		Matrix4x4 orthographicMatrix = matrix->MakeOrthographicMatrix(-160.0f, 160.0f, 200.0f, 300.0f, 0.0f, 1000.0f);
		Matrix4x4 perspectiveFovMatrix = matrix->MakePerspectiveFovMatrix(0.63f, 1.33f, 0.1f, 1000.0f);
		Matrix4x4 viewportMatrix = matrix->MakeViewportMatrix(100.0f, 200.0f, 600.0f, 300.0f, 0.0f, 1.0f);

		///===================
		/// ↑ 更新処理 ここまで
		///===================

		///===================
		/// ↓ 描画処理 ここから
		///===================

		matrix->ScreenPrintf(0, 0, orthographicMatrix);
		matrix->ScreenPrintf(0, kRowHeight * 5, perspectiveFovMatrix);
		matrix->ScreenPrintf(0, kRowHeight * 5 * 2, viewportMatrix);

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
