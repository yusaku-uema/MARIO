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

    //�`����W
    int rendering_coordinates_x;
   
    //�ǂݎ�����f�[�^�ۑ�
    int block;

    Player* player;
    BackgroundStage* background_stage;
    CameraWork* camerawork;
    Stage* stage[MAP_Y][MAP_MAX];

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

