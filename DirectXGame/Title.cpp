#include "Title.h"
#include "Input.h"
#include "DirectXCommon.h"

Title::~Title() { 
	delete modelFlont_;
	delete modelBack_;
	delete modelSkyDome_;
	delete skydome_;
	delete modelStart_;

}

void Title::Initialize() { 

	worldTransform_.Initialize();
	viewProjection_.Initialize();
	modelBack_ = Model::CreateFromOBJ("title1", true);
	modelFlont_ = Model::CreateFromOBJ("title2", true);
	isfinish = false;

	modelSkyDome_ = Model::CreateFromOBJ("sphere", true);
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkyDome_, &viewProjection_);

	modelStart_ = Model::CreateFromOBJ("startText", true);
	startWorldTransform_.Initialize();
	startWorldTransform_.translation_ = {0.0f, -10.0f, 0.0f};
	initialPositionX_ = startWorldTransform_.translation_.y;

	audio_ = Audio::GetInstance();
	// サウンドデータの読み込み
	soundDataHandle_ = audio_->LoadWave("gameBGM.wav");
	soundDataHadle2_ = audio_->LoadWave("buttonSE.wav");
	// 音声再生
	voiceJandle_ = audio_->PlayWave(soundDataHandle_, true, 0.7f);
}

void Title::Update() { 
	worldTransform_.UpdateMatrix();
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		audio_->StopWave(voiceJandle_);
		audio_->PlayWave(soundDataHadle2_);
		isfinish = true;
	} 
	skydome_->Update();

	// テキストの移動処理
	startWorldTransform_.translation_.y += moveSpeed_ * moveDirection_;

	// 一定範囲を超えたら移動方向を反転
	if (std::abs(startWorldTransform_.translation_.y - initialPositionX_) > moveRange_) {
		moveDirection_ *= -1; // 移動方向を反転
	}
	startWorldTransform_.UpdateMatrix();
}

void Title::Draw() {
	DirectXCommon* dxCommon_ = DirectXCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Model::PreDraw(commandList);
	skydome_->Draw();
	modelBack_->Draw(worldTransform_,viewProjection_);
	modelFlont_->Draw(worldTransform_, viewProjection_);
	modelStart_->Draw(startWorldTransform_, viewProjection_);
	Model::PostDraw();
}