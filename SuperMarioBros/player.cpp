#define _USE_MATH_DEFINES
#define NOMINMAX
#include "player.h"
#include"DxLib.h"
#include <stdio.h>
#include <math.h>
#include <algorithm> 

//当たり判定の大きさ
#define AMALL_MAIO_WIDTH 32
#define AMALL_MAIO_HEIGHT 32

#define SUPER_MARIO_WIDTH 36
#define SUPER_MARIO_HEIGHT 64


//アニメーション切り替え時間
#define SWITCHING_TIME 6
#define POWRT_UP_TIME 10
#define FIRE_MARIO_TIME 5

//最大ジャンプ力
#define STRONG_JUMP 5.5

//歩くスピード
#define WALKING_SPEED 5.0f
#define RUNNING_SPEED 8.0f

//加速スピード
#define ACCELERATION_SPEED  0.1f
#define ACCELERATION_MAX_SPEED 0.3f

//ジャンプ力
#define MINIUM_JUMP 12.0f   //12.0
#define INTERIM_JUMP 17.0f  //16.0
#define MAX_JUMP 6.5f //6.5f

//落下
#define FALL_SPEED 0.6f
#define JUMP_FALL  0.9f
#define FALL_SPEED_MAX 5.5f

//-----------------------------------
// 初期化
//-----------------------------------
Player::Player()
{

	LoadDivGraph("image/mario/mario.png", 9, 9, 1, 32, 32, tiny_mario);
	LoadDivGraph("image/mario/dekamarimation.png", 3, 3, 1, 32, 64, power_up_image);
	LoadDivGraph("image/mario/dekamario.png", 9, 9, 1, 32, 64, super_mario_image);
	LoadDivGraph("image/mario/faiyamario.png", 9, 9, 1, 32, 64, fire_mario);
	LoadDivGraph("image/mario/starsmallmario.png", 36, 9, 4, 32, 32, star_mario_tiny);
	LoadDivGraph("image/mario/starmario.png", 36, 9, 4, 32, 64, star_mario);

	fire_power_up[0] = 0;
	fire_power_up[1] = 9;
	fire_power_up[2] = 18;
	fire_power_up[3] = 27;


	view_charx = 0;
	animation = 0;
	animation_time = 0;
	animation_count = 0;
	power_up_animation = 0;

	descent_speed = 0;
	jumping_descent_speed = 0;
	movement_speed = 0;
	b_button_press_time = 0;
	jumping_power = 0;
	location.x = 30;
	location.y = 30;
	area.height = 32;
	area.width = 32;
	stick_x = 0;

	jump_flg = false;
	right_flg = false;
	left_flg = false;
	power_up_flg = false;
	hit_block_flg = false;
	fall_flg = false;
	side_flg = false;
	bust_flg = false;

	mario_state = MARIO_STATE::AMALL_MAIO;
}

//-----------------------------------
// デストラクタ
//-----------------------------------
Player::~Player()
{

}


