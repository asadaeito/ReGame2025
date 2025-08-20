#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"
#include "Sound/SoundEngine.h"

GameOver::GameOver()
{
	g_soundEngine->ResistWaveFileBank(2, "Assets/Sound/GameoverBGM.wav");
	gameOverBGM = NewGO<SoundSource>(2);
	gameOverBGM->Init(2);
	gameOverBGM->Play(false);
}

GameOver::~GameOver()
{
	
}

void GameOver::Update()
{
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		NewGO<Title>(0, "Title");
		DeleteGO(this);
	}
}

void GameOver::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}