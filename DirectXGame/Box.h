#pragma once
#include "Model.h"
#include "Vector3.h"
#include "WorldTransform.h"
class Box {
public:
	void Initialize(Model* model, ViewProjection* viewProjection);

	void Update();

	void Draw();

	//落下
	void SetFalling(bool falling) { isFalling_ = falling; }
	void SetPosition(const Vector3& position) { 
		worldTransform_.translation_ = position;
		worldTransform_.UpdateMatrix();
	}
	//箱の位置を取得
	const Vector3& GetPosition() const { return worldTransform_.translation_; }

	Vector3 GetWorldPosition();

	AABB GetAABB();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	// 重力
	bool isFalling_ = false;
	float fallSpeed_ = 0.0f;
	//重力加速度
	static constexpr float kGravity = 0.1f; 
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
};