//-----------------------------------
// 更新
//-----------------------------------
void Player::Update(int view_charx)
{
	old_location = location;	//前の座標

	this->view_charx = view_charx; //座標更新

	// スティックの感度
	const int stick_sensitivity = 200;

	// スティックのX座標を取得
	int stick_y = PadInput::GetLStick().y;

	//アニメーション
	if (jump_flg == false || movement_speed != 0)
	{
		if (animation_time % SWITCHING_TIME == 0)
		{
			animation++;
			++animation_time;
		}

		if (movement_speed > 0 && right_flg == true)
		{
			//左に動いているのか
			left_move = false;
		}
		else if (movement_speed < 0)
		{
			//左に動いているのか
			left_move = true;
		}

	}
	else if (jump_flg == false)
	{
		animation = 0;
	}




	//当たり判定の設定
	switch (mario_state)
	{
	case MARIO_STATE::AMALL_MAIO:
		//当たり判定の設定
		area.height = AMALL_MAIO_HEIGHT;
		area.width = AMALL_MAIO_WIDTH;

		//アニメーション関係
		if (right_flg == true && movement_speed < 0 && jump_flg == false
			|| left_flg == true && movement_speed > 0 && jump_flg == false)
		{
			animation = 4;
		}
		else if (jump_flg == false)
		{
			//アニメーション
			if (animation > 3)
			{
				animation = 0;
			}
		}
		else
		{
			animation = 5;
		}

		break;
	case MARIO_STATE::SUPER_MARIO:
		//ファイアマリオと一緒

	case MARIO_STATE::FIRE_MARIO:
		//当たり判定の設定
		area.height = SUPER_MARIO_HEIGHT;
		area.width = SUPER_MARIO_WIDTH;

		//スティックの受付
		if (stick_y < stick_sensitivity * -1)
		{
			animation = 1;
		}
		else if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_DOWN))
		{
			animation = 1;
		}

		else if (right_flg == true && movement_speed < 0 && jump_flg == false
			|| left_flg == true && movement_speed > 0 && jump_flg == false)
		{
			animation = 5;
		}

		//アニメーション関係
		else if (jump_flg == false)
		{
			//アニメーション
			if (animation > 4)
			{
				animation = 0;
			}

			if (animation == 0)
			{
				animation = 2;
			}
		}
		else
		{
			animation = 6;
		}


		break;

	default:
		break;
	}

	//マリオ移動関係
	Operation();

	//ジャンプ受付
	if (PadInput::OnButton(XINPUT_BUTTON_B) && jump_flg == false && fall_flg == true)
	{
		jump_flg = true;
	}

	if (jump_flg == true)
	{
		MarioJump();
	}
	else
	{

		jumping_descent_speed = 0;
		b_button_press_time = 0;

	}

	if (PadInput::OnPressed(XINPUT_BUTTON_Y) || power_up_flg == true)
	{
		PowerUpAnimation();
	}


	if (hit_block_flg)
	{
		hit_block_flg = false;
	}

	if (fall_flg)
	{
		fall_flg = false;
		descent_speed = 0;
	}
	else
	{
		if (jump_flg == false && hit_block_flg == false)
		{
			if (descent_speed < FALL_SPEED_MAX)
			{
				descent_speed += FALL_SPEED;
			}
			//落ちる
			location.y += descent_speed;
		}
	}


	//画面外にいかないように
	if (location.x < area.width / 2)
	{
		location.x = old_location.x;
	}

}


//-----------------------------------
// 描画
//-----------------------------------
void Player::Draw() const
{
	////デバック
	DrawBox(view_charx - (area.width / 2), location.y - (area.height / 2),
		(view_charx - (area.width / 2)) + area.width, location.y + (area.height / 2),
		GetColor(255, 255, 0), false);

	switch (mario_state)
	{
	case MARIO_STATE::AMALL_MAIO:

		DrawRotaGraphF(view_charx, location.y, 1,
			M_PI / 180, tiny_mario[animation], TRUE, left_move);
		break;
	case MARIO_STATE::SUPER_MARIO:

		DrawRotaGraphF(view_charx, location.y, 1,
			M_PI / 180, super_mario_image[animation], TRUE, left_move);

		break;
	case MARIO_STATE::FIRE_MARIO:
		DrawRotaGraphF(view_charx, location.y, 1,
			M_PI / 180, fire_mario[animation], TRUE, left_move);
		break;
	case MARIO_STATE::STAR_MARIO:
		break;
	case MARIO_STATE::CHANGE_SUPER_MARIO:

		DrawRotaGraphF(view_charx, location.y, 1,
			M_PI / 180, power_up_image[power_up_animation], TRUE, left_move);

		break;
	case MARIO_STATE::CHANGE_FIRE_MARIO:
		DrawRotaGraphF(view_charx, location.y, 1,
			M_PI / 180, star_mario[power_up_animation], TRUE, left_move);

		break;
	case MARIO_STATE::DEATH:
		break;
	default:
		break;
	}

	//デバック
	DrawFormatString(100, 100, 0xFFFFFF, "%d 頭", bust_flg);

	//デバック
	DrawFormatString(100, 300, 0xFFFFFF, "%f", jumping_descent_speed);

	DrawFormatString(100, 200, 0xFFFFF, "%d 横", side_flg);

	DrawFormatString(300, 200, 0xFFFFF, "%f", location.x);

	DrawFormatString(400, 200, 0xFFFFFF, "%d 落", fall_flg);


}


