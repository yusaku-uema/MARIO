#pragma once

//�����蔻��Ȃ��B
class BackgroundStage
{
private:

	//�摜
	int image;

	//�����Ȃ��w�i�f�[�^
	int data[301] = {};
		
	//�w�i�摜���Ăяo���̂�
	bool call_flg;

public:

	//�R���X�g���N�^
	BackgroundStage();

	//�f�X�g���N�^
	~BackgroundStage();

	//�X�V
	void UpdateFlg(bool call_flg);

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const;
};

