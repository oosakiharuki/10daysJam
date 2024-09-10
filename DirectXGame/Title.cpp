#include "Title.h"
#include "Input.h"
#include "DirectXCommon.h"

Title::~Title() { 
	delete modelFlont_;
	delete modelBack_;
}

void Title::Initialize() { 

	worldTransform_.Initialize();
	viewProjection_.Initialize();
	modelBack_ = Model::CreateFromOBJ("title1", true);
	modelFlont_ = Model::CreateFromOBJ("title2", true);
	isfinish = false;
}

void Title::Update() { 
	worldTransform_.UpdateMatrix();
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		isfinish = true;
	} 
}

void Title::Draw() {
	DirectXCommon* dxCommon_ = DirectXCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Model::PreDraw(commandList);
	modelBack_->Draw(worldTransform_,viewProjection_);
	modelFlont_->Draw(worldTransform_, viewProjection_);
	Model::PostDraw();
}