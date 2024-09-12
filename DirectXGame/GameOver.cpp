#include "DirectXCommon.h"
#include "Input.h"
#include "GameOver.h"
#include "Skydome.h"

GameOver::~GameOver() {
	delete model_;
	delete modelSkydome_;
	delete skydome_;
}

void GameOver::Initialize() {
	worldTransform_.Initialize();
	viewProjection_.Initialize();
	model_ = Model::CreateFromOBJ("title2", true);
	modelSkydome_ = Model::CreateFromOBJ("sphere", true);
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_, &viewProjection_);
	isfinish = false;
}

void GameOver::Update() {
	// テキストの移動処理
	worldTransform_.translation_.y += moveSpeed_ * moveDirection_;

	// 一定範囲を超えたら移動方向を反転
	if (std::abs(worldTransform_.translation_.y - initialPositionX_) > moveRange_) {
		moveDirection_ *= -1; // 移動方向を反転
	}

	worldTransform_.UpdateMatrix();
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		isfinish = true;
	}
}

void GameOver::Draw() {
	DirectXCommon* dxCommon_ = DirectXCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Model::PreDraw(commandList);
	skydome_->Draw();
	model_->Draw(worldTransform_, viewProjection_);
	Model::PostDraw();
}
