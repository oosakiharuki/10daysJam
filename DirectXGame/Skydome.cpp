#include "Skydome.h"

void Skydome::Initialize(Model* model, ViewProjection* viewProjection) {
	worldTransform_.Initialize();
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.translation_ = {0.0f, 0.0f, 100.0f};
}

void Skydome::Update() { worldTransform_.UpdateMatrix(); }

void Skydome::Draw() { model_->Draw(worldTransform_, *viewProjection_); }