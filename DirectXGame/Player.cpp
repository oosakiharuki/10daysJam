#define NOMINMAX
#include "Player.h"
#include "Input.h"
#include "MyMath.h"
#include <algorithm>
#include <numbers>
#include <limits>

void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	viewProjection_ = viewProjection;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
}

void Player::Update(const std::vector<Box*>& boxes) {
	// 移動
	Move();
	// 旋回
	Rotate();
	bool isQKeyPressed = Input::GetInstance()->PushKey(DIK_Q);
	// 箱を持ち上げる・落とす
	if (isQKeyPressed && !wasQKeyPressed_) {
		if (!isCarryingBox_) {
			// 近くにある箱を探す
			Box* nearestBox = FindNearestBox(boxes);
			if (nearestBox != nullptr) {
				// 箱を持ち上げる
				PickOrDropBox(nearestBox);
			}
		} else {
			// 箱を投げ落とす
			PickOrDropBox(carriedBox_);
		}
	}
	wasQKeyPressed_ = isQKeyPressed;
	if (isCarryingBox_ && carriedBox_ != nullptr) {
		// 箱の位置をプレイヤーの位置に合わせる
		carriedBox_->SetPosition({worldTransform_.translation_.x, worldTransform_.translation_.y + 1.0f, worldTransform_.translation_.z});
	}
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
				turnFirstRotationY_ = worldTransform_.rotation_.y;
				turnTimer_ = kTimeTurn;
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
				turnFirstRotationY_ = worldTransform_.rotation_.y;
				turnTimer_ = kTimeTurn;
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
// 旋回
void Player::Rotate() {
	if (turnTimer_ > 0.0f) {
		turnTimer_ -= 1.0f / 60.0f;
		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};
		// 状態に応じた角度を取得する
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		float easing = 1 - turnTimer_ / kTimeTurn;
		float nowRotationY = std::lerp(turnFirstRotationY_, destinationRotationY, easing);
		// 自キャラの角度を設定する
		worldTransform_.rotation_.y = nowRotationY;
	}
}
void Player::PickOrDropBox(Box* box) {
	if (isCarryingBox_) {
		// 箱を投げ落とす
		carriedBox_->SetPosition({worldTransform_.translation_.x, worldTransform_.translation_.y - kBoxPickupHeight, worldTransform_.translation_.z});
		carriedBox_->SetFalling(true);
		isCarryingBox_ = false;
		carriedBox_ = nullptr;
	} else if (box != nullptr&&IsNearBox(box)) {
		// 箱を持ち上げる
		carriedBox_ = box;
		carriedBox_->SetPosition({worldTransform_.translation_.x, worldTransform_.translation_.y + kBoxPickupHeight, worldTransform_.translation_.z});
		isCarryingBox_ = true;
	}
}
//プレイヤーと箱の距離を計算
bool Player::IsNearBox(const Box* box) const {
	// プレイヤーと箱の距離を計算
	Vector3 playerPos = worldTransform_.translation_;
	Vector3 boxPos = box->GetPosition();
	float distance = static_cast<float>(
	    sqrt(static_cast<double>(pow(playerPos.x - boxPos.x, 2.0f)) + static_cast<double>(pow(playerPos.y - boxPos.y, 2.0f)) + static_cast<double>(pow(playerPos.z - boxPos.z, 2.0f))));

	return distance < 2.0f;
}
//一番近い箱を判定する
Box* Player::FindNearestBox(const std::vector<Box*>& boxes) {
	Box* nearestBox = nullptr;
	float nearestDistance = std::numeric_limits<float>::max();

	for (Box* box : boxes) {
		float distance = static_cast<float>(sqrt(
		    pow(worldTransform_.translation_.x - box->GetPosition().x, 2.0) + pow(worldTransform_.translation_.y - box->GetPosition().y, 2.0) +
		    pow(worldTransform_.translation_.z - box->GetPosition().z, 2.0)));

		if (distance < nearestDistance && distance < 2.0f) {
			nearestBox = box;
			nearestDistance = distance;
		}
	}


	return nearestBox;
}
