#pragma once
#include "Vector.h"
#include "Sphere.h"
#include "Plane.h"
#include "Line.h"
#include "Triangle.h"

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

private:
	Vector vector;
};
