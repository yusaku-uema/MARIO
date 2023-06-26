#pragma once

//ƒTƒCƒY
struct Area
{
	float height;	//c
	float width;	//‰¡
};

class BoxCollider
{

public:
	//BoxCollider‚Æ‚Ì“–‚½‚è”»’è
	bool HitBox(const class BoxCollider* box_collider) const;

protected:

	Area area; //”ÍˆÍ
};

