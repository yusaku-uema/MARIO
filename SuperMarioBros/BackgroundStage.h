#pragma once

//�����蔻��Ȃ��B
class BackgroundStage
{
private:

	//�摜
	int image;
	
	//�`�悷����W
	int x; 
	int y;

	//�����Ȃ��w�i�f�[�^
	int data[301] = {};
		
	//�w�i�摜���Ăяo���̂�
	bool call_flg;

	//������~����̂�
	bool processing_halt;

public:

	//�R���X�g���N�^
	BackgroundStage();

	//�f�X�g���N�^
	~BackgroundStage();

	//�X�V
	void Update();

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const;
};

