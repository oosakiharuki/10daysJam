#include "Model.h"
#include "WorldTransform.h"

class Enemy{
public:
	void Initialize(Model* model,ViewProjection* viewProjection);
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