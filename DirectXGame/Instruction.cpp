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
}

void Instruction::Update() {
	skydome_->Update();
	worldTransform_.UpdateMatrix();
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
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