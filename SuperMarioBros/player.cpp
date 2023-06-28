#include "player.h"
#include"DxLib.h"
#include <stdio.h>

//最大ジャンプ力
#define STRONG_JUMP 5.5

//歩くスピード
#define WALKING_SPEED 5.0f
#define RUNNING_SPEED 8.0f

//加速スピード
#define ACCELERATION_SPEED  0.1f
#define ACCELERATION_MAX_SPEED 0.3f

Player::Player()
{
	descent_speed = 0;
	movement_speed = 0;
	location.x = 30;
	location.y = 300;
	area.height = 32;
	area.width = 32;
	stick_x = 0;
}

Player::~Player()
{

}

void Player::Update()
{

	//マリオ操作関係
	Operation();


}

void Player::Draw() const
{

	DrawBox(location.x - area.width / 2, location.y - area.height / 2,
		location.x + area.width / 2, location.y + area.height / 2,
		GetColor(255, 255, 0), TRUE);

	DrawFormatString(100, 100, 0xFFFFFF, "%f", movement_speed);
}

void Player::Operation()
{
	// スティックのX座標を取得
	stick_x = PadInput::GetLStick().x;

	// スティックの感度
	const int stick_sensitivity = 20000;

	//スティックの受付
	if (stick_x > stick_sensitivity || stick_x < stick_sensitivity * -1)
	{

		// スティックが上に移動した場合
		if (stick_x > 0)
		{

		}
		// スティックが下に移動した場合
		else if (stick_x < 0)
		{

		}
	}
	else if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT) || PadInput::OnPressed(XINPUT_BUTTON_DPAD_LEFT))
	{
		//Aボタンを押しているのか
		if (PadInput::OnPressed(XINPUT_BUTTON_A))
		{
			//十字キーの右を押したら
			if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT))
			{
				//最大加速速度より小さいか
				if (movement_speed <= RUNNING_SPEED)
				{
					movement_speed += ACCELERATION_MAX_SPEED;
				}

			}
			else if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_LEFT))
			{
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

		location.x += movement_speed;

	}
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


		location.x += movement_speed;

	}
}
