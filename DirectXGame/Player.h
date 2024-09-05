#pragma once
#include "Model.h"
#include "Vector3.h"
#include "WorldTransform.h"

// 左右
enum class LRDirection {
	kRight,
	kLeft,
};
class MapChipField;
class Player {
public:
	void Initialize(Model* model, ViewProjection* viewProjection,const Vector3&position);

	void Update();

	void Draw();
    //移動
	void Move();
	//旋回
	void Rotate();
	//セッタ
	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	//マップチップ
	MapChipField* mapChipField_ = nullptr;
	//速度
	Vector3 velocity_ = {};
	LRDirection lrDirection_ = LRDirection::kRight;
	//加速
	static inline const float kAcceleration = 0.05f;
	//速度減衰
	static inline const float kAttenuation = 0.05f;
	static inline const float kLimitRunSpeed = 0.3f;
	// 旋回時間<秒>
	static inline const float kTimeTurn = 0.3f;
	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;
};