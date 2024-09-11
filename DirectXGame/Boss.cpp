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
			// audio_->PlayWave(soundDataHandle_);//エラーが起きる
			//bossHp -= 1; //何回も当たってる
			score->ScoreCounter(bossHp);
			hitBox_ = false;
		}

	} else if (hitEnemy_) {
		if (bossHp > 0) {
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