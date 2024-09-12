#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include "cmath"

// Vector3の足し算
Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3& operator+=(Vector3& v1, const Vector3& v2);

// Vector3の引き算
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3 operator-=(Vector3& v1, const Vector3& v2);

// Vector3の掛け算(スカラー)
Vector3 operator*(const Vector3& v, float s);
Vector3& operator*=(Vector3& v, float s);

// Vector3同士の掛け算
Vector3 operator*(const Vector3& v1, const Vector3& v2);
Vector3& operator*=(Vector3& v1, const Vector3& v2);

// 加算
Vector3 Add(const Vector3& v1, const Vector3& v2);
// 長さの2乗
float LengthSquared(const Vector3& v);
    // 長さ
float Length(const Vector3& v);
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
// 平行移動行列
// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale);
// x軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);
// y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);
// z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);
// アフィン変換
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);