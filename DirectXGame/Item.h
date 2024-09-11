#pragma once
#include "Model.h"
#include "Vector3.h"
#include "WorldTransform.h"
class Item {
public:
	void Initialize(Model* model, ViewProjection* viewProjection);

	void Update();

	void Draw();

	void SetPosition(const Vector3& position) {
		worldTransform_.translation_ = position;
		worldTransform_.UpdateMatrix();
	}

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
