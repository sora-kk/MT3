#pragma once
#include "Vector.h"
#include "Sphere.h"
#include "Plane.h"
#include "Line.h"

class IsHit {
public:
	bool IsCollision(const SphereData &sphere1, const SphereData &sphere2);

	bool IsCollision(const SphereData &sphere, const PlaneData &plane);

	bool IsCollision(const Segment &segment, const PlaneData &plane);

private:
	Vector vector;
};
