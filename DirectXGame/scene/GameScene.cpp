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

	for (uint32_t i = 0; i < 3; i++) {
		delete boss[i];
		delete bossModel[i];
		delete score[i];
	}

	delete skydome_;
	delete skydomeModel_;
	delete cameraController_;
	for (Box* box : boxes_) {
		delete box;
	}
	delete boxModel_;
	boxes_.clear();
	for (obstructionBox* box : obstructionBoxes_) {
		delete box;
	}
	/*
	for (obstructionBox* structionBox : obstructionBoxes_) {
	    delete structionBox;
	}
	*/
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
		enemyPosX = rand() % 32;
		enemyPosY = rand() % 15 + 3;
		// 生成
		Enemy* enemy_ = new Enemy();
		// 初期化
		enemy_->LoadEnemyMoveData(BossNum);
		enemy_->UpdateEnemyPopCommands(i);		
		enemy_->Initialize(enemyModel_, &viewProjection_, {mapChipField_->GetMapChipPositionByIndex(enemyPosX,enemyPosY)});
	
		enemies_.push_back(enemy_);
	}

	// ボスのモデル
	bossModel[0] = Model::CreateFromOBJ("boss", true);
	bossModel[1] = Model::CreateFromOBJ("boss2", true);
	bossModel[2] = Model::CreateFromOBJ("boss3", true);
	for (uint32_t i = 0; i < 3; i++) {
		// スコア
		score[i] = new Score();
		score[i]->Initialize();

		// ボスの生成と初期化
		boss[i] = new Boss();
		boss[i]->GetScore(score[i]);
		boss[i]->Initialize(bossModel[i], &viewProjection_,i*5);
	}
	// 天球のモデル
	skydomeModel_ = Model::CreateFromOBJ("sphere", true);
	// 天球の生成と初期化
	skydome_ = new Skydome();
	skydome_->Initialize(skydomeModel_, &viewProjection_);
	// ブロックモデル
	modelBlocks_ = Model::CreateFromOBJ("scaffold", true);
	// カメラコントローラの生成・初期化
	cameraController_ = new CameraController(); //
	cameraController_->Initialize(&viewProjection_, movableArea);
	cameraController_->SetTarget(player_);
	cameraController_->Reset();
	// 箱モデル
	boxModel_ = Model::CreateFromOBJ("hako", true);
	for (uint32_t i = 0; i < 3; ++i) {
		Box* box = new Box();
		box->Initialize(boxModel_, &viewProjection_);
		Vector3 randomPosition = GenerateRandomPosition();
		box->SetPosition(randomPosition);
		boxes_.push_back(box);
	}
	// 妨害箱
	obstructionboxModel_ = Model::CreateFromOBJ("ojama", true);

	// アイテムモデル
	// itemModel_ = Model::CreateFromOBJ("item", true);
	//  ブロックの生成
	GenerateBlocks();
}

void GameScene::ChangeScene() {
	switch (bosses) {
	case Bosses::boss01:
		if (boss[0]->IsDead()) {
			bosses = Bosses::boss02;
		}
		break;
	case Bosses::boss02:
		if (boss[1]->IsDead()) {
			bosses = Bosses::boss03;
		}
		break;
	case Bosses::boss03:
		if (boss[2]->IsDead()) {
			isFinish_ = true; // ゲームクリア
		}
		break;
	}
}

