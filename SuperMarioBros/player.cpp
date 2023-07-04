#include "player.h"
#include"DxLib.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

//�����蔻��̑傫��
#define AMALL_MAIO_WIDTH 32
#define AMALL_MAIO_HEIGHT 32

#define SUPER_MARIO_WIDTH 32
#define SUPER_MARIO_HEIGHT 64


//�A�j���[�V�����؂�ւ�����
#define SWITCHING_TIME 6
#define POWRT_UP_TIME 10

//�ő�W�����v��
#define STRONG_JUMP 5.5

//�����X�s�[�h
#define WALKING_SPEED 5.0f
#define RUNNING_SPEED 8.0f

//�����X�s�[�h
#define ACCELERATION_SPEED  0.1f
#define ACCELERATION_MAX_SPEED 0.3f

//�W�����v��
#define MINIUM_JUMP 12.0f
#define INTERIM_JUMP 16.0f
#define MAX_JUMP 6.5f

//�W�����v����
#define JUMP_FALL_SPEED 0.6f

Player::Player()
{

	LoadDivGraph("image/mario/mario.png", 9, 9, 1, 32, 32, tiny_mario);
	LoadDivGraph("image/mario/dekamarimation.png", 3, 3, 1, 32, 64, power_up_image);
	LoadDivGraph("image/mario/dekamario.png", 9, 9, 1, 32, 64, super_mario_image);

	animation = 0;
	animation_time = 0;
	animation_count = 0;
	power_up_animation = 0;

	descent_speed = 0;
	movement_speed = 0;
	b_button_press_time = 0;
	jumping_power = -MINIUM_JUMP;
	location.x = 30;
	location.y = 300;
	area.height = 32;
	area.width = 32;
	stick_x = 0;

	jump_flg = false;
	left_move = false;
	power_up_flg = false;

	mario_state = MARIO_STATE::AMALL_MAIO;
}

Player::~Player()
{

}

void Player::Update()
{
	//�����蔻��̐ݒ�
	switch (mario_state)
	{
	case MARIO_STATE::AMALL_MAIO:
		//�����蔻��̐ݒ�
		area.height = AMALL_MAIO_HEIGHT;
		area.width = AMALL_MAIO_WIDTH;
		break;
	case MARIO_STATE::SUPER_MARIO:
		//�t�@�C�A�}���I�ƈꏏ

	case MARIO_STATE::FIRE_MARIO:
		//�����蔻��̐ݒ�
		area.height = SUPER_MARIO_HEIGHT;
		area.width = SUPER_MARIO_WIDTH;
		break;
	
	default:
		break;
	}

	//�}���I�ړ��֌W
	Operation();

	//�W�����v��t
	if (PadInput::OnButton(XINPUT_BUTTON_B) && jump_flg == false)
	{
		jump_flg = true;
	}

	if (jump_flg == true)
	{
		MarioJump();
	}

	//�A�j���[�V����
	if (movement_speed != 0)
	{
		if (++animation_time % SWITCHING_TIME == 0)
		{
			animation++;

			if (animation > 3)
			{
				animation = 0;
			}
		}

		if (movement_speed > 0)
		{
			//���ɓ����Ă���̂�
			left_move = false;
		}
		else
		{
			//���ɓ����Ă���̂�
			left_move = true;

		}

	}

	if (PadInput::OnPressed(XINPUT_BUTTON_Y) || power_up_flg == true)
	{
		PowerUpAnimation();
	}

}

