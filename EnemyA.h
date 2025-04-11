#pragma once
#include "Enemy.h"

class EnemyA : public Enemy {
public:
	/// <summary>
	/// EnemyAのコンストラクタ
	/// </summary>
	/// <param name="isAlive"> 生存フラグ </param>
	/// <param name="pos"> 初期座標 </param>
	/// <param name="velocity"> 速度 </param>
	/// <param name="radius"> 半径 </param>
	/// <param name="color"> 矩形の色 </param>
	EnemyA(int isAlive, const Vector2 &pos, const Vector2 &velocity, const Vector2 &radius, unsigned int color);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
};
