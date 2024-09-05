#include "Player.h"
#include "Input.h"
#include "MyMath.h"
#include <algorithm>
#include <numbers>

void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	viewProjection_ = viewProjection;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
}

void Player::Update() { 
	//移動
	Move();
	//旋回
	Rotate();
}

void Player::Draw() { model_->Draw(worldTransform_, *viewProjection_); }
// 移動
void Player::Move() {
	// 移動入力
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
		// 左右加速
		Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
			// 速度と逆方向にブレーキ
			if (velocity_.x < 0.0f) {
				velocity_.x *= (1.0f - kAttenuation);
			}
			acceleration.x += kAcceleration;
			// 左右切り替え
			if (lrDirection_ != LRDirection::kRight) {
				lrDirection_ = LRDirection::kRight;
			}
		} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
			// 速度と逆方向にブレーキ
			if (velocity_.x > 0.0f) {
				velocity_.x *= (1.0f - kAttenuation);
			}
			acceleration.x -= kAcceleration;
			// 左右切り替え
			if (lrDirection_ != LRDirection::kLeft) {
				lrDirection_ = LRDirection::kLeft;
			}
		}
		// 加減速
		velocity_ += acceleration;
		// 最大速度制限
		velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
	} else {
		// 非入力時には移動減衰をかける
		velocity_.x *= (1.0f - kAttenuation);
	}
	// 移動
	worldTransform_.translation_.x += velocity_.x;
	// 行列計算
	worldTransform_.UpdateMatrix();
}
//旋回
void Player::Rotate() { float destinationRotationYTable[] = {
	std::numbers::pi_v<float> / 2.0f,
	std::numbers::pi_v<float> * 3.0f / 2.0f};
//状態に応じた角度を取得
	float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
	//自キャラの角度を設定する
	worldTransform_.rotation_.y = destinationRotationY;
}