#include "Model.h"
#include "WorldTransform.h"

class Title {
public:
	void Initialize();
	void Update();
	void Draw();
	bool IsNextScene() { return isfinish; }

private:
	bool isfinish = false;
};