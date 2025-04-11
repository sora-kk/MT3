#include <Novice.h>
#include <memory>
#include "MT3.h"

const char kWindowTitle[] = "LC1C_11_ダイドウソラ_MT3_00_01";

// ローカル変数の宣言と初期化
const float kWinWidth = 1280.0f;
const float kWinHeight = 720.0f;

static const float kRowHeight = 20.0f;

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

	Vector3	v1{ 1.0f,3.0f,-5.0f };
	Vector3	v2{ 4.0f,-1.0f,2.0f };
	float k = 4.0f;

	std::unique_ptr<Vector> vector;

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

		Vector3 resultAdd = vector->Add(v1, v2);
		Vector3 resultSubtract = vector->Subtract(v1, v2);
		Vector3 resultMultiply = vector->Multiply(k, v1);
		float resultDot = vector->Dot(v1, v2);
		float resultLength = vector->Length(v1);
		Vector3 resultNormalize = vector->Normalize(v2);

		///===================
		/// ↑ 更新処理 ここまで
		///===================

		///===================
		/// ↓ 描画処理 ここから
		///===================

		vector->VectorScreenPrintf(Vector2{ 0.0f,0.0f }, resultAdd, " : Add");
		vector->VectorScreenPrintf(Vector2{ 0.0f,kRowHeight }, resultSubtract, " : Subtract");
		vector->VectorScreenPrintf(Vector2{ 0.0f,kRowHeight * 2.0f }, resultMultiply, " : Multiply");
		Novice::ScreenPrintf(0, static_cast<int>(kRowHeight * 3.0f), "%.02f : Dot", resultDot);
		Novice::ScreenPrintf(0, static_cast<int>(kRowHeight * 4.0f), "%.02f : Length", resultLength);
		vector->VectorScreenPrintf(Vector2{ 0.0f,kRowHeight * 5.0f }, resultNormalize, " : Normalize");

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
