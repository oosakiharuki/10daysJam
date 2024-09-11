#ifndef INSTRUCTION
#define INSTRUCTION

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Skydome.h"

class Instruction {
public:
	~Instruction();
	void Initialize();
	void Update();
	void Draw();
	bool IsNextScene() { return isfinish; }

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Model* modelBackground_ = nullptr;
	Model* modelSkyDome_ = nullptr;
	Skydome* skydome_ = nullptr;
	bool isfinish = false;
};


#endif / INSTRUCTION