//-----------------------------------
// マリオ移動系
//-----------------------------------
void Player::Operation()
{
	// スティックの感度
	const int stick_sensitivity = 200;

	stick_x = PadInput::GetLStick().x;

	//スティックの受付
	if (stick_x > stick_sensitivity || stick_x < stick_sensitivity * -1)
	{

		++animation_time;

		//Aボタンを押しているのか
		if (PadInput::OnPressed(XINPUT_BUTTON_A))
		{
			// スティックが右に移動した場合
			if (stick_x > 0)
			{
				right_flg = true;
				left_flg = false;

				//最大加速速度より小さいか
				if (movement_speed <= RUNNING_SPEED)
				{
					movement_speed += ACCELERATION_MAX_SPEED;
				}
			}
			// スティックが左に移動した場合
			else if (stick_x < 0)
			{
				right_flg = false;
				left_flg = true;
				if (movement_speed > -RUNNING_SPEED)
				{
					movement_speed -= ACCELERATION_MAX_SPEED;
				}
			}
		}

		//Aボタンを押していないとき
		else
		{
			// スティックが右に移動した場合
			if (stick_x > 0)
			{
				right_flg = true;
				left_flg = false;

				if (movement_speed > WALKING_SPEED)
				{
					movement_speed -= ACCELERATION_SPEED;
				}
				else if (movement_speed <= WALKING_SPEED)
				{
					movement_speed += ACCELERATION_SPEED;
				}
			}
			// スティックが左に移動した場合
			else if (stick_x < 0)
			{
				right_flg = false;
				left_flg = true;

				if (movement_speed > -WALKING_SPEED)
				{
					movement_speed -= ACCELERATION_SPEED;
				}
				else if (movement_speed < -WALKING_SPEED)
				{
					movement_speed += ACCELERATION_SPEED;
				}
			}
		}
	}
	else if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT) || PadInput::OnPressed(XINPUT_BUTTON_DPAD_LEFT))
	{
		++animation_time;

		//Aボタンを押しているのか
		if (PadInput::OnPressed(XINPUT_BUTTON_A))
		{
			//十字キーの右を押したら
			if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT))
			{

				right_flg = true;
				left_flg = false;

				//最大加速速度より小さいか
				if (movement_speed <= RUNNING_SPEED)
				{
					movement_speed += ACCELERATION_MAX_SPEED;
				}

			}
			else if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_LEFT))
			{

				right_flg = false;
				left_flg = true;

				if (movement_speed > -RUNNING_SPEED)
				{
					movement_speed -= ACCELERATION_MAX_SPEED;
				}
			}
		}
		//Aボタンが押されていなかったら
		else
		{
			if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT))
			{

				right_flg = true;
				left_flg = false;

				if (movement_speed > WALKING_SPEED)
				{
					movement_speed -= ACCELERATION_SPEED;
				}
				else if (movement_speed <= WALKING_SPEED)
				{
					movement_speed += ACCELERATION_SPEED;
				}


			}
			else if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_LEFT))
			{

				right_flg = false;
				left_flg = true;

				if (movement_speed > -WALKING_SPEED)
				{
					movement_speed -= ACCELERATION_SPEED;
				}
				else if (movement_speed < -WALKING_SPEED)
				{
					movement_speed += ACCELERATION_SPEED;
				}
			}

		}

	}
	//何もしていない時
	else
	{

		if (movement_speed > 0.1)
		{
			movement_speed -= ACCELERATION_SPEED;
		}
		else if (movement_speed <= -0.1)
		{
			movement_speed += ACCELERATION_SPEED;
		}
		else
		{
			movement_speed = 0;
		}
	}

	if (side_flg)
	{
		side_flg = false;
		movement_speed = 0;
	}

	location.x += movement_speed;
}

//-----------------------------------
// マリオのジャンプ系
//-----------------------------------
void Player::MarioJump()
{
	//Bボタンを押している長さ
	if (PadInput::OnPressed(XINPUT_BUTTON_B))
	{
		b_button_press_time += 0.1;
	}

	//Bボタンを押している時間によって飛ぶ力を変える
	if (b_button_press_time < 0.6)
	{
		jumping_power = -MINIUM_JUMP;
	}
	else if (b_button_press_time >= 0.6 && b_button_press_time < 1)
	{
		jumping_power = -INTERIM_JUMP;
	}

	//ジャンプ開始
	jumping_descent_speed += JUMP_FALL;

	location.y += jumping_power + jumping_descent_speed;

}

