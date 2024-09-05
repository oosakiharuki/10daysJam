#include "Boss.h"

void Boss::Initialize(Model* model, ViewProjection* viewProjection) { 
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_.y -= 25.0f;
}

void Boss::Updata() { 

	IsHit();

	if (bossHp <= 0) {
		isDead_ = true;
	}
	worldTransform_.UpdateMatrix(); 
}

void Boss::Draw() { 
	model_->Draw(worldTransform_, *viewProjection_); 
}

Vector3 Boss::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

AABB Boss::GetAABB() {
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}

void Boss::OnBoxCollision(const Box* box) { 
	(void)box; 
	hitBox_ = true;
}

 void Boss::OnEnemyCollision(const Enemy* enemy) {
	(void)enemy;
	hitEnemy_ = true;
}

void Boss::IsHit() {
	if (hitBox_) {
		if (bossHp >= 0) {
			bossHp -= 2;
		}
		hitBox_ = false;
	} else if (hitEnemy_) {
		if (bossHp >= 0) {
			bossHp -= 5;
		}
		hitEnemy_ = false;
	} else if (hitHeal_) {
		if (bossHp < 100) {
			bossHp += 5;
		}
		hitHeal_ = false;
	}
}