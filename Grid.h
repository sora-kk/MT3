#pragma once
#include <Novice.h>
#include <stdint.h>
#include "Matrix4x4.h"
#include "Math.h"

class Grid {
public:
	void DrawGrid(const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix);

private:
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / static_cast<float>(kSubdivision);

	Math math;
};