//-----------------------------------
// マリオがパワーアップアイテムを取得した時の動き
//-----------------------------------
void Player::PowerUpAnimation()
{

	//マリオの状態確認
	if (mario_state == MARIO_STATE::AMALL_MAIO)
	{
		mario_state = MARIO_STATE::CHANGE_SUPER_MARIO;
		power_up_flg = true;
	}
	else if (mario_state == MARIO_STATE::SUPER_MARIO)
	{
		mario_state = MARIO_STATE::CHANGE_FIRE_MARIO;
		power_up_flg = true;
	}

	//スーパマリオに変化
	if (mario_state == MARIO_STATE::CHANGE_SUPER_MARIO)
	{

		if (animation_time++ % POWRT_UP_TIME == 0)
		{
			animation_count++;
		}

		switch (animation_count)
		{
		case 0:
			power_up_animation = 0;
			break;
		case 1:
			power_up_animation = 1;
			break;
		case 2:
			power_up_animation = 0;
			break;
		case 3:
			power_up_animation = 1;
			break;
		case 4:
			power_up_animation = 2;
			break;
		case 5:
			power_up_animation = 0;
			break;
		case 6:
			power_up_animation = 2;
			break;

		case 8:
			power_up_flg = false;
			mario_state = MARIO_STATE::SUPER_MARIO;
			power_up_animation = 0;
			animation_count = 0;
		default:
			break;
		}
	}

	//ファイアマリオに変化する
	else if (mario_state == MARIO_STATE::CHANGE_FIRE_MARIO)
	{
		if (animation_time++ % FIRE_MARIO_TIME == 0)
		{
			animation_count++;
		}

		switch (animation_count)
		{
		case 0:
			power_up_animation = fire_power_up[0] + animation;
			break;
		case 1:
			power_up_animation = fire_power_up[1] + animation;
			break;
		case 2:
			power_up_animation = fire_power_up[2] + animation;
			break;
		case 3:
			power_up_animation = fire_power_up[3] + animation;
			break;
		case 4:
			power_up_animation = fire_power_up[0] + animation;
			break;
		case 5:
			power_up_animation = fire_power_up[1] + animation;
			break;
		case 6:
			power_up_animation = fire_power_up[2] + animation;
			break;
		case 7:
			power_up_animation = fire_power_up[3] + animation;
			break;
		case 8:
			power_up_animation = fire_power_up[0] + animation;
			break;
		case 9:
			power_up_animation = fire_power_up[1] + animation;
			break;
		case 10:
			power_up_animation = fire_power_up[2] + animation;
			break;
		case 11:
			power_up_animation = fire_power_up[3] + animation;
			break;
		case 12:
			power_up_animation = fire_power_up[0] + animation;
			break;
		case 13:
			power_up_animation = fire_power_up[1] + animation;
			break;
		case 15:
			power_up_flg = false;
			mario_state = MARIO_STATE::FIRE_MARIO;
			power_up_animation = 0;
			animation_count = 0;
		default:
			break;
		}
	}

}

