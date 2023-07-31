#pragma once
#include"BoxCollider.h"
#include"Define.h"


//背景と違ってこっちには当たり判定がある
class Stage : public  BoxCollider
{
private:
	
	//ブロックの種類
	int image;

	int block[12];

	int  animation;

	long long int animation_count;

	int type;

	int camerax;

public:

	//コンストラクタ
	Stage(float location_x,float location_y,float area_width,float area_height ,int type);

	//デストラクタ
	~Stage();

	//更新
	void Update(int camerax);

	//描画に関することを実装
	void Draw() const;

};

