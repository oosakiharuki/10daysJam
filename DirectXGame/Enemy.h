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
	void Initialize(Model* model,ViewProjection* viewProjection,Vector3 position,float speed,float range);
	void Update();
	void Draw();

private:

	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;

	Vector3 move = {0, 0, 0};
	float kSpeed;
	float kLoad;
	float kRange; //半径

};