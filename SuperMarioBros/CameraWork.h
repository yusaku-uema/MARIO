#pragma once

class CameraWork
{
private:
		
	//�X�N���[���n���H������
	int camerax;//�J�����̍�����W
	int charx;//���L�����ʒu
	int view_charx;//���L�����̕\���ʒu�B���̍��W��draw����B

public:

	//�R���X�g���N�^
	CameraWork();

	//�f�X�g���N�^
	~CameraWork();

	//�X�V
	void Update(float player_location);

	//�L�����N�^�̕`�悷��ʒu
	int GetViewCharX();

	//�X�e�[�W�`��ʒu�����炷
	int GetCameraX();

};

