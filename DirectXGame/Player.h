#pragma once
#include "Model.h"
#include "Vector3.h"
#include "WorldTransform.h"
#include "Box.h"

// 左右
enum class LRDirection {
	kRight,
	kLeft,
};
class MapChipField;
class Player {
public:
	void Initialize(Model* model, ViewProjection* viewProjection,const Vector3&position);

	void Update(const std::vector<Box*>& boxes);

	void Draw();
    //移動
	void Move();
	//旋回
	void Rotate();
	//箱を持ち上げる・落とす
	void PickOrDropBox(Box* box);
	//セッタ
	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }
	const WorldTransform& GetWorldTransform() { return worldTransform_; };
	//速度加算
	const Vector3& GetVelocity() const { return velocity_; }
    //プレイヤーと箱との距離
	bool IsNearBox(const Box* box) const;
	// 一番近い箱を探す
	Box* FindNearestBox(const std::vector<Box*>& boxes);

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
	static inline const float kLimitRunSpeed = 0.15f;
	// 旋回時間<秒>
	static inline const float kTimeTurn = 0.3f;
	//箱の高さ
	static constexpr float kBoxPickupHeight = 2.0f;
	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;
	//箱を持ち上げてるか
	bool isCarryingBox_ = false;
	//持ち上げてる箱のポインタ
	Box* carriedBox_ = nullptr;
	//キーの状態保存
	bool wasQKeyPressed_ = false;
};