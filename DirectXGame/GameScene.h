#pragma once

#include "Effect.h"
#include "KamataEngine.h"

#include <list>

using namespace KamataEngine;
using namespace MathUtility;

class GameScene {
public:
	GameScene() = default;
	~GameScene();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

	// エフェクト生成
	void EffectBorn(Vector3 position);

private:
	// カメラ
	Camera camera_;

	// モデル
	Model* modelEffect_ = nullptr;

	// エフェクト一覧
	std::list<Effect*> effects_;
};