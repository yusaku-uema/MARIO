#pragma once
#include "AbstractScene.h"
#include "player.h"
#include"Stage.h"
#include "BackgroundStage.h"

class GameMain :
    public AbstractScene
{
private:
    Player* player;
    BackgroundStage* background_stage;
    Stage* stage;

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

