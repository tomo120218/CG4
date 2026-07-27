#pragma once

#include "KamataEngine.h"

class TitleScene {
public:
	~TitleScene();

	void Initialize();
	void Update();
	void Draw();

private:
	uint32_t textureHandle_ = 0;
	uint32_t textureHandleFont_ = 0;
	uint32_t textureHandleHit_ = 0;

	KamataEngine::Sprite* sprite_ = nullptr;
	KamataEngine::Sprite* spriteFont_ = nullptr;
	KamataEngine::Sprite* spriteHit_ = nullptr;

	int timer = 0;
};