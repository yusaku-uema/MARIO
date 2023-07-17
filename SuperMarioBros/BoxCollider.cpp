#include "BoxCollider.h"

//-----------------------------------
// “–‚½‚è”»’è
//-----------------------------------
bool BoxCollider::HitBox(const BoxCollider* box_collider) const
{
	bool ret = false; //•Ô‚è’l

					  
	//Ž©•ª‚Ì“–‚½‚è”»’è‚Ì”ÍˆÍ
	float my_x[2];
	float my_y[2];

	//‘ŠŽè‚Ì“–‚½‚è”»’è‚Ì”ÍˆÍ
	float sub_x[2];
	float sub_y[2];

	//Ž©•ª‚Ì“–‚½‚è”»’è‚Ì”ÍˆÍ‚ÌŒvŽZ
	my_x[0] = location.x - (area.width / 2);
	my_y[0] = location.y - (area.height / 2);
	my_x[1] = my_x[0] + area.width;
	my_y[1] = my_y[0] + area.height;

	//‘ŠŽè‚Ì“–‚½‚è”»’è‚Ì”ÍˆÍ‚ÌŒvŽZ
	sub_x[0] = box_collider->GetLocation().x - (box_collider->GetArea().width / 2);
	sub_y[0] = box_collider->GetLocation().y - (box_collider->GetArea().height / 2);
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;

	if ((my_x[0] <= sub_x[1]) && (sub_x[0] <= my_x[1])
		&& (my_y[0] <= sub_y[1]) && (sub_y[0] <= my_y[1])) //“–‚½‚è”»’è
	{
		ret = true;
	}

	return ret;
}

bool BoxCollider::HitBlock(const class BoxCollider* box_collider) const
{
	bool ret = false; //•Ô‚è’l


	//Ž©•ª‚Ì“–‚½‚è”»’è‚Ì”ÍˆÍ
	float my_x[2];
	float my_y[2];

	//‘ŠŽè‚Ì“–‚½‚è”»’è‚Ì”ÍˆÍ
	float sub_x[2];
	float sub_y[2];

	//Ž©•ª‚Ì“–‚½‚è”»’è‚Ì”ÍˆÍ‚ÌŒvŽZ
	my_x[0] = location.x - (area.width / 2);
	my_y[0] = location.y - (area.height / 2);
	my_x[1] = my_x[0] + area.width;
	my_y[1] = my_y[0] + area.height;

	//‘ŠŽè‚Ì“–‚½‚è”»’è‚Ì”ÍˆÍ‚ÌŒvŽZ
	sub_x[0] = box_collider->GetLocation().x ;
	sub_y[0] = box_collider->GetLocation().y ;
	sub_x[1] = sub_x[0] + box_collider->GetArea().width;
	sub_y[1] = sub_y[0] + box_collider->GetArea().height;

	if ((my_x[0] <= sub_x[1]) && (sub_x[0] <= my_x[1])
		&& (my_y[0] <= sub_y[1]) && (sub_y[0] <= my_y[1])) //“–‚½‚è”»’è
	{
		ret = true;
	}

	return ret;
}

//-----------------------------------
// 
//-----------------------------------
Location BoxCollider::GetLocation() const
{
    return location;
}

Area BoxCollider::GetArea() const
{
	return area;
}
