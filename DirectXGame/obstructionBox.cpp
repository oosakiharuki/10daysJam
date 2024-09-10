#include "obstructionBox.h"

void obstructionBox::Initialize(Model* model, ViewProjection* viewProjection) {
	model_ = model;
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;
}
void obstructionBox::Update() {

}
void obstructionBox::Draw() { model_->Draw(worldTransform_, *viewProjection_); }
Vector3 obstructionBox::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}
AABB obstructionBox::GetAABB() {
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}