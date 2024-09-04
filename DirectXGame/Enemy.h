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

};