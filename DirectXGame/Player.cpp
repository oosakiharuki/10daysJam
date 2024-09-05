#include "Player.h"
#include "Input.h"
#include "MyMath.h"
#include <numbers>

void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	viewProjection_ = viewProjection;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
}

void Player::Update() { 
	Move();
	 }

void Player::Draw() { model_->Draw(worldTransform_, *viewProjection_); }
// 移動
void Player::Move() {
	// 移動入力
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
		// 左右加速
		Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
			acceleration.x += kAcceleration;
		} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
			acceleration.x -= kAcceleration;
		}
		//加減速
		velocity_ += acceleration;
	}
	// 移動
	worldTransform_.translation_.x += velocity_.x;
	// 行列計算
	worldTransform_.UpdateMatrix();
}