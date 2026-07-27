#pragma once

#include "KamataEngine.h"

#include "DrawNumber.h"
#include "GraphBar.h"
#include "Player.h"
#include "Stage.h"

class GameScene {
public:
	~GameScene();

	void Initialize();
	void Update();
	void Draw();

private:
	KamataEngine::Camera camera_;

	Stage* stage_ = nullptr;
	Player* player_ = nullptr;
	GraphBar* graphBar_ = nullptr;
	DrawNumber* drawNumber_ = nullptr;

	KamataEngine::Model* modelPlayer_ = nullptr;

	uint32_t textureHandleStage_ = 0;
	uint32_t textureHandleGraph_ = 0;
	uint32_t textureHandleNumber_ = 0;

	int hp_ = 200;
	uint32_t gameScore_ = 0;
};