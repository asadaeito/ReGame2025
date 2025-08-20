#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	animationClips[enAnimationClip_Run].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);

	m_modelRender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);

	characterController.Init(25.0f, 75.0f, m_position);

}

Player::~Player()
{

}

void Player::Update()
{

	//移動処理
	Move();
	//回転処理
	Rotation();
	//ステートの管理
	ManageState();
	//アニメーションの再生
	PlayAnimation();
	m_modelRender.Update();
}

void Player::Move()
{
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	//スティック情報取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//前後左右ベクトル取得
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	forward.y = 0.0f;
	right.y = 0.0f;

	//ダッシュ判定とスピード設定

	isDashing = g_pad[0]->IsPress(enButtonB);//Bボタン押しっぱなしでダッシュ。

	//三項演算子でダッシュか歩きかでスピードを変える
	float speed = isDashing ? 300.0f : 120.0f;

	//スティックの方向にスピードを反映
	right *= stickL.x * speed;
	forward *= stickL.y * speed;
	
	//i移動速度に加算
	moveSpeed += right + forward;


	//ジャンプ処理
	if (characterController.IsOnGround())
	{
		moveSpeed.y = 0.0f;
		jumpcount = 0;
		
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			moveSpeed.y = 600.0f;
			jumpcount++;
		}
	}
	else
	{
		moveSpeed.y -= 10.0f;

		if (g_pad[0]->IsTrigger(enButtonA) && jumpcount <2)
		{
			moveSpeed.y = 500.0f;
			jumpcount++;
		}
	}

	//ダッシュ状態を確認
	right *= stickL.x * speed;
	forward *= stickL.y * speed;

	m_position = characterController.Execute(moveSpeed, 1.0f / 60.0f);

	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		rotation.SetRotationYFromDirectionXZ(moveSpeed);

		m_modelRender.SetRotation(rotation);
	}
}

void Player::ManageState()
{
	//地面に着いていなかったら。
	if (characterController.IsOnGround() == false)
	{
		playerState = 1;//空中
		return;
	}

	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		if (isDashing)
		{
			playerState = 3;//ダッシュ
		}
		else 
		{
			playerState = 2;//歩き

		}
	}
	//x,zの移動速度がなかったら~
	else
	{
		playerState = 0;//待機
	}
}

void Player::PlayAnimation()
{
	switch (playerState)
	{
	case 0:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1:
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
	case 2:
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	case 3:
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	}

}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
