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
#include "Score.h"
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
	//距離をチェック
	bool IsFarEnough(const Vector3& newPos);
	//ランダムな位置を生成
	Vector3 GenerateRandomPosition();

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
	uint32_t enemyPosX;
	uint32_t enemyPosY;

	const uint32_t kNumEnemies = 10; //敵の数
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
	Score* score = nullptr;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};