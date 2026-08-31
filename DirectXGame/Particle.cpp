#include "Particle.h"

#include <algorithm>
#include <cassert>
#include <cmath>

using namespace MathUtility;

// ========================================
// 流星の初期化
// ========================================
void Particle::Initialize(Model* model, Vector3 position, Vector3 velocity) {

	assert(model);

	model_ = model;

	// 初期位置
	worldTransform_.translation_ = position;

	// 移動量
	velocity_ = velocity;

	// 最初の大きさ
	worldTransform_.scale_ = {0.35f, 0.35f, 0.35f};

	// 移動方向を向く
	worldTransform_.rotation_.z = std::atan2f(velocity_.y, velocity_.x);

	// ワールド変換初期化
	worldTransform_.Initialize();

	// 本体カラー
	objectColor_.Initialize();

	color_ = {1.0f, 1.0f, 0.5f, 1.0f};

	objectColor_.SetColor(color_);

	// ========================================
	// 軌跡初期化
	// ========================================

	for (int i = 0; i < kTrailCount; i++) {

		// 最初から少しずつ後ろにずらす
		oldPositions_[i] = position - velocity_ * static_cast<float>(i);

		float scale = 0.22f - static_cast<float>(i) * 0.015f;

		if (scale < 0.04f) {
			scale = 0.04f;
		}

		trailWorldTransforms_[i].translation_ = oldPositions_[i];

		trailWorldTransforms_[i].scale_ = {scale, scale, scale};

		trailWorldTransforms_[i].rotation_.z = std::atan2f(velocity_.y, velocity_.x);

		trailWorldTransforms_[i].Initialize();

		trailObjectColors_[i].Initialize();

		trailColors_[i] = {1.0f, 0.8f, 0.2f, 0.5f};

		trailObjectColors_[i].SetColor(trailColors_[i]);
	}

	counter_ = 0.0f;
	isFinished_ = false;
}

// ========================================
// 更新
// ========================================
void Particle::Update() {

	if (isFinished_) {
		return;
	}

	// 時間
	counter_ += 1.0f / 60.0f;

	float t = counter_ / kDuration;

	// ========================================
	// 過去の位置を保存
	// ========================================

	for (int i = kTrailCount - 1; i > 0; i--) {

		oldPositions_[i] = oldPositions_[i - 1];
	}

	oldPositions_[0] = worldTransform_.translation_;

	// ========================================
	// 流星を移動
	// ========================================

	worldTransform_.translation_ += velocity_;

	// ========================================
	// 徐々に大きくする
	// ========================================

	float scale = 0.35f + t * 0.9f;

	worldTransform_.scale_ = {scale * 1.5f, scale * 0.7f, scale * 0.7f};

	// ========================================
	// 移動方向を向く
	// ========================================

	worldTransform_.rotation_.z = std::atan2f(velocity_.y, velocity_.x);

	// ========================================
	// 本体をフェード
	// ========================================

	color_.w = std::clamp(1.0f - t * 0.7f, 0.0f, 1.0f);

	objectColor_.SetColor(color_);

	// ========================================
	// 軌跡
	// ========================================

	for (int i = 0; i < kTrailCount; i++) {

		trailWorldTransforms_[i].translation_ = oldPositions_[i];

		float trailScale = 0.22f - static_cast<float>(i) * 0.015f;

		if (trailScale < 0.03f) {
			trailScale = 0.03f;
		}

		// 後ろほど小さくする
		float fadeScale = 1.0f - static_cast<float>(i) / static_cast<float>(kTrailCount);

		trailScale *= fadeScale;

		trailWorldTransforms_[i].scale_ = {trailScale * 1.3f, trailScale * 0.7f, trailScale * 0.7f};

		// 流星と同じ方向
		trailWorldTransforms_[i].rotation_.z = std::atan2f(velocity_.y, velocity_.x);

		// 後ろほど透明
		trailColors_[i].w = 0.75f * (1.0f - static_cast<float>(i) / static_cast<float>(kTrailCount));

		trailColors_[i].w *= 1.0f - t * 0.5f;

		trailObjectColors_[i].SetColor(trailColors_[i]);

		trailWorldTransforms_[i].UpdateMatrix();
	}

	// 本体の行列更新
	worldTransform_.UpdateMatrix();

	// 寿命
	if (counter_ >= kDuration) {

		counter_ = kDuration;

		isFinished_ = true;
	}
}

// ========================================
// 描画
// ========================================
void Particle::Draw(Camera& camera) {

	// ========================================
	// 軌跡
	// ========================================

	for (int i = kTrailCount - 1; i >= 0; i--) {

		model_->Draw(trailWorldTransforms_[i], camera, &trailObjectColors_[i]);
	}

	// ========================================
	// 流星本体
	// ========================================

	model_->Draw(worldTransform_, camera, &objectColor_);
}