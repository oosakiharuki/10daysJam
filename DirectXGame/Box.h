#pragma once
#include "Model.h"
#include "Vector3.h"
#include "WorldTransform.h"
class Box {
public:
	void Initialize();

	void Update();

	void Draw();

	Vector3 GetWorldPosition();

	AABB GetAABB();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
};
