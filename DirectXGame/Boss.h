#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Vector3.h"

class Box;

class Boss {
public:

	void Initialize(Model* model, ViewProjection* viewProjection);

	void Updata();

	void Draw();

	Vector3 GetWorldPosition();

	AABB GetAABB();

	void OnBoxCollision(const Box* box);

	void IsHit();

	bool IsDead() const { return isDead_; }

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	ViewProjection* viewProjection_ = nullptr;

	float bossHp = 100.0f;
	bool hitBox_ = false;
	bool hitEnemy_ = false;
	bool hitHeal_ = false;
	bool isDead_ = false;
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
};