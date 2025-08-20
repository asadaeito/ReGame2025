#include "stdafx.h"
#include "GameCamera.h"
#include"Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(0.0f, 125.0f, -250.0f);
	//プレイヤーのインスタンスを探す。
	m_player = FindGO<Player>("BattleCharacter");

	//カメラのニアクリップとファークリップを設定する。
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(40000.0f);

	return true;
}

void GameCamera::Update()
{

	
	Vector3 target;
	target.x = m_player->m_position.x;

	target.y = m_player->m_position.y += 100.0f;
	target.z = m_player->m_position.z;

	g_camera3D->SetTarget(target);

	Vector3 cameraPos;
	cameraPos = target;

	cameraPos.z -= 300.0f;

	g_camera3D->SetPosition(cameraPos);
}

