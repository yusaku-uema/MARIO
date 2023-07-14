#pragma once
#include "AbstractScene.h"
#include "player.h"
#include "Stage.h"
#include "BackgroundStage.h"

class GameMain :
    public AbstractScene
{
private:

    
    int block[NUM_MAP_X][NUM_MAP_X];

    Player* player;
    BackgroundStage* background_stage;
    Stage* stage[NUM_MAP_Y][NUM_MAP_X];

public:

    //コンストラクタ
    GameMain();

    //デストラクタ
    ~GameMain();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;

};

