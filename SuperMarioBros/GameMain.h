#pragma once
#include "AbstractScene.h"
#include "player.h"
#include "Stage.h"
#include"CameraWork.h"
#include "BackgroundStage.h"

class GameMain :
    public AbstractScene
{
private:

    //描画座標
    int rendering_coordinates_x;
   
    //読み取ったデータ保存
    int block;

    Player* player;
    BackgroundStage* background_stage;
    CameraWork* camerawork;
    Stage* stage[MAP_Y][MAP_MAX];

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

