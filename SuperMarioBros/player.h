#pragma once
#include"BoxCollider.h"
#include"PadInput.h"

class Player :public BoxCollider
{
private:
	
	int tiny_mario[9]; //チビマリオ
	long long int animation_time; //アニメーション時間
	int animation; //画像切り替え

	int stick_x; //スティック移動
	float jumping_power; //ジャンプ(上に向かう力)
	float descent_speed; //降下スピード
	float movement_speed; //移動速度
	float direction_move; //移動する方向

	bool jump_flg; //ジャンプしているのか
	bool left_move; //左に動いているのか
	

public:

	//コンストラクタ
	Player();

	//デストラクタ
	~Player();
	

	//更新
	void Update();

	//描画に関することを実装
	void Draw() const;

	//マリオの操作
	void Operation();

	//マリオジャンプ
	void MarioJump();

};

