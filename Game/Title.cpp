#include "stdafx.h"
#include "Title.h"
#include"Game.h"
#include"Sound/soundEngine.h"

Title::Title()
{
	spriteRender.Init("Assets/modelData/Title.dds", 1920.0f, 1080.0f);
	
	g_soundEngine->ResistWaveFileBank(0, "Assets/Sound/TitleBGM.wav");
	titleBGM = NewGO<SoundSource>(0);
	titleBGM->Init(0);
	titleBGM->Play(true);
}

Title::~Title()
{
	DeleteGO(titleBGM);
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonStart))
	{
		Game* game = NewGO<Game>(0, "Game");
		DeleteGO(this);
		return;
	}
}

void Title::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}