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

