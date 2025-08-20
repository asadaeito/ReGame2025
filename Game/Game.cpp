#include "stdafx.h"
#include "Game.h"
#include"nature/skyCube.h"
#include"Player.h"
#include"Background.h"
#include"GameCamera.h"
#include"Item.h"
#include "Gameclear.h"
#include "GameOver.h"
#include "Title.h"
#include"graphics/RenderingEngine.h"
#include"Sound/SoundEngine.h"

Game::Game()
{
	InitSky();

	player = NewGO<Player>(0, "BattleCharacter");
	
	gameCamera = NewGO<GameCamera>(0, "gameCamera");

	backGround = NewGO<Background>(0);

	//Item* item[5];

    Item*item1 = NewGO<Item>(0, "Item1");
	item1->position = { 0.0f,25.0f,1100.0f };
	
	Item*item2 = NewGO<Item>(0, "Item2");
	item2->position = { 0.0f,420.0f,2460.0f };
	
	Item*item3 = NewGO<Item>(0, "Item3");
	item3->position = { 0.0f,740.0f,3950.0f };
	
	Item*item4 = NewGO<Item>(0, "Item4");
	item4->position = { 0.0f,-870.0f,4100.0f };
	
	Item*item5 = NewGO<Item>(0, "Item5");
	item5->position = { 0.0f,-380.0f,6500.0f };

	gameCamera->m_player = player;

	g_soundEngine->ResistWaveFileBank(1, "Assets/Sound/GameBGM.wav");
	gameBGM = NewGO<SoundSource>(1);
	gameBGM->Init(1);
	gameBGM->Play(true);
}

Game::~Game()
{
	DeleteGO(gameCamera);
	DeleteGO(backGround);
	DeleteGO(player);
	DeleteGO(m_skyCube);
	DeleteGO(gameBGM);

	DeleteGO(FindGO<Item>("Item1"));
	DeleteGO(FindGO<Item>("Item2"));
	DeleteGO(FindGO<Item>("Item3"));
	DeleteGO(FindGO<Item>("Item4"));
	DeleteGO(FindGO<Item>("Item5"));
}

void Game::InitSky()
{
	//現在の空を廃棄
	DeleteGO(m_skyCube);
	m_skyCube = NewGO<SkyCube>(0, "skycube");

	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);

	//環境光の計算のためのIBLテクスチャをセットする。
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 1.0f);
	//環境日光の影響が分かりやすいように、ディレクションライトはオフにする。
	g_renderingEngine->SetDirectionLight(0, g_vec3Zero, g_vec3Zero);
}



void Game::Update()
{
	if(player->itemCount >= 5)
	{
		Gameclear* gameclear = NewGO<Gameclear>(0, "Gameclear");
		gameclear->spriteRender.Init("Assets/modelData/Gameclear.dds", 1920.0f, 1080.0f);
		DeleteGO(this);
		return;
	}

	if(player->m_position.y < -1000.0f)
	{
		GameOver* gameOver = NewGO<GameOver>(0, "GameOver");
		gameOver->spriteRender.Init("Assets/modelData/Gameover.dds", 1920.0f, 1080.0f);
		DeleteGO(this);
		return;
	}
}

void Game::Render(RenderContext& rc)
{
	
}