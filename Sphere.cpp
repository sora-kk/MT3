#include "Sphere.h"

bool Sphere::IsCollision(const SphereData &s1, const SphereData &s2) {
    float distance = vector.Length(vector.Subtract(s2.center, s1.center));

	if (distance <= s1.radius + s2.radius) {
		return true;
	} else {
		return false;
	}
}

void Sphere::DrawSphere(const SphereData &sphere, const Matrix4x4 &viewProjectionMatrix, const Matrix4x4 &viewportMatrix, uint32_t color) {
	for (uint32_t latIndex = 0; latIndex < kSubdivision; latIndex++) {
		float lat = -pi / 2.0f + kLatEvery * latIndex;
		float latDistance = pi / kSubdivision;
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; lonIndex++) {
			float lon = lonIndex * kLonEvery;
			float lonDistance = 2 * pi / kSubdivision;
			Vector3 a{
				sphere.center.x + sphere.radius * cos(lat) * cos(lon),
				sphere.center.y + sphere.radius * sin(lat),
				sphere.center.z + sphere.radius * cos(lat) * sin(lon)
			};
			Vector3 b{
				sphere.center.x + sphere.radius * cos(lat + latDistance) * cos(lon),
				sphere.center.y + sphere.radius * sin(lat + latDistance),
				sphere.center.z + sphere.radius * cos(lat + latDistance) * sin(lon)
			};
			Vector3 c{
				sphere.center.x + sphere.radius * cos(lat) * cos(lon + lonDistance),
				sphere.center.y + sphere.radius * sin(lat),
				sphere.center.z + sphere.radius * cos(lat) * sin(lon + lonDistance)
			};

			// スクリーン座標系まで変換
			Vector3 screenA = vector.Transform(vector.Transform(a, viewProjectionMatrix), viewportMatrix);
			Vector3 screenB = vector.Transform(vector.Transform(b, viewProjectionMatrix), viewportMatrix);
			Vector3 screenC = vector.Transform(vector.Transform(c, viewProjectionMatrix), viewportMatrix);

			// ab,bcで線を引く
			Novice::DrawLine(static_cast<int>(screenA.x), static_cast<int>(screenA.y), static_cast<int>(screenB.x), static_cast<int>(screenB.y), color);
			Novice::DrawLine(static_cast<int>(screenA.x), static_cast<int>(screenA.y), static_cast<int>(screenC.x), static_cast<int>(screenC.y), color);
		}
	}
}
