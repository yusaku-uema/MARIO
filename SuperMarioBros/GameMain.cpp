#include "GameMain.h"

GameMain::GameMain()
{
	player = new Player();
	background_stage = new BackgroundStage();
}

GameMain::~GameMain()
{
	delete player;
	delete background_stage;
}

AbstractScene* GameMain::Update()
{
	
	player->Update();


	return this;
}

void GameMain::Draw() const
{
	background_stage->Draw();
	player->Draw();
}
