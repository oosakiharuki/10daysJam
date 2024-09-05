#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "Enemy.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "MapChipField.h"
#include <vector>

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
	//ブロック生成
	void GenerateBlocks();

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
	//エネミー
	const uint32_t kNumEnemies = 3; //敵の数
	std::list<Enemy*> enemies_;
	Model* enemyModel_ = nullptr;
	std::stringstream enemyPopCommands;
	//ブロック
	Model* modelBlocks_ = nullptr;
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
	//マップチップフィールド
	MapChipField* mapChipField_;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};