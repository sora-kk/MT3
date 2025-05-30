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

bool IsHit::IsCollision(const TriangleData &triangle, const Segment &segment) {
    // 線分の始点と終点
    Vector3 startPoint = segment.origin;
    Vector3 endPoint = vector.Add(segment.origin, segment.diff);

    // 三角形の法線を計算
    Vector3 edge[3];

    edge[1] = vector.Subtract(triangle.vertices[1], triangle.vertices[0]);
    edge[2] = vector.Subtract(triangle.vertices[2], triangle.vertices[0]);
    Vector3 triangleNormal = vector.Cross(edge[1], edge[2]);
    triangleNormal = vector.Normalize(triangleNormal);

    // 線分の始点と終点の平面からの距離を計算
    float startDistance = vector.Dot(triangleNormal, vector.Subtract(startPoint, triangle.vertices[0]));
    float endDistance = vector.Dot(triangleNormal, vector.Subtract(endPoint, triangle.vertices[0]));

    // 始点と終点が平面の異なる側にある場合、線分が三角形の平面を横切っている
    if (startDistance * endDistance > 0.0f) {
        return false;
    }

    // 線分が三角形の平面を横切る場合、交点を計算
    float t = startDistance / (startDistance - endDistance);
    Vector3 intersectionPoint = vector.Add(startPoint, vector.Multiply(t, vector.Subtract(endPoint, startPoint)));

    // 交点が三角形の内部にあるかを判定

    edge[0] = vector.Subtract(triangle.vertices[1], triangle.vertices[0]);
    Vector3 edge1ToIntersection = vector.Subtract(intersectionPoint, triangle.vertices[0]);
    if (vector.Dot(triangleNormal, vector.Cross(edge[0], edge1ToIntersection)) < 0.0f) {
        return false;
    }

    edge[1] = vector.Subtract(triangle.vertices[2], triangle.vertices[1]);
    Vector3 edge2ToIntersection = vector.Subtract(intersectionPoint, triangle.vertices[1]);
    if (vector.Dot(triangleNormal, vector.Cross(edge[1], edge2ToIntersection)) < 0.0f) {
        return false;
    }

    edge[2] = vector.Subtract(triangle.vertices[0], triangle.vertices[2]);
    Vector3 edge3ToIntersection = vector.Subtract(intersectionPoint, triangle.vertices[2]);
    if (vector.Dot(triangleNormal, vector.Cross(edge[2], edge3ToIntersection)) < 0.0f) {
        return false;
    }

    return true;
}
