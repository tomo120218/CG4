#pragma once

#include <KamataEngine.h>

using namespace KamataEngine;

// パーティクル
class Particle {

public:
	// 流星の初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Vector3 position, KamataEngine::Vector3 velocity);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera& camera);

	// 終了フラグ
	bool IsFinished() { return isFinished_; }

private:
	// 流星本体のワールド変換
	KamataEngine::WorldTransform worldTransform_;

	// 軌跡のワールド変換
	KamataEngine::WorldTransform trailWorldTransforms_[12];

	// モデル
	KamataEngine::Model* model_ = nullptr;

	// 本体の色
	KamataEngine::ObjectColor objectColor_;

	// 軌跡の色
	KamataEngine::ObjectColor trailObjectColors_[12];

	// 本体の色
	KamataEngine::Vector4 color_{};

	// 軌跡の色
	KamataEngine::Vector4 trailColors_[12]{};

	// 移動量
	KamataEngine::Vector3 velocity_{};

	// 過去の位置
	KamataEngine::Vector3 oldPositions_[12]{};

	// 終了フラグ
	bool isFinished_ = false;

	// 経過時間
	float counter_ = 0.0f;

	// 寿命
	const float kDuration = 1.5f;

	// 軌跡の数
	static const int kTrailCount = 12;
};