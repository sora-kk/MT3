#include <Novice.h>
#include <memory>
#include "Vector.h"
#include "Matrix.h"

const char kWindowTitle[] = "LC1C_11_ダイドウソラ_MT3_01_00";

// ローカル変数の宣言と初期化
const int kWinWidth = 1280;
const int kWinHeight = 720;

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

	Vector vector;
	Matrix matrix;

	Vector3 scale{ 1.0f,1.0f,1.0f };
	Vector3 rotate{ 0.0f,0.0f,0.0f };
	Vector3 translate{ 0.0f,0.0f,0.0f };

	Vector3 cameraScale{ 1.0f,1.0f,1.0f };
	Vector3 cameraRotate{ 0.0f,0.0f,0.0f };
	Vector3 cameraPos{ 0.0,0.0,-100.0f };

	static const Vector3 kLocalVertices[3] = {
		{-8.0f, 16.0f, 0.0f},
		{8.0f, 16.0f, 0.0f},
		{0.0f, -16.0f, 0.0f}
	};

	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };

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

		Vector3 cross = vector.Cross(v1, v2);

		// WSキーで前後に移動
		if (keys[DIK_W]) {
			translate.z += 1.0f;
		} else if (keys[DIK_S]) {
			translate.z -= 1.0f;
		}

		// ADキーで左右に移動
		if (keys[DIK_A]) {
			translate.x += 1.0f;
		} else if (keys[DIK_D]) {
			translate.x -= 1.0f;
		}

		// Y軸回転させる
		rotate.y += 0.03f;

		// 各種行列の計算
		Matrix4x4 worldMatrix = matrix.MakeAffineMatrix(scale, rotate, translate);
		Matrix4x4 cameraMatrix = matrix.MakeAffineMatrix(cameraScale, cameraRotate, cameraPos);
		Matrix4x4 viewMatrix = matrix.Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = matrix.MakePerspectiveFovMatrix(0.45f, static_cast<float>(kWinWidth / kWinHeight), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = matrix.Multiply(worldMatrix, matrix.Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = matrix.MakeViewportMatrix(0.0f, 0.0f, static_cast<float>(kWinWidth), static_cast<float>(kWinHeight), 0.0f, 1.0f);
		Vector3 screenVertices[3];
		for (int i = 0; i < 3; i++) {
			Vector3 ndcVertex = vector.Transform(kLocalVertices[i], worldViewProjectionMatrix);
			screenVertices[i] = vector.Transform(ndcVertex, viewportMatrix);
		}

		///===================
		/// ↑ 更新処理 ここまで
		///===================

		///===================
		/// ↓ 描画処理 ここから
		///===================

		vector.ScreenPrintf({ 0.0f,0.0f }, cross, "Cross");

		Novice::DrawLine(0, kWinHeight / 2, kWinWidth, kWinHeight / 2, 0xFFFFFFFF);
		Novice::DrawLine(kWinWidth / 2, 0, kWinWidth / 2, kWinHeight, 0xFFFFFFFF);

		Novice::DrawTriangle(
			static_cast<int>(screenVertices[0].x),
			static_cast<int>(screenVertices[0].y),
			static_cast<int>(screenVertices[1].x),
			static_cast<int>(screenVertices[1].y),
			static_cast<int>(screenVertices[2].x),
			static_cast<int>(screenVertices[2].y),
			RED,
			kFillModeSolid
		);

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
