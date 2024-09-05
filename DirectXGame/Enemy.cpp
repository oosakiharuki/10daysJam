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