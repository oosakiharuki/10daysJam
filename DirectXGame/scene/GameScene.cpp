#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <cstdlib>
#include <ctime>

GameScene::GameScene() {
	// ランダムシードを初期化
	srand(static_cast<unsigned int>(time(nullptr)));
}

GameScene::~GameScene() {
	delete player_;
	delete playermodel_;
	delete modelBlocks_;
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();
	delete debugCamera_;

	delete enemyModel_;
	for (Enemy* enemy_ : enemies_) {
		delete enemy_;
	}
	delete mapChipField_;
	delete boss_;
	delete bossModel_;
	delete skydome_;
	delete skydomeModel_;
	delete cameraController_;
	for (Box* box : boxes_) {
		delete box;
	}
	delete boxModel_;
	boxes_.clear();
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	viewProjection_.Initialize();
	worldTransform_.Initialize();
	// デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	// マップチップフィールドの生成
	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/map.csv");
	// プレイヤーモデル
	playermodel_ = Model::CreateFromOBJ("player", true);
	// プレイヤーの生成
	player_ = new Player();
	// 座標指定
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(6, 0);
	// プレイヤーの初期化
	player_->Initialize(playermodel_, &viewProjection_, playerPosition);
	// エネミー
	// モデル
	enemyModel_ = Model::CreateFromOBJ("enemy", true);
	for (uint32_t i = 0; i < kNumEnemies; i++) {
		// 生成
		Enemy* enemy_ = new Enemy();
		// 初期化
		enemy_->LoadEnemyMoveData();
		enemy_->UpdateEnemyPopCommands(i);
		enemy_->Initialize(enemyModel_, &viewProjection_, {15, 14.0f - (i * 5.0f), 0});

		enemies_.push_back(enemy_);
	}
	// ボスのモデル
	bossModel_ = Model::CreateFromOBJ("boss", true);
	// ボスの生成と初期化
	boss_ = new Boss();
	boss_->Initialize(bossModel_, &viewProjection_);
	// 天球のモデル
	skydomeModel_ = Model::CreateFromOBJ("sphere", true);
	// 天球の生成と初期化
	skydome_ = new Skydome();
	skydome_->Initialize(skydomeModel_, &viewProjection_);
	// ブロックモデル
	modelBlocks_ = Model::CreateFromOBJ("block", true);
	// カメラコントローラの生成・初期化
	cameraController_ = new CameraController();
	cameraController_->Initialize(&viewProjection_, movableArea);
	cameraController_->SetTarget(player_);
	cameraController_->Reset();
	// 箱モデル
	boxModel_ = Model::CreateFromOBJ("cube", true);
	for (uint32_t i = 0; i < 3; ++i) {
		Box* box = new Box();
		box->Initialize(boxModel_, &viewProjection_);
		Vector3 randomPosition = GenerateRandomPosition();
		box->SetPosition(randomPosition);
		boxes_.push_back(box);
	}

	// ブロックの生成
	GenerateBlocks();
}

void GameScene::Update() {
	// 天球の更新
	skydome_->Update();
	// ブロックの更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			// アフィン変換行列の作成
			worldTransformBlock->UpdateMatrix();
		}
	}
	// プレイヤーの更新
	player_->Update(boxes_);
	// ボスの更新
	boss_->Updata();
	// カメラコントローラーの更新
	cameraController_->Update();
	// 箱の生成間隔
	timeSinceLastBox_ += 1.0f / 60.0f;

	if (timeSinceLastBox_ >= kBoxSpawnInterval) {
		Vector3 randomPosition;
		bool positionFound = false;

		// 一定回数試行してランダムな位置を生成
		for (int i = 0; i < 10; ++i) {
			randomPosition = GenerateRandomPosition();
			if (IsFarEnough(randomPosition)) {
				positionFound = true;
				break;
			}
		}

		// 適切な位置が見つかった場合のみ箱を生成
		if (positionFound) {
			Box* newBox = new Box();
			newBox->Initialize(boxModel_, &viewProjection_);
			newBox->SetPosition(randomPosition);
			boxes_.push_back(newBox);
			timeSinceLastBox_ = 0.0f;
		}
	}

	// 箱の更新
	for (Box* box : boxes_) {
		box->Update();
	}
	// デバックカメラの更新
	debugCamera_->Update();
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		if (isDebugCameraActive_ == false) {
			isDebugCameraActive_ = true;
		} else {
			isDebugCameraActive_ = false;
		}
	}