void Player::Hit(const Stage* stage)
{

	////自分の当たり判定の範囲
	//float my_x[6];
	//float my_y[6];

	////相手の当たり判定の範囲
	//float sub_x[2];
	//float sub_y[2];

	////自分の当たり判定の範囲の計算
	//my_x[0] = location.x - (area.width / 2);
	//my_y[0] = location.y  -(area.height / 2);
	//my_x[1] = my_x[0] + area.width;
	//my_y[1] = my_y[0] + area.height;

	////	地面との当たり判定
	//my_x[2] = location.x - (area.width / 2);
	//my_y[2] = location.y - (area.height / 2);
	//my_x[3] = my_x[2] + area.width;
	//my_y[3] = my_y[2] + area.height;


	////横との当たり判定

	//if (right_flg)
	//{
	//	my_x[4] = (location.x ) - (area.width / 2);
	//	my_x[5] = my_x[4] + (area.width + 2);
	//}
	//else
	//{
	//	my_x[4] = (location.x ) - (area.width / 2);
	//	my_x[5] = my_x[4] + (area.width + 2);
	//}

	//my_y[4] = location.y;
	//my_y[5] = my_y[4];


	////相手の当たり判定の範囲の計算
	//sub_x[0] = stage->GetLocation().x;
	//sub_y[0] = stage->GetLocation().y;
	//sub_x[1] = sub_x[0] + stage->GetArea().width;
	//sub_y[1] = sub_y[0] + stage->GetArea().height;

	//if ((my_x[0] <= sub_x[1]) && (sub_x[0] <= my_x[1])
	//	&& (my_y[0] <= sub_y[1]) && (sub_y[0] <= my_y[1])) //当たり判定
	//{
	//	hit_block_flg = true;
	//}

	//if (hit_block_flg)
	//{

	//	//地面についているのか
	//	if ((my_x[2] <= sub_x[1]) && (sub_x[0] <= my_x[3])
	//		&& (my_y[2] <= sub_y[1]) && (sub_y[0] <= my_y[3]))
	//	{
	//		jump_flg = false;
	//		fall_flg = true;
	//	}

	//	//横方向に当たっているのか
	//	if ((my_x[4] <= sub_x[1]) && (sub_x[0] <= my_x[5])
	//		&& (my_y[4] <= sub_y[1]) && (sub_y[0] <= my_y[5]))
	//	{
	//		side_flg = true;
	//	}


	//}




	//自分の当たり判定の範囲
	float my_x[8];
	float my_y[8];

	//相手の当たり判定の範囲
	float sub_x[2];
	float sub_y[2];

	//自分の当たり判定の範囲の計算
	my_x[0] = location.x - (area.width / 2);
	my_y[0] = location.y - (area.height / 2);
	my_x[1] = my_x[0] + area.width;
	my_y[1] = my_y[0] + area.height;

	//	地面との当たり判定
	my_x[2] = (location.x - 1) - (area.width / 2);
	my_y[2] = location.y + ((area.height / 2) / 2);
	my_x[3] = my_x[2] + area.width;
	my_y[3] = location.y + (area.height / 2);


	//横との当たり判定


	my_x[4] = location.x - (area.width / 2);
	my_y[4] = location.y - (area.height / 2);
	my_x[5] = my_x[4] + area.width;
	my_y[5] = my_y[4] + (area.height / 2);

	//上半身の当たり判定
	my_x[6] = location.x - (area.width / 2);
	my_y[6] = location.y - (area.height / 2);
	my_x[7] = my_x[6] + area.width;
	my_y[7] = my_y[6] + 10;


	//相手の当たり判定の範囲の計算
	sub_x[0] = stage->GetLocation().x;
	sub_y[0] = stage->GetLocation().y;
	sub_x[1] = sub_x[0] + stage->GetArea().width;
	sub_y[1] = sub_y[0] + stage->GetArea().height;


	if ((my_x[0] <= sub_x[1]) && (sub_x[0] <= my_x[1])
		&& (my_y[0] <= sub_y[1]) && (sub_y[0] <= my_y[1])) //当たり判定
	{
		hit_block_flg = true;


		if ((my_x[6] <= sub_x[1]) && (sub_x[0] <= my_x[7])
			&& (my_y[6] <= sub_y[1]) && (sub_y[0] <= my_y[7]))
		{
			jump_flg = false;
			bust_flg = true;
			fall_flg = false;
			location.y = old_location.y;
		}
		//地面についているのか
		else if ((my_x[2] <= sub_x[1]) && (sub_x[0] <= my_x[3])
			&& (my_y[2] <= sub_y[1]) && (sub_y[0] <= my_y[3]))
		{
			jump_flg = false;
			fall_flg = true;
			location.y = sub_y[0]- (area.height / 2);
		}

		//横方向に当たっているのか
		if ((my_x[4] <= sub_x[1]) && (sub_x[0] <= my_x[5])
			&& (my_y[4] <= sub_y[1]) && (sub_y[0] <= my_y[5]))
		{
			side_flg = true;
			location.x = old_location.x;
		}

	}

}

void Player::SetHitBlockFlg(bool set_flg)
{
	hit_block_flg = set_flg;
	fall_flg = set_flg;
}

bool Player::GetHitBlockFlg()
{
	return hit_block_flg;
}




