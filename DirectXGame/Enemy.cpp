#include "Enemy.h"
#include <cassert>

void Enemy::Initialize(Model* model,  ViewProjection* viewProjection) { 
	
	assert(model);

	model_ = model;
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;


}

void Enemy::Update() {


}

void Enemy::Draw() {

	model_->Draw(worldTransform_, *viewProjection_);

}
