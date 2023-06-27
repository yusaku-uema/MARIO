#pragma once

//�T�C�Y
struct Area
{
	float height;	//�c
	float width;	//��
};

//���S���W
struct Location
{
	float x;	//���S���W(x)
	float y;	//���S���W(y)
};

class BoxCollider
{

public:
	//BoxCollider�Ƃ̓����蔻��
	bool HitBox(const class BoxCollider* box_collider) const;

	//���S���W�̎擾
	Location GetLocation()const;

	//���a�̎擾
	Area GetArea()const;

protected:

	Area area; //�͈�
	Location location; //���S���W
};

