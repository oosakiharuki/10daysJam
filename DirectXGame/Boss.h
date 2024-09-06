#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Vector3.h"
#include "Input.h"
#include "Audio.h"

class Box;
class Enemy;

class Boss {
public:

	void Initialize(Model* model, ViewProjection* viewProjection);

	void Updata();

	void Draw();

	Vector3 GetWorldPosition();

	AABB GetAABB();

	void OnBoxCollision(const Box* box);

	void OnEnemyCollision(const Enemy* enemy);

	void IsHit();

	bool IsDead() const { return isDead_; }

	bool IsHitBox() const { return hitBox_; }

	bool IsHitEnemy() const { return hitEnemy_; }

	bool IsHitHeal() const { return hitHeal_; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t soundDataHandle_ = 0;
	float bossHp = 100.0f;
	bool hitBox_ = false;
	bool hitEnemy_ = false;
	bool hitHeal_ = false;
	bool isDead_ = false;
	static inline const float kWidth = 34.8f;
	static inline const float kHeight = 24.8f;
};