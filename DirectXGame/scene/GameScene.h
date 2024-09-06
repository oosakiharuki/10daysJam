#pragma once

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

	// すべての当たり判定
	void CheckAllCollision();

	bool IsCollision(const AABB& aabb1, const AABB& aabb2);

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
	//エネミー
	const uint32_t kNumEnemies = 5; //敵の数
	std::list<Enemy*> enemies_;
	Model* enemyModel_ = nullptr;

	std::stringstream enemyPopCommands;

	// ボス
	Boss* boss_ = nullptr;
	Model* bossModel_ = nullptr;
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
	Rect movableArea = {12, 10, 0, 10};
    //箱
	Box* box_ = nullptr;
	Model* boxModel_ = nullptr;
	// 複数の箱を保持
	std::vector<Box*> boxes_; 
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};