void Player::Draw() const
{

	DrawBox(location.x - area.width / 2, location.y - area.height / 2,
		location.x + area.width / 2, location.y + area.height / 2,
		GetColor(255, 255, 0), TRUE);

	switch (mario_state)
	{
	case MARIO_STATE::AMALL_MAIO:

		DrawRotaGraphF(location.x, location.y, 0.7f,
			M_PI / 180, tiny_mario[animation], TRUE, left_move);
		break;
	case MARIO_STATE::SUPER_MARIO:

		DrawRotaGraphF(location.x, location.y, 0.7f,
			M_PI / 180, super_mario_image[animation], TRUE, left_move);

		break;
	case MARIO_STATE::FIRE_MARIO:
		break;
	case MARIO_STATE::STAR_MARIO:
		break;
	case MARIO_STATE::CHANGE_SUPER_MARIO:

		DrawRotaGraphF(location.x, location.y, 0.7f,
			M_PI / 180, power_up_image[power_up_animation], TRUE, left_move);

		break;
	case MARIO_STATE::CHANGE_FIRE_MARIO:
		break;
	case MARIO_STATE::DEATH:
		break;
	default:
		break;
	}

	DrawFormatString(100, 100, 0xFFFFFF, "%f", movement_speed);

	DrawFormatString(100, 300, 0xFFFFFF, "%f", b_button_press_time);

	
}

void Player::Operation()
{
	// �X�e�B�b�N��X���W���擾
	stick_x = PadInput::GetLStick().x;

	// �X�e�B�b�N�̊��x
	const int stick_sensitivity = 200;

	//�X�e�B�b�N�̎�t
	if (stick_x > stick_sensitivity || stick_x < stick_sensitivity * -1)
	{

		//A�{�^���������Ă���̂�
		if (PadInput::OnPressed(XINPUT_BUTTON_A))
		{
			// �X�e�B�b�N����Ɉړ������ꍇ
			if (stick_x > 0)
			{
				//�ő�������x��菬������
				if (movement_speed <= RUNNING_SPEED)
				{
					movement_speed += ACCELERATION_MAX_SPEED;
				}
			}
			// �X�e�B�b�N�����Ɉړ������ꍇ
			else if (stick_x < 0)
			{
				if (movement_speed > -RUNNING_SPEED)
				{
					movement_speed -= ACCELERATION_MAX_SPEED;
				}
			}
		}

		//A�{�^���������Ă��Ȃ��Ƃ�
		else
		{
			// �X�e�B�b�N����Ɉړ������ꍇ
			if (stick_x > 0)
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
			// �X�e�B�b�N�����Ɉړ������ꍇ
			else if (stick_x < 0)
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
	}
	else if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT) || PadInput::OnPressed(XINPUT_BUTTON_DPAD_LEFT)
		|| stick_x > stick_sensitivity || stick_x < stick_sensitivity * -1)
	{
		//A�{�^���������Ă���̂�
		if (PadInput::OnPressed(XINPUT_BUTTON_A))
		{
			//�\���L�[�̉E����������
			if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT))
			{

				//�ő�������x��菬������
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
		//A�{�^����������Ă��Ȃ�������
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

	}
	//�������Ă��Ȃ���
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

	location.x += movement_speed;

}

void Player::MarioJump()
{
	//B�{�^���������Ă��钷��
	if (PadInput::OnPressed(XINPUT_BUTTON_B))
	{
		b_button_press_time += 0.1;
	}

	//B�{�^���������Ă��鎞�Ԃɂ���Ĕ�ԗ͂�ς���
	if (b_button_press_time < 0.6)
	{
		jumping_power = -MINIUM_JUMP;
	}
	else if (b_button_press_time >= 0.6 && b_button_press_time <1 )
	{
		jumping_power = -INTERIM_JUMP;
	}

	//�W�����v�J�n
	descent_speed += JUMP_FALL_SPEED;
	location.y += jumping_power + descent_speed;


	//�f�o�b�N
	if (location.y > 460)
	{
		jump_flg = false;
		descent_speed= 0;
		b_button_press_time = 0;
	}

}


void Player::PowerUpAnimation()
{

	//�}���I�̏�Ԋm�F
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

	//�X�[�p�}���I�ɕω�
	if (mario_state == MARIO_STATE::CHANGE_SUPER_MARIO)
	{

		if (animation_time % POWRT_UP_TIME == 0)
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
	else if (mario_state == MARIO_STATE::CHANGE_SUPER_MARIO)
	{
		
	}

}