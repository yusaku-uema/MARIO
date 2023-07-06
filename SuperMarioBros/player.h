#pragma once
#include"BoxCollider.h"
#include"PadInput.h"


enum class MARIO_STATE
{
	AMALL_MAIO,   //チビマリオ 
	SUPER_MARIO, //スーパマリオ
	FIRE_MARIO, //ファイアマリオ
	STAR_MARIO, //スターマリオ
	CHANGE_SUPER_MARIO, //スーパマリオに変化中
	CHANGE_FIRE_MARIO, //ファイアマリオに変化中
	DEATH //死亡状態
};


class Player :public BoxCollider
{
private:
	
	int tiny_mario[9]; //チビマリオ
	int power_up_image[3]; //チビマリオからスーパマリオ 
	int super_mario_image[9]; //スーパマリオ
	int fire_mario[8]; //ファイアマリオ
	int star_mario_tiny[36]; //小さい状態でのスターマリオ
	int star_mario[36]; //スーパマリオorファイアマリオの状態でのスターマリオ

	long long int animation_time; //アニメーション時間
	int animation; //画像切り替え
	int animation_count; //画像切り替え
	int power_up_animation; //パワーアップする時に使うアニメーション用変数
	int fire_power_up[4]; //ファイアマリオになるときの使う要素数を収納する。
	int stick_x; //スティック移動


	float jumping_power; //ジャンプ(上に向かう力)
	float descent_speed; //降下スピード
	float movement_speed; //移動速度
	float b_button_press_time; //Bボタンを押している時間

	bool jump_flg; //ジャンプしているのか
	bool left_move; //左に動いているのか
	bool power_up_flg; //マリオがパワーアップアニメーションを行っているのか


	MARIO_STATE mario_state; //マリオの状態
	

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

	//マリオパワーアップ,アニメーション
	void PowerUpAnimation();

};

