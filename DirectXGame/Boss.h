#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Vector3.h"
#include "Input.h"
#include "Audio.h"

class Box;
class Enemy;
class Score;

class Boss {
public:
	void Initialize(Model* model, ViewProjection* viewProjection, uint32_t additionalHp);
	void Updata();
	void Draw();

	Vector3 GetWorldPosition();
	AABB GetAABB();
	void OnBoxCollision(const Box* box);
	void OnEnemyCollision(const Enemy* enemy);

	// 衝突時にスコアの加算
	void IsHit();

	//スコアのgetter
	//float GetScore() const { return score_; }
	void GetScore(Score* score_) { score = score_; }
	void EnemyCounter();
	void CounterReset();

	bool IsDead() const { return isDead_; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t soundDataHandle_ = 0;
	int bossHp;
	bool hitBox_ = false;
	bool hitEnemy_ = false;
	bool hitHeal_ = false;
	bool isDead_ = false;
	static inline const float kWidth = 34.8f;
	static inline const float kHeight = 8.8f;
	int scorePoint_ = 0;

	Score* score = nullptr;

	uint32_t enemyCounter_ = 1;

	float moveSpeed_ = 0.05f; // 移動速度
	float moveRange_ = 5.0f; // 移動範囲
	int moveDirection_ = 1;   // 1: 右移動, -1: 左移動
	float initialPositionX_;  // 初期位置のX座標

    float rotationAngle_ = 0.0f;    // 現在の回転角度
	float rotationSpeed_ = 0.1f;    // 回転速度
	float rotationDuration_ = 0.5f; // 回転時間（HIT後どれくらい揺れるか）
	float rotationTimer_ = 0.0f;    // 回転アニメーションのためのタイマー
	bool isRotating_ = false;       // 回転アニメーションが有効かどうか
	//増えるHP
	uint32_t additionalHp;
};