#pragma once
class StageSelect {
public:
	void Initialize();
	void Update();
	void Draw();
	bool IsNextScene() { return isfinish; }

private:
	bool isfinish = false;
};
