#pragma once

//サイズ
struct Area
{
	float height;	//縦
	float width;	//横
};

//中心座標
struct Location
{
	float x;	//中心座標(x)
	float y;	//中心座標(y)
};

class BoxCollider
{

public:
	//BoxColliderとの当たり判定
	bool HitBox(const class BoxCollider* box_collider) const;

	//中心座標の取得
	Location GetLocation()const;

	//半径の取得
	Area GetArea()const;

protected:

	Area area; //範囲
	Location location; //中心座標
};

