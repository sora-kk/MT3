#include "IsHit.h"

bool IsHit::IsCollision(const SphereData &sphere1, const SphereData &sphere2) {
    // 2つの球の中心間の距離を計算
    float distance = vector.Length(vector.Subtract(sphere2.center, sphere1.center));

    // 中心間の距離が2つの球の半径の合計以下であれば衝突している
    if (distance <= sphere1.radius + sphere2.radius) {
        return true;
    } else {
        return false;
    }
}

bool IsHit::IsCollision(const SphereData &sphere, const PlaneData &plane) {
    // 平面の法線を正規化
    Vector3 normalizedNormal = vector.Normalize(plane.normal);

    // 球の中心から平面までの距離を計算
    float distance = vector.Dot(normalizedNormal, sphere.center) - plane.distance;

    // 距離が球の半径以下であれば衝突
    return std::abs(distance) <= sphere.radius;
}

bool IsHit::IsCollision(const Segment &segment, const PlaneData &plane) {
    // 平面の法線を正規化
    Vector3 normalizedNormal = vector.Normalize(plane.normal);

    // 線分の始点と終点
    Vector3 startPoint = segment.origin;
    Vector3 endPoint = vector.Add(segment.origin, segment.diff);

    // 始点と終点の平面からの距離を計算
    float startDistance = vector.Dot(normalizedNormal, startPoint) - plane.distance;
    float endDistance = vector.Dot(normalizedNormal, endPoint) - plane.distance;

    // 始点と終点が平面の異なる側にある場合、衝突している
    if (startDistance * endDistance <= 0.0f) {
        return true;
    }

    return false;
}
