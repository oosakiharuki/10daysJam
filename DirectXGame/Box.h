#pragma once
#include "Model.h"
#include "Vector3.h"
#include "WorldTransform.h"
class Box {
public:
	void Initialize(Model* model, ViewProjection* viewProjection);

	void Update();

	void Draw();

	void SetPosition(const Vector3& position) { 
		worldTransform_.translation_ = position;
		worldTransform_.UpdateMatrix();
	}
	//箱の位置を取得
	const Vector3& GetPosition() const { return worldTransform_.translation_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
};
