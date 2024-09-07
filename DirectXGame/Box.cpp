#include "Box.h"

void Box::Initialize(Model* model, ViewProjection* viewProjection) { 
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {10,20,0};
	viewProjection_ = viewProjection;
}

void Box::Update() {
	if (isFalling_) {
		fallSpeed_ += kGravity;
		worldTransform_.translation_.y -= fallSpeed_;
	}
	worldTransform_.UpdateMatrix();
}

void Box::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

Vector3 Box::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

AABB Box::GetAABB() {
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}


void Box::OnCollisionBoss() { isDead_ = true; }