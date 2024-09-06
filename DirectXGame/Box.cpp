#include "Box.h"

void Box::Initialize(Model* model, ViewProjection* viewProjection) { 
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {};
	viewProjection_ = viewProjection;
}

void Box::Update() {

}

void Box::Draw() { model_->Draw(worldTransform_, *viewProjection_); }
