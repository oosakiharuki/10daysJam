#pragma once
#include "Vector3.h"
#include <stdint.h>
#include <vector>
#include <string>
enum class MapChipType {
	kBlank, // 空洞
	kBlock, // ブロック
};
struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};

class MapChipField {
public:
	void ResetMapChipData();
	void LoadMapChipCsv(const std::string& filePath);
	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);
	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);
	uint32_t GetNumBlockVirtical();
	uint32_t GetNumBlockHorizontal();

private:
	// 1ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;
	// ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;//18
	static inline const uint32_t kNumBlockHorizontal = 100;//32

	MapChipData mapChipData_;
};
