#include "EnemyA.h"

// コンストラクタ
EnemyA::EnemyA(int isAlive, const Vector2 &pos, const Vector2 &velocity, const Vector2 &radius, unsigned int color) {
	isAlive_ = isAlive;
	pos_ = pos;
	velocity_ = velocity;
	radius_ = radius;
	color_ = color;
}

// 更新処理
void EnemyA::Update() {
	pos_.x += velocity_.x;
	if (pos_.x <= radius_.x || pos_.x >= 1280.0f - radius_.x) {
		velocity_.x *= -1.0f;
	}
}
