#include "Enemy.h"
#include <cassert>

void Enemy::Initialize(Model* model, ViewProjection* viewProjection, Vector3 position) { 
	
	assert(model);

	model_ = model;
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;

	worldTransform_.translation_ = position;

	move = position;
}

void Enemy::Update() {

	worldTransform_.UpdateMatrix();

	speed += 1.0f / 60.0f; //速度

	worldTransform_.translation_.x = move.x + std::sin(speed) * range;

}

void Enemy::Draw() {

	model_->Draw(worldTransform_, *viewProjection_);

}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

AABB Enemy::GetAABB() {
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}