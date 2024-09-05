#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;
};

struct AABB {
	Vector3 min; //!< 最小点
	Vector3 max; //!< 最大点
};