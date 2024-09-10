#include "DirectXCommon.h"
#include "Input.h"
#include "ClearScene.h"

ClearScene::~ClearScene() {
	//delete modelFlont_;
	delete modelBack_;
}

void ClearScene::Initialize() {

	worldTransform_.Initialize();
	viewProjection_.Initialize();
	modelBack_ = Model::CreateFromOBJ("title1", true);
	//modelFlont_ = Model::CreateFromOBJ("title2", true);
	isfinish = false;
}

void ClearScene::Update() {
	worldTransform_.UpdateMatrix();
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		isfinish = true;
	}
}

void ClearScene::Draw() {
	DirectXCommon* dxCommon_ = DirectXCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Model::PreDraw(commandList);
	modelBack_->Draw(worldTransform_, viewProjection_);
	//modelFlont_->Draw(worldTransform_, viewProjection_);
	Model::PostDraw();
}