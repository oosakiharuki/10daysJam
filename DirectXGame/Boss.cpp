#include "Boss.h"
#include "Score.h"
#define _USE_MATH_DEFINES
#include<math.h>

void Boss::Initialize(Model* model, ViewProjection* viewProjection) { 
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	soundDataHandle_ = audio_->LoadWave("HitSE.wav");
	worldTransform_.translation_ = {
	    15.0f,
	    -8.0f,
	   0.0,
	};

	initialPositionX_ = worldTransform_.translation_.x;
	bossHp = 40;
}

void Boss::Updata() { 
	// ボスの移動処理
	worldTransform_.translation_.x += moveSpeed_ * moveDirection_;

	// 一定範囲を超えたら移動方向を反転
	if (std::abs(worldTransform_.translation_.x - initialPositionX_) > moveRange_) {
		moveDirection_ *= -1; // 移動方向を反転
	}
    
    // HIT時の回転処理
	if (isRotating_) {
		rotationTimer_ -= 1.0f / 60.0f;                              // タイマーを減らす
		rotationAngle_ = sinf(rotationTimer_ * float(M_PI) * 4.0f) * 10.0f; // 上下に揺れる

		worldTransform_.rotation_.z = rotationAngle_ * (float(M_PI) / 180.0f); // 回転角度をラジアンに変換して適用

		if (rotationTimer_ <= 0.0f) {
			isRotating_ = false;                // 回転を終了
			worldTransform_.rotation_.z = 0.0f; // 回転をリセット
		}
	}

	IsHit();

	if (bossHp <= 0) {
		isDead_ = true;
	}
	worldTransform_.UpdateMatrix(); 
}

void Boss::Draw() { 
    model_->Draw(worldTransform_, *viewProjection_); 
}

Vector3 Boss::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

AABB Boss::GetAABB() {
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}

void Boss::OnBoxCollision(const Box* box) { 
	(void)box; 
	hitBox_ = true;
}

 void Boss::OnEnemyCollision(const Enemy* enemy) {
	(void)enemy;
	hitEnemy_ = true;
}

void Boss::IsHit() {
	if (hitBox_) {
		if (bossHp > 0) {
			// HITしたら回転を開始
			isRotating_ = true;
			rotationTimer_ = rotationDuration_;  
			// audio_->PlayWave(soundDataHandle_);//エラーが起きる
			bossHp -= 1; //何回も当たってる
			score->ScoreCounter(bossHp);
			hitBox_ = false;
		}

	} else if (hitEnemy_) {
		if (bossHp > 0) {
			// HITしたら回転を開始
			isRotating_ = true;
			rotationTimer_ = rotationDuration_;  
			// audio_->PlayWave(soundDataHandle_);//ココも
			bossHp -= 1 * enemyCounter_;
			score->ScoreCounter(bossHp);
			enemyCounter_ = 1;
			hitEnemy_ = false;
		}

	} /* else if (hitHeal_) {
		if (bossHp < 100) {
			bossHp += 5;
		}
		hitHeal_ = false;
	}*/
	else
	{
		score->NowHp(bossHp);
	}
	
}

void Boss::EnemyCounter() { enemyCounter_ *= 2; }