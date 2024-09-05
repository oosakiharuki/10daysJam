#include "Model.h"
#include "WorldTransform.h"

class Enemy{
public:
	/// <summary>
	/// 初期位置
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="position">位置</param>
	void Initialize(Model* model,ViewProjection* viewProjection,Vector3 position);
	void Update();
	void Draw();

private:

	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;

	Vector3 move = {0, 0, 0};
	float speed = 0.0f;
	float range = 10.0f; //半径

};