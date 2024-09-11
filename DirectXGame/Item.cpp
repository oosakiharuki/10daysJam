#include "Item.h"

void Item::Initialize(Model* model, ViewProjection* viewProjection) {
	model_ = model;
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;
}
void Item::Update() {
	worldTransform_.UpdateMatrix();
}
void Item::Draw() { model_->Draw(worldTransform_, *viewProjection_); }

Vector3 Item::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

AABB Item::GetAABB() {
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}