#include "Model.h"
#include "WorldTransform.h"
#include <sstream>

class Enemy{
public:
	/// <summary>
	/// 初期位置
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="viewProjection">ビュープロジェクション</param>
	/// <param name="position">位置</param>
	void Initialize(Model* model,ViewProjection* viewProjection,Vector3 position);

	void LoadEnemyMoveData();
	void UpdateEnemyPopCommands(uint32_t number);

	void Update();
	void Draw();

	Vector3 GetWorldPosition();

	AABB GetAABB();

private:

	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;

	Vector3 move = {0, 0, 0};
	float kSpeed;
	float kLoad;
	Vector3 kRange; //半径
	bool rotateFlag; //敵が T:回転するか / F:斜め移動か

	std::stringstream enemyMoveCommands;

	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
};