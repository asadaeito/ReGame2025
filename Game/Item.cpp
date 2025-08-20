#include "stdafx.h"
#include "Item.h"
#include"Player.h"

Item::Item()
{
	modelRender.Init("Assets/modelData/Item.tkm");

	player = FindGO<Player>("BattleCharacter");

}

Item::~Item()
{

}

bool Item::Start()
{
	
	return true;
}

void Item::Move()
{
	modelRender.SetPosition(position);
}

void Item::Rotation()
{
	//回転を加算する。
	rotation.AddRotationDegY(2.0f);

	modelRender.SetRotation(rotation);
}

void Item::Update()
{
	Move();

	Rotation();

	//プレイヤーからItemに向かうベクトルを計算。
	Vector3 diff = player->m_position - position;
	//ベクトルの長さが120.0fより小さかったら。
	if (diff.Length() <= 120.0f)
	{
		player->itemCount++;
		DeleteGO(this);
	}
	
	modelRender.Update();

}

void Item::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}
