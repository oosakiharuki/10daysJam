#pragma once
#include "Model.h"
#include "Vector3.h"
#include "WorldTransform.h"
class obstructionBox {
public:
	void Initialize(Model* model, ViewProjection* viewProjection);

	void Update();

	void Draw();
	void SetPosition(const Vector3& position) {
		worldTransform_.translation_ = position;
		worldTransform_.UpdateMatrix();
	}
	Vector3 GetWorldPosition();
	const Vector3& GetPosition() const { return worldTransform_.translation_; }
	AABB GetAABB();

private:
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
};
