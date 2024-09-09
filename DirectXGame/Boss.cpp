#include "Boss.h"
#include "Score.h"

void Boss::Initialize(Model* model, ViewProjection* viewProjection) { 
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	soundDataHandle_ = audio_->LoadWave("HitSE.wav");
	worldTransform_.translation_ = {
	    10.0f,
	    -8.5f,
	   0.0,
	};

	initialPositionX_ = worldTransform_.translation_.x;
}

void Boss::Updata() { 
	// ボスの移動処理
	worldTransform_.translation_.x += moveSpeed_ * moveDirection_;

	// 一定範囲を超えたら移動方向を反転
	if (std::abs(worldTransform_.translation_.x - initialPositionX_) > moveRange_) {
		moveDirection_ *= -1; // 移動方向を反転
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
		/*if (bossHp > 0) {
			bossHp -= 2;

		}*/ 
		//audio_->PlayWave(soundDataHandle_);//エラーが起きる
		//scorePoint_ += 2; //何回も当たってる
		score->ScoreCounter(scorePoint_);
		hitBox_ = false;
	} else if (hitEnemy_) {
		/*if (bossHp > 0) {
			bossHp -= 5;

		}*/ 
    	//audio_->PlayWave(soundDataHandle_);//ココも
		scorePoint_ += 1 * enemyCounter_;
		score->ScoreCounter(scorePoint_);
		enemyCounter_ = 1;
		hitEnemy_ = false;
	} /* else if (hitHeal_) {
		if (bossHp < 100) {
			bossHp += 5;
		}
		hitHeal_ = false;
	}*/

	
}

void Boss::EnemyCounter() { enemyCounter_ *= 2; }