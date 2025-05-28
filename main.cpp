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

	Vector vector;
	Matrix matrix;
	Grid grid;
	Sphere sphere;

	Segment segment = { {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} };
	Vector3 point = { -1.5f,0.6f,0.6f };

	Vector3 project = vector.Project(vector.Subtract(point, segment.origin), segment.diff);
	Vector3 closestPoint = vector.ClosestPoint(point, segment);

	SphereData pointSphere{ point,0.01f };
	SphereData closestPointSphere{ closestPoint,0.01f };

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
		ImGui::InputFloat3("Point", &point.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("Segment origin", &segment.origin.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("Segment diff", &segment.diff.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("Project", &project.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::End();

		// 各種行列の計算
		Matrix4x4 worldMatrix = matrix.MakeAffineMatrix(scale, rotate, translate);
		Matrix4x4 cameraMatrix = matrix.MakeAffineMatrix(cameraScale, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = matrix.Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = matrix.MakePerspectiveFovMatrix(0.45f, kWindowWidth / kWindowHeight, 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = matrix.Multiply(worldMatrix, matrix.Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = matrix.MakeViewportMatrix(0.0f, 0.0f, kWindowWidth, kWindowHeight, 0.0f, 1.0f);
		
		// 線分の始点と終点
		Vector3 start = vector.Transform(vector.Transform(segment.origin, worldViewProjectionMatrix), viewportMatrix);
		Vector3 end = vector.Transform(vector.Transform(vector.Add(segment.origin,segment.diff), worldViewProjectionMatrix), viewportMatrix);

		///===================
		/// ↑ 更新処理 ここまで
		///===================

		///===================
		/// ↓ 描画処理 ここから
		///===================

		// グリッド
		grid.DrawGrid(worldViewProjectionMatrix, viewportMatrix);

		// 線分
		Novice::DrawLine(static_cast<int>(start.x), static_cast<int>(start.y), static_cast<int>(end.x), static_cast<int>(end.y), WHITE);

		// 球体
		sphere.DrawSphere(pointSphere, worldViewProjectionMatrix, viewportMatrix, RED);
		sphere.DrawSphere(closestPointSphere, worldViewProjectionMatrix, viewportMatrix, BLACK);

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
