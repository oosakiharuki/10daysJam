#include "Enemy.h"
#include <cassert>

void Enemy::Initialize(Model* model,  ViewProjection* viewProjection) { 
	
	assert(model);

	model_ = model;
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;

	Vector3 position = {10, 10, 0};	// mapchipで入れるposition;csvで変えれると思う

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