#pragma once
#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Audio.h"
#include "Boss.h"
#include "Box.h"
#include "CameraController.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "Input.h"
#include "Item.h"
#include "MapChipField.h"
#include "Model.h"
#include "Player.h"
#include "Score.h"
#include "Skydome.h"
#include "Sprite.h"
#include "TimeLimit.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "obstructionBox.h"
#include <vector>
#include "Item.h"
#include "TimeLimit.h"
#include "DeathParticles.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	// ブロック生成
	void GenerateBlocks();
	// すべての当たり判定
	void CheckAllCollision(int bossNum);

	bool IsCollision(const AABB& aabb1, const AABB& aabb2);
	// 距離をチェック
	bool IsFarEnough(const Vector3& newPos);
	bool IsFarEnoughobBox(const Vector3& newPos);
	// ランダムな位置を生成
	Vector3 GenerateRandomPosition();
	// ランダムな位置を生成(妨害箱)
	Vector3 GenerateRandomPositionobBox();

	// アイテムで敵が止まる
	void IsStopEnemy();

	//当たった時のパーテイクル
	void ParticleBorn(Vector3 position);
	//ボスの数
	enum class Bosses { boss01, boss02,boss03 };
	//シーンチェンジ
	void ChangeScene();
	// ゲームクリア
	bool IsClearScene() { return isFinishClear_; }
	// ゲームオーバー
	bool IsGameOverScene() { return isFinishOver_; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	// デバックカメラ有効
	bool isDebugCameraActive_ = false;
	// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;
	// プレイヤー
	Player* player_ = nullptr;
	Model* playermodel_ = nullptr;
	// 箱
	// Box* box_ = nullptr;
	Model* boxModel_ = nullptr;
	// エネミー
	uint32_t enemyPosX;
	uint32_t enemyPosY;

	uint32_t kNumEnemies = 10; // 敵の数
	std::list<Enemy*> enemies_;
	Model* enemyModel_ = nullptr;

	std::stringstream enemyPopCommands;
	// ボス
	Bosses bosses = Bosses::boss01;
	Boss* boss[3] = {nullptr, nullptr, nullptr};
	Model* bossModel[3] = {nullptr, nullptr, nullptr};
	int BossNum = 0;
	// ブロック
	Model* modelBlocks_ = nullptr;
	// 天球
	Skydome* skydome_ = nullptr;
	Model* skydomeModel_ = nullptr;
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
	// マップチップフィールド
	MapChipField* mapChipField_;
	// カメラコントローラー
	CameraController* cameraController_ = nullptr;
	Rect movableArea = {12, 15, 0, 10};
	// 複数の箱を保持
	std::vector<Box*> boxes_;
	// 最後の箱生成からの経過時間
	float timeSinceLastBox_ = 0.0f;
	// 箱生成間隔
	const float kBoxSpawnInterval = 3.0f;

	const float kBoxSpawnMinX = 0.0f;
	const float kBoxSpawnMaxX = 31.0f;
	const float kBoxSpawnMinY = 19.5f;
	const float kBoxSpawnMaxY = 19.5f;
	const float kBoxSpawnMinZ = 0.0f;
	const float kBoxSpawnMaxZ = 0.0f;

	Score* score[3] = {nullptr, nullptr, nullptr};

	bool isDestroy[2] = {false, false};

	bool isFinishClear_ = false;
	bool isFinishOver_ = false;

	// 妨害箱

	Model* obstructionboxModel_ = nullptr;
	std::vector<obstructionBox*> obstructionBoxes_;
	// スポーン範囲
	float spawnRangeXMin = 0.0f;
	float spawnRangeXMax = 31.0f;
	float spawnRangeYMin = 1.0f;
	float spawnRangeYMax = 15.0f;
	float spawnRangeZMin = 0.0f;
	float spawnRangeZMax = 0.0f;
	// 妨害箱の生成間隔
	const float kObBoxSpawnInterval = 5.0f;
	float timeSinceLastObBoxSpawn_ = 0.0f;
	// アイテム
	Model* itemModel_ = nullptr;
	Item* item_ = nullptr;
	bool isItemActive_ = false;
	// 最後にアイテムが使われてからの時間
	float timeSinceLastItem_ = 0.0f;
	const float itemRespawnTime_ = 20.0f;
	// アイテムの止める時間
	bool isStopEnemy_ = false;
	float timerCount = 5.0f;
	float deltaTimer_ = 1.0f / 60.0f;

	TimeLimit* timeLimit_ = nullptr;

	std::list<DeathParticles*> deathParticles_;
	Model* particleModel_ = nullptr;

	uint32_t soundDataHandle_ = 0;
	uint32_t voiceHandele_ = 0;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
#endif // GAMESCENE_H