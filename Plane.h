#pragma once
#include <stdint.h>
#include <Novice.h>
#include "Vector.h"
#include "Vector3.h"
#include "Matrix4x4.h"

struct PlaneData {
	Vector3 normal;
	float distance;
};

class Plane {
public:
	void DrawPlane(const PlaneData &plane, const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, uint32_t color);

private:
	Vector vector;
};