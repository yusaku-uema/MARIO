#pragma once

//�T�C�Y
struct Area
{
	float height;	//�c
	float width;	//��
};

class BoxCollider
{

public:
	//BoxCollider�Ƃ̓����蔻��
	bool HitBox(const class BoxCollider* box_collider) const;

protected:

	Area area; //�͈�
};

