#pragma once
#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "Box.h"
#include "Enemy.h"
#include "Boss.h"
#include "Skydome.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "MapChipField.h"
#include "CameraController.h"
#include "Box.h"
#include <vector>
#include "Score.h"
#include "obstructionBox.h"
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

	//妨害箱のスポーン
	void SpawnobstructionBox();

	bool IsCollision(const AABB& aabb1, const AABB& aabb2);
	// 距離をチェック
	bool IsFarEnough(const Vector3& newPos);
	// ランダムな位置を生成
	Vector3 GenerateRandomPosition();
	//ランダムな位置を生成(妨害箱)
	Vector3 GenerateRandomPositionobBox();

	enum class Bosses { boss01, boss02,boss03 };

	void ChangeScene();


	// ゲームクリア
	bool IsNextScene() { return isFinish_; }

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
	Box* box_ = nullptr;
	Model* boxModel_ = nullptr;
	// エネミー
	uint32_t enemyPosX;
	uint32_t enemyPosY;

	const uint32_t kNumEnemies = 10; // 敵の数
	std::list<Enemy*> enemies_;
	Model* enemyModel_ = nullptr;

	std::stringstream enemyPopCommands;

	// ボス
	Bosses bosses = Bosses::boss01;
	Boss* boss[3] = {nullptr, nullptr,nullptr};
	Model* bossModel[3] = {nullptr, nullptr, nullptr};
	int BossNum = 0;
	//ブロック
	Model* modelBlocks_ = nullptr;
	// 天球
	Skydome* skydome_ = nullptr;
	Model* skydomeModel_ = nullptr;
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
	//マップチップフィールド
	MapChipField* mapChipField_;
	//カメラコントローラー
	CameraController* cameraController_ = nullptr;
	Rect movableArea = {12, 15, 0, 10};
	// 複数の箱を保持
	std::vector<Box*> boxes_; 
	 // 最後の箱生成からの経過時間
	float timeSinceLastBox_ = 0.0f; 
	// 箱生成間隔
	const float kBoxSpawnInterval = 5.0f; 

	const float kBoxSpawnMinX = 0.0f; 
	const float kBoxSpawnMaxX = 31.0f;
	const float kBoxSpawnMinY = 19.5f;
	const float kBoxSpawnMaxY = 19.5f;  
	const float kBoxSpawnMinZ = 0.0f; 
	const float kBoxSpawnMaxZ = 0.0f;  

	Score* score[3] = {nullptr, nullptr, nullptr};

	bool isDestroy[2] = {false, false};
	bool isFinish_ = false;

	//妨害箱
	Model* obstructionboxModel_ = nullptr;
	std::vector<obstructionBox*> obstructionBoxes_;
	//スポーン範囲
	float spawnRangeXMin = -10.0f;
	float spawnRangeXMax = 10.0f;
	float spawnRangeYMin = 0.0f;
	float spawnRangeYMax = 10.0f;
	float spawnRangeZMin = 0.0f;
	float spawnRangeZMax = 0.0f;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};

#endif // GAMESCENE_H