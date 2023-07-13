#include "BackgroundStage.h"
#include"DxLib.h"


#define  SIZE_MAP_X  32  //< �}�b�v�`�b�vX�T�C�Y
#define  SIZE_MAP_Y  32	//< �}�b�v�`�b�vY�T�C�Y

#define NUM_MAP_X 20 // 32x20=640
#define NUM_MAP_Y 15 // 32x15=480

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
BackgroundStage::BackgroundStage()
{
	image = LoadGraph("image/stage/sora.png");
	
	for (int i = 0; i < 300; i++)
	{
		data[i] = 0;
	}

	call_flg = false;
}


//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
BackgroundStage::~BackgroundStage()
{

}

//-----------------------------------
// �`�悷��̂����Ȃ��̂�
//-----------------------------------
void BackgroundStage::UpdateFlg(bool call_flg)
{
	this->call_flg = call_flg;
}


//-----------------------------------
// �󂾂���`��
//-----------------------------------
void BackgroundStage::Draw() const
{
	if (call_flg == false)
	{
		for (int j = 0; j < NUM_MAP_Y; j++)
		{
			for (int i = 0; i < NUM_MAP_X; i++)
			{
				DrawGraph(i * SIZE_MAP_X, j * SIZE_MAP_Y, image, FALSE);
			}
		}
	}
}
