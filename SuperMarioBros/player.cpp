#include "player.h"
#include"DxLib.h"

#define STRONG_JUMP 5.5 

Player::Player()
{
	descent_speed = 0;
	movement_speed = 1.5;
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
		if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT))
		{
			if (movement_speed >= 0 &&movement_speed<=3.5)
			{
				movement_speed += 0.5;
			}
			location.x += movement_speed;
		}
		else if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_LEFT))
		{
			if (movement_speed >= 0 && movement_speed <= 3.5)
			{
				movement_speed += 0.5;
			}
			location.x += movement_speed * -1;
		}
	}
}

void Player::Draw() const
{

	DrawBox(location.x - area.width / 2, location.y - area.height / 2,
		location.x + area.width / 2, location.y + area.height / 2,
		GetColor(255, 255, 0), TRUE);
}
