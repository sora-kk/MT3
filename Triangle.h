#pragma once
#include <Novice.h>
#include <stdint.h>
#include "Vector.h"
#include "Vector3.h"
#include "Matrix4x4.h"

struct TriangleData {
	Vector3 vertices[3];
};

class Triangle {
public:
	void DrawTriangle(const TriangleData &triangle, const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, uint32_t color);

private:
	Vector vector;
};