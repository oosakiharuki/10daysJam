#include "Instruction.h"
#include "Input.h"
#include "DirectXCommon.h"
Instruction::~Instruction() { 
	delete modelBackground_;
	delete modelSkyDome_;
	delete skydome_;
}

void Instruction::Initialize() {
	worldTransform_.Initialize();
	viewProjection_.Initialize();
	modelBackground_ = Model::CreateFromOBJ("ruleText", true);
	modelSkyDome_ = Model::CreateFromOBJ("sphere", true);
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkyDome_, &viewProjection_);
	isfinish = false;

	audio_ = Audio::GetInstance();
	soundDataHandle_ = audio_->LoadWave("gameBGM.wav");
	soundDataHandle2_ = audio_->LoadWave("buttonSE.wav");
	voiceHandle_ = audio_->PlayWave(soundDataHandle_, true,0.7f);
}

void Instruction::Update() {
	skydome_->Update();
	worldTransform_.UpdateMatrix();
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		audio_->StopWave(voiceHandle_);
		audio_->PlayWave(soundDataHandle2_);
		isfinish = true;
	}
}

void Instruction::Draw() {
	DirectXCommon* dxCommon_ = DirectXCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Model::PreDraw(commandList);
	modelBackground_->Draw(worldTransform_, viewProjection_);
	skydome_->Draw();
	Model::PostDraw();
}