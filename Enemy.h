#pragma once
#include "Actor.h"

class Enemy : public Actor {
public:
	/// <summary>
	/// 更新処理の仮想関数
	/// </summary>
	virtual void Update() = 0;
};
