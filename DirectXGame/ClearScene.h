#ifndef CLEARSCENE
#define CLEARSCENE

#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Skydome.h"

class ClearScene{
public:
	~ClearScene();
	void Initialize();
	void Update();
	void Draw();
	bool IsNextScene() { return isfinish; }

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Model* modelBack_ = nullptr;
	Model* modelSkydome_;
	Skydome* skydome_ = nullptr;
	//Model* modelFlont_ = nullptr;
	bool isfinish = false;
};

#endif // CLEARSCENE