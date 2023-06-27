#pragma once
#include"BoxCollider.h"
#include"PadInput.h"

class Player :public BoxCollider
{
private:
	
	int stick_x; //スティック移動
	float descent_speed; //降下スピード
	float movement_speed; //移動速度
	float direction_move; //移動する方向
	

public:

	//コンストラクタ
	Player();

	//デストラクタ
	~Player();
	

	//更新
	void Update();

	//描画に関することを実装
	void Draw() const;

};

