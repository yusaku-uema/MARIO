#include "GameMain.h"

GameMain::GameMain()
{
	player = new Player();
	background_stage = new BackgroundStage();
	stage = new Stage();
}

GameMain::~GameMain()
{
	delete player;
	delete background_stage;
	delete stage;
}

AbstractScene* GameMain::Update()
{
	
	player->Update();


	return this;
}

void GameMain::Draw() const
{
	background_stage->Draw();
	stage->Draw();
	player->Draw();
}
