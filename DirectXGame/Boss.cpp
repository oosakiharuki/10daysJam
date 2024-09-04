#include "Boss.h"

void Boss::Initialize(Model* model, ViewProjection* viewProjection) { 
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_.y -= 10.0f;
}

void Boss::Updata() { 
	worldTransform_.UpdateMatrix(); 
}

void Boss::Draw() { 
	model_->Draw(worldTransform_, *viewProjection_); 
}