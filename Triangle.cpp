#include "Triangle.h"

void Triangle::DrawTriangle(const TriangleData &triangle, const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, uint32_t color) {
   // 各頂点をワールド座標からスクリーン座標に変換
    Vector3 transformed[3];
    transformed[0] = math.Transform(math.Transform(triangle.vertices[0], viewProjectionMatrix), viewportMatrix);
    transformed[1] = math.Transform(math.Transform(triangle.vertices[1], viewProjectionMatrix), viewportMatrix);
    transformed[2] = math.Transform(math.Transform(triangle.vertices[2], viewProjectionMatrix), viewportMatrix);

    // 三角形を描画
    Novice::DrawLine(static_cast<int>(transformed[0].x), static_cast<int>(transformed[0].y), static_cast<int>(transformed[1].x), static_cast<int>(transformed[1].y), color);
    Novice::DrawLine(static_cast<int>(transformed[1].x), static_cast<int>(transformed[1].y), static_cast<int>(transformed[2].x), static_cast<int>(transformed[2].y), color);
    Novice::DrawLine(static_cast<int>(transformed[0].x), static_cast<int>(transformed[0].y), static_cast<int>(transformed[2].x), static_cast<int>(transformed[2].y), color);
}
