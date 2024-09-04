#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete player_;
	delete playermodel_;
	delete boss_;
	delete bossModel_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	viewProjection_.Initialize();
	worldTransform_.Initialize();
	// プレイヤーモデル
	playermodel_ = Model::CreateFromOBJ("player", true);
	// プレイヤーの生成
	player_ = new Player();
	// プレイヤーの初期化
	player_->Initialize(playermodel_, &viewProjection_);
	// ボスのモデル
	bossModel_ = Model::CreateFromOBJ("boss", true);
	// ボスの生成と初期化
	boss_ = new Boss();
	boss_->Initialize(bossModel_, &viewProjection_);
}

void GameScene::Update() {
	// プレイヤーの更新
	player_->Update();
	// ボスの更新
	boss_->Updata();
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
	// プレイヤーの描画
	player_->Draw();
	// ボスの描画
	boss_->Draw();
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