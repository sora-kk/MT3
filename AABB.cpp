#include "AABB.h"

void AABB::DrawAABB(const AABBData &aabb, const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, uint32_t color) {
    // AABBの8つの頂点を計算
    Vector3 vertices[8] = {
        {aabb.min.x, aabb.min.y, aabb.min.z}, // 左下奥
        {aabb.max.x, aabb.min.y, aabb.min.z}, // 右下奥
        {aabb.min.x, aabb.max.y, aabb.min.z}, // 左上奥
        {aabb.max.x, aabb.max.y, aabb.min.z}, // 右上奥
        {aabb.min.x, aabb.min.y, aabb.max.z}, // 左下手前
        {aabb.max.x, aabb.min.y, aabb.max.z}, // 右下手前
        {aabb.min.x, aabb.max.y, aabb.max.z}, // 左上手前
        {aabb.max.x, aabb.max.y, aabb.max.z}  // 右上手前
    };

    // スクリーン座標系に変換
    Vector3 screenVertices[8];
    for (int i = 0; i < 8; ++i) {
        screenVertices[i] = math.Transform(math.Transform(vertices[i], viewProjectionMatrix), viewportMatrix);
    }

    // AABBの辺を描画
    int edges[12][2] = {
        {0, 1}, {1, 3}, {3, 2}, {2, 0}, // 奥の面
        {4, 5}, {5, 7}, {7, 6}, {6, 4}, // 手前の面
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // 奥と手前を結ぶ辺
    };

    for (int i = 0; i < 12; ++i) {
        Novice::DrawLine(
            static_cast<int>(screenVertices[edges[i][0]].x), static_cast<int>(screenVertices[edges[i][0]].y),
            static_cast<int>(screenVertices[edges[i][1]].x), static_cast<int>(screenVertices[edges[i][1]].y),
            color
        );
    }
}
