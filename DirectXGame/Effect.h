#pragma once

#include "KamataEngine.h"

using namespace KamataEngine;
using namespace MathUtility;

class Effect {
public:
	void Initialize(Model* model, float rotate, float size, Vector3 position, Vector3 color);

	void Update();

	void Draw(Camera& camera);

	bool IsFinished() const { return isFinished_; }

private:
	// 存続時間
	const float kDuration = 1.0f;

	// 経過時間
	float counter_ = 0.0f;

	// 終了フラグ
	bool isFinished_ = false;

	// モデル
	Model* model_ = nullptr;

	// ワールド変換
	WorldTransform worldTransform_;

	// 色変更
	ObjectColor objectColor_;

	// RGBAカラー
	Vector4 color_ = {1, 1, 1, 1};
};