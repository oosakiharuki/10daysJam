#pragma once
#include "Model.h"
#include "Vector3.h"
#include "WorldTransform.h"
class Box {
public:
	void Initialize();

	void Update();

	void Draw();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
};
