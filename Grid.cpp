#include "Grid.h"

void Grid::DrawGrid(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix) {
	// 奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; xIndex++) {
		// 始点と終点を求める
		float x = -kGridHalfWidth + (static_cast<float>(xIndex) * kGridEvery);
		Vector3 start = { x,0.0f,-kGridHalfWidth };
		Vector3 end = { x,0.0f,kGridHalfWidth };
		
		// スクリーン座標系まで変換
		Vector3 screenStart = vector.Transform(vector.Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = vector.Transform(vector.Transform(end, viewProjectionMatrix), viewportMatrix);
		
		// 線を描画
		Novice::DrawLine(static_cast<int>(screenStart.x), static_cast<int>(screenStart.y),
						 static_cast<int>(screenEnd.x), static_cast<int>(screenEnd.y),
						 0xAAAAAAFF);

		// センターラインを黒で描画
		if (xIndex == kSubdivision / 2) {
			Novice::DrawLine(static_cast<int>(screenStart.x), static_cast<int>(screenStart.y),
							 static_cast<int>(screenEnd.x), static_cast<int>(screenEnd.y),
							 0x000000FF);
		}
	}

	// 左から右への線を順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; zIndex++) {
		// 始点と終点を求める
		float z = -kGridHalfWidth + (static_cast<float>(zIndex) * kGridEvery);
		Vector3 start = { -kGridHalfWidth,0.0f,z };
		Vector3 end = { kGridHalfWidth,0.0f,z };

		// スクリーン座標系まで変換
		Vector3 screenStart = vector.Transform(vector.Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = vector.Transform(vector.Transform(end, viewProjectionMatrix), viewportMatrix);

		// 線を描画
		Novice::DrawLine(static_cast<int>(screenStart.x), static_cast<int>(screenStart.y),
						 static_cast<int>(screenEnd.x), static_cast<int>(screenEnd.y),
						 0xAAAAAAFF);

		// センターラインを黒で描画
		if (zIndex == kSubdivision / 2) {
			Novice::DrawLine(static_cast<int>(screenStart.x), static_cast<int>(screenStart.y),
							 static_cast<int>(screenEnd.x), static_cast<int>(screenEnd.y),
							 0x000000FF);
		}
	}
}
