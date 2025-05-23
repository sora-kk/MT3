#pragma once
#include <Novice.h>
#include <stdint.h>
#include <cmath>
#include <numbers>
#include "Vector.h"
#include "Vector3.h"
#include "Matrix4x4.h"

struct SphereData {
	Vector3 center;
	float radius;
};

class Sphere {
public:
	void DrawSphere(const SphereData &sphere, const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, uint32_t color);

private:
	const uint32_t kSubdivision = 16;
	float pi = std::numbers::pi_v<float>;
	const float kLonEvery = pi * 2.0f / static_cast<float>(kSubdivision);
	const float kLatEvery = pi / static_cast<float>(kSubdivision);
	Vector vector;
};