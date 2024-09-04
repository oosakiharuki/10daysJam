#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Vector3.h"

class Boss {
public:

	void Initialize(Model* model, ViewProjection* viewProjection);

	void Updata();

	void Draw();

	Vector3 GetWorldPosition();

	AABB GetAABB();

	void IsHit();

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	ViewProjection* viewProjection_ = nullptr;

	float bossHp = 100.0f;
	bool isDamage_ = false;
	bool isHeal_ = false;
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
};