#include "Boss.h"

void Boss::Initialize(Model* model, ViewProjection* viewProjection) { 
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_.y -= 10.0f;
}

void Boss::Updata() { 
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

void Boss::IsHit() {
	if (isDamage_) {
		if (bossHp >= 0) {
			bossHp -= 5;
		}
		isDamage_ = false;
	} else if (isHeal_) {
		if (bossHp <= 100) {
			bossHp += 5;
		}
		isHeal_ = false;
	}
}