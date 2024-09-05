#include "Enemy.h"
#include <cassert>

void Enemy::Initialize(Model* model, ViewProjection* viewProjection, Vector3 position, float speed, float range) { 
	
	assert(model);

	model_ = model;
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;

	worldTransform_.translation_ = position;

	move = position;

	kLoad = speed;
	kRange = range;
}

void Enemy::Update() {

	worldTransform_.UpdateMatrix();

	kSpeed += kLoad; // 速度

	worldTransform_.translation_.x = move.x + std::sin(kSpeed) * kRange;

}

void Enemy::Draw() {

	model_->Draw(worldTransform_, *viewProjection_);

}