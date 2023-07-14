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

    //�R���X�g���N�^
    GameMain();

    //�f�X�g���N�^
    ~GameMain();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

};

