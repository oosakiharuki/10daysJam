#include "Instruction.h"
#include "Input.h"
#include "DirectXCommon.h"
Instruction::~Instruction() { delete modelBackground_; }

void Instruction::Initialize() {
	worldTransform_.Initialize();
	viewProjection_.Initialize();
	modelBackground_ = Model::CreateFromOBJ("title1", true);
	isfinish = false;
}

void Instruction::Update() {
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
	Model::PostDraw();
}