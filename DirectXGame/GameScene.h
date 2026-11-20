#pragma once

#include "DrawNumber.h"
#include "GraphBar.h"
#include "KamataEngine.h"
#include "Particle.h"
#include "Player.h"
#include "Stage.h"

#include <list>

// ゲームシーン
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

	// 流星群用
	KamataEngine::Model* modelParticle_ = nullptr;
	std::list<Particle*> particles_;
	int spawnCounter_ = 0;

	uint32_t textureHandleStage_ = 0;
	uint32_t textureHandleGraph_ = 0;
	uint32_t textureHandleNumber_ = 0;

	int hp_ = 200;
	uint32_t gameScore_ = 0;

	// 流星を発生させる
	void ParticleBorn();
};
