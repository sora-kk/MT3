#include <Novice.h>
#include <memory>
#include <imgui.h>
#include "Math.h"
#include "Grid.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "AABB.h"
#include "IsHit.h"

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

	Math math;
	Grid grid;
	IsHit isHit;
	Sphere sphere;
	//Plane plane;
	//Triangle triangle;
	AABB aabb;

	//Segment segment{ {-1.0f,-1.0f,0.0f},{1.5f,1.0f,1.0f} };
	SphereData sphere1{ {0.0f,0.0f,0.0f},0.6f };
	//PlaneData plane1{ {0.0f,1.0f,0.0f},1.0f };
	/*TriangleData triangle1;
	triangle1.vertices[0] = { -1.0f,0.0f,0.0f };
	triangle1.vertices[1] = { 0.0f,-1.0f,0.0f };
	triangle1.vertices[2] = { 1.0f,0.0f,0.0f };*/

	AABBData aabb1{
		.min{-0.5f,-0.5f,-0.5f},
		.max{0.0f,0.0f,0.0f}
	};

	/*AABBData aabb2{
		.min{0.2f,0.2f,0.2f},
		.max{1.0f,1.0f,1.0f}
	};*/

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
		ImGui::DragFloat3("AABB1 Min", &aabb1.min.x, 0.01f);
		ImGui::DragFloat3("AABB1 Max", &aabb1.max.x, 0.01f);
		ImGui::DragFloat3("Sphere1 Center", &sphere1.center.x, 0.01f);
		ImGui::DragFloat("Sphere1 Radius", &sphere1.radius, 0.01f);
		ImGui::End();

		// minとmaxが入れ替わらないように処理
		aabb1.min.x = (std::min)(aabb1.min.x, aabb1.max.x);
		aabb1.min.y = (std::min)(aabb1.min.y, aabb1.max.y);
		aabb1.min.z = (std::min)(aabb1.min.z, aabb1.max.z);
		aabb1.max.x = (std::max)(aabb1.min.x, aabb1.max.x);
		aabb1.max.y = (std::max)(aabb1.min.y, aabb1.max.y);
		aabb1.max.z = (std::max)(aabb1.min.z, aabb1.max.z);

		// 各種行列の計算
		Matrix4x4 worldMatrix = math.MakeAffineMatrix(scale, rotate, translate);
		Matrix4x4 cameraMatrix = math.MakeAffineMatrix(cameraScale, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = math.Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = math.MakePerspectiveFovMatrix(0.45f, kWindowWidth / kWindowHeight, 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = math.Multiply(worldMatrix, math.Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = math.MakeViewportMatrix(0.0f, 0.0f, kWindowWidth, kWindowHeight, 0.0f, 1.0f);

		// 線の始点と終点
		//Vector3 start = math.Transform(math.Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
		//Vector3 end = math.Transform(math.Transform(math.Add(segment.origin, segment.diff), viewProjectionMatrix), viewportMatrix);

		///===================
		/// ↑ 更新処理 ここまで
		///===================

		///===================
		/// ↓ 描画処理 ここから
		///===================

		// グリッド
		grid.DrawGrid(viewProjectionMatrix, viewportMatrix);

		if (isHit.IsCollision(aabb1, sphere1)) {
			aabb.DrawAABB(aabb1, viewProjectionMatrix, viewportMatrix, RED);
		} else {
			aabb.DrawAABB(aabb1, viewProjectionMatrix, viewportMatrix, WHITE);
		}
		
		sphere.DrawSphere(sphere1, viewProjectionMatrix, viewportMatrix, WHITE);


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
