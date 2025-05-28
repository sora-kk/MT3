#include <Novice.h>
#include <memory>
#include <imgui.h>
#include "Vector.h"
#include "Matrix.h"
#include "Grid.h"
#include "Sphere.h"

const char kWindowTitle[] = "LC1C_11_ダイドウソラ_MT3_01_00";

// ローカル変数の宣言と初期化
const float kWindowWidth = 1280.0f;
const float kWindowHeight = 720.0f;

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, static_cast<int>(kWindowWidth), static_cast<int>(kWindowHeight));

	///====================
	/// ↓ 変数の宣言と初期化
	///====================

	//Vector vector;
	Matrix matrix;
	Grid grid;
	Sphere sphere;

	SphereData sphere1{ {0.0f,0.0f,0.0f},0.6f };
	SphereData sphere2{ {-1.0f,0.0f,-1.0f},0.4f };

	Vector3 scale{ 1.0f,1.0f,1.0f };
	Vector3 rotate{ 0.0f,0.0f,0.0f };
	Vector3 translate{ 0.0f,0.0f,0.0f };

	Vector3 cameraScale{ 1.0f,1.0f,1.0f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };
	Vector3 cameraTranslate{ 0.0f,0.0f,-7.49f };

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

		// ImGuiを呼び出す
		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("Sphere1 Center", &sphere1.center.x, 0.01f);
		ImGui::DragFloat("Sphere1 Radius", &sphere1.radius, 0.01f);
		ImGui::DragFloat3("Sphere2 Center", &sphere2.center.x, 0.01f);
		ImGui::DragFloat("Sphere2 Radius", &sphere2.radius, 0.01f);
		ImGui::End();

		// 各種行列の計算
		Matrix4x4 worldMatrix = matrix.MakeAffineMatrix(scale, rotate, translate);
		Matrix4x4 cameraMatrix = matrix.MakeAffineMatrix(cameraScale, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = matrix.Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = matrix.MakePerspectiveFovMatrix(0.45f, kWindowWidth / kWindowHeight, 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = matrix.Multiply(worldMatrix, matrix.Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = matrix.MakeViewportMatrix(0.0f, 0.0f, kWindowWidth, kWindowHeight, 0.0f, 1.0f);

		///===================
		/// ↑ 更新処理 ここまで
		///===================

		///===================
		/// ↓ 描画処理 ここから
		///===================

		// グリッド
		grid.DrawGrid(worldViewProjectionMatrix, viewportMatrix);

		// 球体
		if (sphere.IsCollision(sphere1, sphere2)) {
			sphere.DrawSphere(sphere1, worldViewProjectionMatrix, viewportMatrix, RED);
		} else {
			sphere.DrawSphere(sphere1, worldViewProjectionMatrix, viewportMatrix, WHITE);
		}
		sphere.DrawSphere(sphere2, worldViewProjectionMatrix, viewportMatrix, WHITE);

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
