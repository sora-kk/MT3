#include "IsHit.h"

bool IsHit::IsCollision(const SphereData &sphere1, const SphereData &sphere2) {
    // 2つの球の中心間の距離を計算
    float distance = math.Length(math.Subtract(sphere2.center, sphere1.center));

    // 中心間の距離が2つの球の半径の合計以下であれば衝突している
    if (distance <= sphere1.radius + sphere2.radius) {
        return true;
    } else {
        return false;
    }
}

bool IsHit::IsCollision(const SphereData &sphere, const PlaneData &plane) {
    // 平面の法線を正規化
    Vector3 normalizedNormal = math.Normalize(plane.normal);

    // 球の中心から平面までの距離を計算
    float distance = math.Dot(normalizedNormal, sphere.center) - plane.distance;

    // 距離が球の半径以下であれば衝突
    return std::abs(distance) <= sphere.radius;
}

bool IsHit::IsCollision(const Segment &segment, const PlaneData &plane) {
    // 平面の法線を正規化
    Vector3 normalizedNormal = math.Normalize(plane.normal);

    // 線分の始点と終点
    Vector3 startPoint = segment.origin;
    Vector3 endPoint = math.Add(segment.origin, segment.diff);

    // 始点と終点の平面からの距離を計算
    float startDistance = math.Dot(normalizedNormal, startPoint) - plane.distance;
    float endDistance = math.Dot(normalizedNormal, endPoint) - plane.distance;

    // 始点と終点が平面の異なる側にある場合、衝突している
    if (startDistance * endDistance <= 0.0f) {
        return true;
    }

    return false;
}

bool IsHit::IsCollision(const TriangleData &triangle, const Segment &segment) {
    // 線分の始点と終点
    Vector3 startPoint = segment.origin;
    Vector3 endPoint = math.Add(segment.origin, segment.diff);

    // 三角形の法線を計算
    Vector3 edge[3];

    edge[1] = math.Subtract(triangle.vertices[1], triangle.vertices[0]);
    edge[2] = math.Subtract(triangle.vertices[2], triangle.vertices[0]);
    Vector3 triangleNormal = math.Cross(edge[1], edge[2]);
    triangleNormal = math.Normalize(triangleNormal);

    // 線分の始点と終点の平面からの距離を計算
    float startDistance = math.Dot(triangleNormal, math.Subtract(startPoint, triangle.vertices[0]));
    float endDistance = math.Dot(triangleNormal, math.Subtract(endPoint, triangle.vertices[0]));

    // 始点と終点が平面の異なる側にある場合、線分が三角形の平面を横切っている
    if (startDistance * endDistance > 0.0f) {
        return false;
    }

    // 線分が三角形の平面を横切る場合、交点を計算
    float t = startDistance / (startDistance - endDistance);
    Vector3 intersectionPoint = math.Add(startPoint, math.Multiply(t, math.Subtract(endPoint, startPoint)));

    // 交点が三角形の内部にあるかを判定
    edge[0] = math.Subtract(triangle.vertices[1], triangle.vertices[0]);
    Vector3 edge1ToIntersection = math.Subtract(intersectionPoint, triangle.vertices[0]);
    if (math.Dot(triangleNormal, math.Cross(edge[0], edge1ToIntersection)) < 0.0f) {
        return false;
    }

    edge[1] = math.Subtract(triangle.vertices[2], triangle.vertices[1]);
    Vector3 edge2ToIntersection = math.Subtract(intersectionPoint, triangle.vertices[1]);
    if (math.Dot(triangleNormal, math.Cross(edge[1], edge2ToIntersection)) < 0.0f) {
        return false;
    }

    edge[2] = math.Subtract(triangle.vertices[0], triangle.vertices[2]);
    Vector3 edge3ToIntersection = math.Subtract(intersectionPoint, triangle.vertices[2]);
    if (math.Dot(triangleNormal, math.Cross(edge[2], edge3ToIntersection)) < 0.0f) {
        return false;
    }

    return true;
}

bool IsHit::IsCollision(const AABBData &aabb1, const AABBData &aabb2) {
    // 各軸での衝突判定
    bool xOverlap = aabb1.max.x >= aabb2.min.x && aabb1.min.x <= aabb2.max.x;
    bool yOverlap = aabb1.max.y >= aabb2.min.y && aabb1.min.y <= aabb2.max.y;
    bool zOverlap = aabb1.max.z >= aabb2.min.z && aabb1.min.z <= aabb2.max.z;

    // 全ての軸で重なっている場合、衝突している
    if (xOverlap && yOverlap && zOverlap) {
        return true;
    }

    return false;
}