void GameScene::Update() {
	ChangeScene();
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

	switch (bosses) {
	case Bosses::boss01:
		// ボスの更新
		boss[0]->Updata();
		score[0]->Updata();
		if (boss[0]->IsDead()) {
			isDestroy[0] = true; // ボス撃破　
			BossNum = 1;
		}
		break;
	case Bosses::boss02:
		boss[1]->Updata();
		score[1]->Updata();
		kNumEnemies = 8;
		if (boss[1]->IsDead()) {
			isDestroy[1] = true; // ボス撃破　
			BossNum = 2;
		}
		break;
	case Bosses::boss03:
		boss[2]->Updata();
		score[2]->Updata();
		break;
	}

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
	// 箱の削除処理
	boxes_.erase(
	    std::remove_if(
	        boxes_.begin(), boxes_.end(),
	        [](Box* box) {
		        if (box->IsDead()) {
			        delete box;  // メモリを解放
			        return true; // 削除対象
		        }
		        return false; // 削除しない
	        }),
	    boxes_.end());
	// エネミーの処理
	for (Enemy* enemy_ : enemies_) {
		enemy_->Update();
	}

	CheckAllCollision(BossNum);

	enemies_.remove_if([](Enemy* enemy) {
		if (enemy->IsDead()) {

			delete enemy;
			return true;
		}
		return false;
	});

	if (enemies_.empty()) {
		for (uint32_t i = 0; i < kNumEnemies; i++) {
			// 生成
			enemyPosX = rand() % 32;
			enemyPosY = rand() % 15 + 3;
			Enemy* enemy_ = new Enemy();
			// 初期化
			enemy_->LoadEnemyMoveData(BossNum);
			enemy_->UpdateEnemyPopCommands(i);
			enemy_->Initialize(enemyModel_, &viewProjection_, {mapChipField_->GetMapChipPositionByIndex(enemyPosX, enemyPosY)});

			enemies_.push_back(enemy_);
		}
	}
	// 妨害箱の生成・更新
	if (obstructionBoxes_.size() >= 5) {
		return;
	}
	if (isDestroy[0]) {
		Vector3 randomPosition;
		bool positionFound = false;
		for (int i = 0; i < 5; ++i) {
			for (int attempt = 0; attempt < 10; ++attempt) {
				randomPosition = GenerateRandomPositionobBox();
				if (IsFarEnoughobBox(randomPosition)) {
					positionFound = true;
					break;
				}
			}
			if (positionFound) {
				obstructionBox* newObstructionBox = new obstructionBox();
				newObstructionBox->Initialize(obstructionboxModel_, &viewProjection_);
				newObstructionBox->SetPosition(randomPosition);
				obstructionBoxes_.push_back(newObstructionBox);
			}
		}
		isDestroy[0] = false;
	}
	for (obstructionBox* box : obstructionBoxes_) {
		box->Update();
	}
	// アイテムの更新
	/*
	if (!isItemActive_) {
	    timeSinceLastItem_ += 1.0f / 60.0f;
	    //アイテムが消えて一定時間経過後生成
	    if (timeSinceLastItem_ >= itemRespawnTime_) {
	        Vector3 randomPosition = GenerateRandomPosition();
	        //アイテムを生成
	        item_ = new Item();
	        item_->Initialize(itemModel_, &viewProjection_);
	        item_->SetPosition(randomPosition);
	        isItemActive_ = true;
	        timeSinceLastItem_ = 0.0f;
	    }
	} else {
	    item_->Update();
	}
	*/
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

	switch (bosses) {
	case Bosses::boss01:
		// ボスの描画
		boss[0]->Draw();
		break;
	case Bosses::boss02:
		// ボスの描画
		boss[1]->Draw();
		break;
	case Bosses::boss03:
		// ボスの描画
		boss[2]->Draw();
		break;
	}
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
		
	for (Box* box : boxes_) {
		box->Draw();
	}
	// 妨害箱の描画
	for (obstructionBox* box : obstructionBoxes_) {
		box->Draw();
	}
	// アイテムの描画
	/*
	if (isItemActive_ && item_ != nullptr) {
	    item_->Draw();
	}
	*/
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	switch (bosses) {
	case Bosses::boss01:
		score[0]->Draw();
		break;
	case Bosses::boss02:
		score[1]->Draw();
		break;
	case Bosses::boss03:
		score[2]->Draw();
		break;
	}

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
// 妨害箱をランダムスポーン
void GameScene::SpawnobstructionBox() {}
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
// 妨害箱同士の距離をチェック
bool GameScene::IsFarEnoughobBox(const Vector3& newPos) {
	const float kMinDistance = 3.0f;
	for (obstructionBox* box : obstructionBoxes_) {
		Vector3 boxPos = box->GetPosition();
		float dx = newPos.x - boxPos.x;
		float dy = newPos.y - boxPos.y;
		float dz = newPos.z - boxPos.z;

		float distance = sqrt(dx * dx + dy * dy + dz * dz);
		if (distance < kMinDistance) {
			return false;
		}
	}
	return true;
}
// すべての当たり判定
void GameScene::CheckAllCollision(int bossNum) {

	// 判定1と2の座標
	AABB aabb1, aabb2;
#pragma region ボスと箱の当たり判定
	{
		for (Box* box : boxes_) {
			// ボスの座標
			aabb1 = boss[bossNum]->GetAABB();
			// 箱の座標
			aabb2 = box->GetAABB();

			// ボスと箱の当たり判定

			// AABB同士の交差判定
			if (IsCollision(aabb1, aabb2)) {
				// ボスの衝突時コールバックを呼び出す
				boss[bossNum]->OnBoxCollision(box);
				// 箱の衝突時コールバックを呼び出す
				box->OnCollisionBoss();
			}
		}
	}
#pragma endregion

#pragma region ボスと敵の当たり判定
	{
		// ボス0の座標
		aabb1 = boss[bossNum]->GetAABB();

		// ボスと敵すべての当たり判定
		for (Enemy* enemy_ : enemies_) {
			// 敵の座標
			aabb2 = enemy_->GetAABB();

			// AABB同士の交差判定
			if (IsCollision(aabb1, aabb2)) {
				// ボスの衝突時コールバックを呼び出す
				boss[bossNum]->OnEnemyCollision(enemy_);

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
					enemy_->SetBoss(boss[bossNum]);
					enemy_->OnCollision();
				}
			}
		}
	}
#pragma endregion

#pragma region 箱と妨害箱の当たり判定
	{
		for (Box* box : boxes_) {
			if (box->IsDead()) {
				continue;
			}
			for (obstructionBox* structionBox : obstructionBoxes_) {
				if (structionBox == nullptr) {

					continue;
				}
				aabb1 = box->GetAABB();
				aabb2 = structionBox->GetAABB();
				if (IsCollision(aabb1, aabb2)) {
					box->OnCollisionBoss();
					break;
				}
			}
		}
	}
#pragma endregion
	/*
	    #pragma region 箱とアイテムの当たり判定
	    {
	        if (isItemActive_) {
	            aabb1 = item_->GetAABB();
	            for (Box* box : boxes_) {
	                aabb2 = box->GetAABB();
	                if (IsCollision(aabb1, aabb2)) {

	                }
	            }
	        }
	    }
	    */
	#pragma region 敵と妨害箱の当たり判定
	{
		for (Enemy* enemy : enemies_) {
			for (obstructionBox* structionBox : obstructionBoxes_) {
				aabb1 = enemy->GetAABB();
				aabb2 = structionBox->GetAABB();
				if (IsCollision(aabb1, aabb2)) {
					enemy->OnCollisionBoss();
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
// ランダムな位置を生成(妨害箱)
Vector3 GameScene::GenerateRandomPositionobBox() {
	float x = spawnRangeXMin + static_cast<float>(rand()) / RAND_MAX * (spawnRangeXMax - spawnRangeXMin);
	float y = spawnRangeYMin + static_cast<float>(rand()) / RAND_MAX * (spawnRangeYMax - spawnRangeYMin);
	float z = spawnRangeZMin + static_cast<float>(rand()) / RAND_MAX * (spawnRangeZMax - spawnRangeZMin);
	return Vector3{x, y, z};
}
