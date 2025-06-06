#pragma once
#include <stdint.h>
#include <Novice.h>
#include "Math.h"
#include "Vector3.h"
#include "Matrix4x4.h"

struct AABBData {
	Vector3 min;
	Vector3 max;
};

class AABB {
public:
	void DrawAABB(const AABBData &aabb, const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, uint32_t color);

private:
	Math math;
};