#endif
	// カメラの処理

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}
	// エネミーの処理
	for (Enemy* enemy_ : enemies_) {
		enemy_->Update();
	}
	CheckAllCollision();

	enemies_.remove_if([](Enemy* enemy) {
		if (enemy->IsDead()) {

			delete enemy;
			return true;
		}
		return false;
	});
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);
	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	// 天球の描画
	skydome_->Draw();
	// ブロックの描画
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			modelBlocks_->Draw(*worldTransformBlock, viewProjection_);
		}
	}
	// プレイヤーの描画
	player_->Draw();
	// エネミーの描画
	for (Enemy* enemy_ : enemies_) {
		enemy_->Draw();
	}

	// ボスの描画
	boss_->Draw();
	for (Box* box : boxes_) {
		box->Draw();
	}
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

// ブロックの生成
void GameScene::GenerateBlocks() {
	// 要素数
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();
	// 要素数を変更する
	// 列数を設定(縦方向のブロック数)
	worldTransformBlocks_.resize(20);
	for (uint32_t i = 0; i < 20; ++i) {
		// 一列の要素数を設定(横ブロック数)
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}
	// ブロックの生成
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}

bool GameScene::IsCollision(const AABB& aabb1, const AABB& aabb2) {
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) && (aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) && (aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)) {
		return true;
	}
	return false;
}
// 距離をチェック
bool GameScene::IsFarEnough(const Vector3& newPos) {
	const float kMinDistance = 2.0f; // 箱同士の最小距離

	for (Box* box : boxes_) {
		Vector3 boxPos = box->GetPosition();
		float dx = newPos.x - boxPos.x;
		float dy = newPos.y - boxPos.y;
		float dz = newPos.z - boxPos.z;

		// float型で計算するためのキャスト
		float distance = sqrt(dx * dx + dy * dy + dz * dz);

		if (distance < kMinDistance) {
			return false;
		}
	}
	return true;
}

// すべての当たり判定
void GameScene::CheckAllCollision() {

	// 判定1と2の座標
	AABB aabb1, aabb2;
#pragma region ボスと箱の当たり判定
	{
		for (Box* box : boxes_) {
			// ボスの座標
			aabb1 = boss_->GetAABB();
			// 箱の座標
			aabb2 = box->GetAABB();

			// ボスと箱の当たり判定

			// AABB同士の交差判定
			if (IsCollision(aabb1, aabb2)) {
				// ボスの衝突時コールバックを呼び出す
				boss_->OnBoxCollision(box);
				// 箱の衝突時コールバックを呼び出す
				box->OnCollisionBoss();
			}
		}
	}
#pragma endregion

#pragma region ボスと敵の当たり判定
	{
		// ボスの座標
		aabb1 = boss_->GetAABB();

		// ボスと敵すべての当たり判定
		for (Enemy* enemy_ : enemies_) {
			// 敵の座標
			aabb2 = enemy_->GetAABB();

			// AABB同士の交差判定
			if (IsCollision(aabb1, aabb2)) {
				// ボスの衝突時コールバックを呼び出す
				boss_->OnEnemyCollision(enemy_);

				enemy_->OnCollisionBoss();
			}
		}
	}
#pragma endregion

#pragma region 敵とはこの当たり判定
	{
		for (Box* box : boxes_) {
			for (Enemy* enemy_ : enemies_) {

				aabb1 = box->GetAABB();
				aabb2 = enemy_->GetAABB();

				if (IsCollision(aabb1, aabb2)) {
					enemy_->SetBox(box);
					enemy_->OnCollision();
				}
			}
		}
	}
#pragma endregion
}
// ランダムな位置を生成
Vector3 GameScene::GenerateRandomPosition() {
	float x = kBoxSpawnMinX + static_cast<float>(rand()) / RAND_MAX * (kBoxSpawnMaxX - kBoxSpawnMinX);
	float y = kBoxSpawnMinY + static_cast<float>(rand()) / RAND_MAX * (kBoxSpawnMaxY - kBoxSpawnMinY);
	float z = kBoxSpawnMinZ + static_cast<float>(rand()) / RAND_MAX * (kBoxSpawnMaxZ - kBoxSpawnMinZ);
	return Vector3{x, y, z};
}
