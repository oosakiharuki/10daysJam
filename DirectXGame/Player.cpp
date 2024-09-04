#include "Player.h"

void Player::Initialize(Model* model, ViewProjection* viewProjection) {
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, 20.0f, 0.0f};
	viewProjection_ = viewProjection;
}

void Player::Update() { worldTransform_.UpdateMatrix(); }

void Player::Draw() { model_->Draw(worldTransform_, *viewProjection_); }