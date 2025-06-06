#pragma once
#include "Math.h"
#include "Sphere.h"
#include "Plane.h"
#include "Line.h"
#include "Triangle.h"
#include "AABB.h"

class IsHit {
public:
	// 球と球
	bool IsCollision(const SphereData &sphere1, const SphereData &sphere2);

	// 球と平面
	bool IsCollision(const SphereData &sphere, const PlaneData &plane);

	// 線と平面
	bool IsCollision(const Segment &segment, const PlaneData &plane);

	// 三角形と線
	bool IsCollision(const TriangleData &triangle, const Segment &segment);

	// AABBとAABB
	bool IsCollision(const AABBData &aabb1, const AABBData &aabb2);

	// AABBと球
	bool IsCollision(const AABBData &aabb, const SphereData &sphere);

private:
	Math math;
};
